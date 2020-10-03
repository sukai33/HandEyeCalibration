//
// Created by ty on 20-9-27.
//


#include <iostream>
#include <XmlUtil.h>
#include <opencv2/opencv.hpp>
#include <Rotation3DUtils.h>
#include <Eigen/Geometry>

#include <opencv/cxeigen.hpp>

using namespace std;
using namespace cv;

// input
char *extrinsic_param_path = "./extrinsic_param_hand_in_eye.xml";
string in_calib_file_path = "./calibration_in_params_hand_in_eye.yml";
// 图片文件夹
std::string image_save_path = "./images2";


// output (包含外参信息的文件)
char* ex_calib_filepath = "./calibration_ex_params_hand_in_eye.yml";


enum Pattern { CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
static void calcChessboardPoints(Size boardSize, float squareSize, vector<Point3f>& objectPoints, Pattern patternType = CHESSBOARD)
{
    objectPoints.resize(0);

    switch(patternType)
    {
        case CHESSBOARD:
        case CIRCLES_GRID:
            for( int i = 0; i < boardSize.height; i++ )
                for( int j = 0; j < boardSize.width; j++ )
                    objectPoints.emplace_back(float(j*squareSize),
                                              float(i*squareSize), 0);
            break;

        case ASYMMETRIC_CIRCLES_GRID:
            for( int i = 0; i < boardSize.height; i++ )
                for( int j = 0; j < boardSize.width; j++ )
                    objectPoints.emplace_back(float((2*j + i % 2)*squareSize),
                                              float(i*squareSize), 0);
            break;

        default:
            CV_Error(Error::StsBadArg, "Unknown pattern type\n");
    }
}


/**
 *
 * 进行眼在手上的外参标定
 *
 * - 输入1： 多个位姿 -> bTg
 *          末端位姿xyzrpy -求逆-> 旋转R+平移t
 *
 * - 输入2： 多张图片 -> 角点 -> cTt
 *          旋转向量+平移向量 -> 旋转R+平移t
 *
 * - 输出： 外参矩阵 4x4 -> bTc
 */
int main(int argc, char *argv[]) {

    // 获取指定目录image_save_path下的所有文件的路径，存放到image_paths
    vector<String> image_paths;
    cv::glob(image_save_path, image_paths); // 1, 10, 11, ... 19, 2, 3, 4

//    * - 输入1： 多个位姿 -> bTg求逆（转置） -> gTb
    std::cout << "------------------ 基坐标系base下抓手gripper的表达 bTg-----------------" << std::endl;
    vector<Mat> R_gripper2base, t_gripper2base;
    vector<Extrinsic> exts = readXml(extrinsic_param_path); // 1, 2, 3,... 19

    map<std::string, double*> poseMap;
    for (auto &ext: exts) {
        // 构建map，key = 文件名， value = pose
        poseMap[ext.image_path] = ext.pose;
    }

    for (auto & path : image_paths) {
        std::cout << "imgPath: " << path << std::endl;
        double* pose = poseMap[path];

        // 旋转矩阵 RPY -> Rotation
        cv::Vec3f eulerAngles(pose[3], pose[4], pose[5]);
        const Mat &R = eulerAnglesToRotationMatrix(eulerAngles);
        std::cout << "eulerAngles: " << eulerAngles << std::endl;
        std::cout << "R: \n" << R << std::endl;

        // 平移矩阵
        Mat t = (Mat_<double>(3, 1) << pose[0], pose[1], pose[2]);
        std::cout << "t: " << t << std::endl;

        R_gripper2base.push_back(R);
        t_gripper2base.push_back(t  / 1000);

    }

//    * - 输入2： 多张图片 -> 角点 -> cTt
    std::cout << "------------------ 相机坐标系camera下标定板target的表达 cTt-----------------" << std::endl;
    vector<Mat> R_target2camera, t_target2camera;

    // 读取相机内参&畸变系数
    FileStorage fs(in_calib_file_path, FileStorage::READ);
    Mat cameraMatrix, distCoeffs;
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;
    fs.release();


    Size patternSize(6, 9);
    float squareSize = 20.0f;
    for (const String& path: image_paths) {
        std::cout << "imgPath: " << path << std::endl;
        const Mat &gray = imread(path, IMREAD_GRAYSCALE);

        vector<Point2f> corners; // 保存了当前图片角点的列表
        bool isFound = findChessboardCorners(gray, patternSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                                         + CALIB_CB_FAST_CHECK);

        if (!isFound) {
            std::cerr << "图片未发现角点，请检查： " << path << std::endl;
            return -1;
        }

        cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                     TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

        vector<Point3f> objectPoints;
        calcChessboardPoints(patternSize, squareSize, objectPoints);

        // 接收结果 (标定板在相机坐标系下的位置+姿态)
        Mat rvec = Mat::zeros(3, 1, CV_64FC1); // 旋转向量 （弧度）
        Mat tvec = Mat::zeros(3, 1, CV_64FC1); // 平移向量 （mm）
        solvePnPRansac(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);

        Mat R;
        cv::Rodrigues(rvec, R); // 罗德里格斯变换，可以将旋转矩阵和旋转向量进行互转

        const Vec3f &eulerAngles = rotationMatrixToEulerAngles(R);

        std::cout << "rotation rvec: \n" << rvec << std::endl;
        std::cout << "rotation R: \n" << R << std::endl;
        std::cout << "rotation eulerAngles: \n" << eulerAngles << std::endl;
        std::cout << "translation tvec: \n" << tvec << std::endl;
        std::cout << "-----------------------------" << std::endl;

        R_target2camera.push_back(R);
        t_target2camera.push_back(tvec / 1000);
    }

    std::cout << "gripper2base: " << R_gripper2base.size() << "-" << t_gripper2base.size() << std::endl;

    std::cout << "target2camera: " << R_target2camera.size() << "-" << t_target2camera.size() << std::endl;

    std::cout << "-------------------开始执行外参标定--------------------" << std::endl;

//    * - 输出： 外参矩阵 4x4 -> bTc
    Mat R_camera2gripper = Mat::eye(3, 3, CV_64F);
    Mat t_camera2gripper = Mat::zeros(3, 1, CV_64F);
    calibrateHandEye(
            R_gripper2base, t_gripper2base, R_target2camera, t_target2camera,  // 输入
            R_camera2gripper, t_camera2gripper, // 输出
            HandEyeCalibrationMethod::CALIB_HAND_EYE_DANIILIDIS
    );
    const Vec3f &euler = rotationMatrixToEulerAngles(R_camera2gripper);

    std::cout << "旋转矩阵：\n" << R_camera2gripper << std::endl;
    std::cout << "欧拉角：" << euler *  180.0f / M_PI << std::endl;
    std::cout << "平移矩阵：" << t_camera2gripper << std::endl;

    // 保存轴角对
    Eigen::Matrix3d eigenRotationMatrix;
    cv::cv2eigen(R_camera2gripper, eigenRotationMatrix);

    // 轴角对
    Eigen::AngleAxisd eigenAngleAxis(eigenRotationMatrix);
    
    // 取出角度
    double &angle = eigenAngleAxis.angle();
    
    // 取出3个轴
    Eigen::AngleAxis<double>::Vector3 &eigen_axis = eigenAngleAxis.axis();

    std::cout << "angle: " << angle << std::endl;
    std::cout << "eigen_axis: " << eigen_axis << std::endl;

    // 保存相机外参
    FileStorage outFs(ex_calib_filepath, FileStorage::WRITE);

    // 获取当前时间
    time_t tm;
    time(&tm);
    struct tm *t2 = localtime(&tm);
    char buf[1024];
    strftime(buf, sizeof(buf), "%c", t2);

    outFs << "calibration_time" << buf;
    outFs << "Angle" << angle;
    outFs << "AxisX" << eigen_axis[0];
    outFs << "AxisY" << eigen_axis[1];
    outFs << "AxisZ" << eigen_axis[2];
    outFs << "TranslationX" << t_camera2gripper.at<double>(0,0) * 1000;
    outFs << "TranslationY" << t_camera2gripper.at<double>(1,0) * 1000;
    outFs << "TranslationZ" << t_camera2gripper.at<double>(2,0) * 1000;

    outFs.release();

    std::cout << "外参文件保存成功： " << ex_calib_filepath << std::endl;
}