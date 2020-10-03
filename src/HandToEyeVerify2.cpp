//
// Created by ty on 20-9-29.
//

#include <KinectCamera.h>
// 要把Eigen声明放到OpenCV上边
#include <Eigen/Geometry>

#include <opencv/cxeigen.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Robot.h>
#include <Rotation3DUtils.h>

using namespace std;
using namespace cv;

string in_calib_file_path = "./hand_to_eye/calibration_in_params.yml";
string ex_calib_file_path = "./hand_to_eye/calibration_ex_params.yml";

Size patternSize(6, 9);
float squareSize = 0.020f;

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

Mat getExMat() {
    double Angle = 0, AxisX = 0, AxisY = 0, AxisZ = 0;
    double TranslationX = 0, TranslationY = 0, TranslationZ = 0;

    FileStorage fs(ex_calib_file_path, FileStorage::READ);

    fs["Angle"] >> Angle;
    fs["AxisX"] >> AxisX;
    fs["AxisY"] >> AxisY;
    fs["AxisZ"] >> AxisZ;
    fs["TranslationX"] >> TranslationX;
    fs["TranslationY"] >> TranslationY;
    fs["TranslationZ"] >> TranslationZ;

    // 将轴角对 -> 旋转矩阵 + 平移矩阵 -> 齐次矩阵
    Eigen::Vector3d axisMatrix(AxisX, AxisY, AxisZ);
    Eigen::AngleAxisd angleAxisd(Angle, axisMatrix);

    const Eigen::AngleAxis<double>::Matrix3 &eigenR = angleAxisd.toRotationMatrix();

    Mat cvR = Mat_<double>(3, 3);
    cv::eigen2cv(eigenR, cvR);

    Mat t = (Mat_<double>(3, 1) << TranslationX / 1000, TranslationY / 1000, TranslationZ / 1000);
    Mat exMat = toHomogeneousMat(cvR, t);
    return exMat;
}
/**
 * 构建标定板所有点的坐标, 54x4 -> 4x54
 * @return
 */
Mat getTargetBoardPoints(Size& patternSize, float squareSize){
    // 54 x 4
    Mat points3d = Mat(patternSize.width * patternSize.height, 4, CV_64FC1);
    double *points3dPtr = points3d.ptr<double>();

    for( int i = 0; i < patternSize.height; i++ ){ // row 9
        for( int j = 0; j < patternSize.width; j++ ){ // col 6
            *points3dPtr++ = j * squareSize;
            *points3dPtr++ = i * squareSize;
            *points3dPtr++ = 0;
            *points3dPtr++ = 1;
        }
    }
    return points3d;
}

void startVerify(Mat& R, vector<Point3d>& points3d) {
    //  1. 获取目标标定板在相机下的位姿cTt         ①
    Mat tMat = (Mat_<double>(3, 1) << points3d[0].x, points3d[0].y, points3d[0].z);
    const Mat &cTtMat = toHomogeneousMat(R, tMat);

    //  2. 读取相机的外参（在基坐标系下的位姿）bTc   ②
    const Mat &exMat = getExMat();

    std::cout << "标定板在相机下的位姿： \n" << cTtMat << std::endl;
    std::cout << "相机的外参： \n" << exMat << std::endl;

    //  3. 初始化标定枪位姿（在法兰盘坐标系下的位姿） ③
    float tool_z = 96.0f;
    Mat toolMat = Mat::eye(4, 4, CV_64FC1);
    toolMat.at<double>(2, 3) = tool_z / 1000.0f;
    std::cout << "工具末端的姿态: \n" << toolMat << std::endl;
    Mat toolMatInv = homogeneousInverse(toolMat); // inv(③)

    float tool_z_up = tool_z + 20.0f;
    Mat toolMatUp = Mat::eye(4, 4, CV_64FC1);
    toolMatUp.at<double>(2, 3) = tool_z_up / 1000.0f;
    Mat toolMatUpInv = homogeneousInverse(toolMatUp); // inv(③)

    //  4. 求：机械臂需要运动到的位姿 ④ = ② * ① * inv(③)
    Mat finalMat = exMat * cTtMat * toolMatInv;
    // 抬高后的标定板变换
    Mat finalMatUp = exMat * cTtMat * toolMatUpInv;

    // 让机械臂运动过去 -> xyz,rpy
    // 将4x4变换矩阵，拆分成3x3旋转矩阵+3x1平移矩阵
    Mat final_RMat = Mat::eye(3, 3, CV_64FC1);
    Mat final_tMat = Mat::zeros(3, 1, CV_64FC1);
    splitHomogeneousMat(finalMat, final_RMat, final_tMat);


    // 创建了标定板坐标系下所有点的坐标，单位m （54x4）[x,y,0,1]
    Mat targetBoardPoints = getTargetBoardPoints(patternSize, squareSize);
    // 把标定板坐标系下的所有点 左乘 变换矩阵 （finalMat）
    // (4x4) * (4x54) = (4x54)
    Mat targetBoardPoints_t = targetBoardPoints.t();
    // 目标点
    Mat targetPoints = (finalMat * targetBoardPoints_t).t();    // (54x4)
    // 目标上方的点
    Mat targetPointsUp = (finalMatUp * targetBoardPoints_t).t();      // (54x4)
    // 姿态
    const Vec3f &targetRPY = rotationMatrixToEulerAngles(final_RMat);

    // 记录当前的位置
    aubo_robot_namespace::wayPoint_S wayPoint;
    int way_point_rst = Robot::getInstance()->robotServiceGetCurrentWaypointInfo(wayPoint);
    if (way_point_rst != aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cerr << "获取当前路点信息失败，请重试" << std::endl;
    }
    double* initial_joints = wayPoint.jointpos;

    Vec4d *vec4dPtr = (Vec4d *) targetPoints.ptr();
    Vec4d *vec4dUpPtr = (Vec4d *) targetPointsUp.ptr();

    // 循环运动所有的角点
    for (int i = 0; i < targetPoints.rows; ++i) { // 54
        Vec4d point = *vec4dPtr++;
        Vec4d pointUp = *vec4dUpPtr++;

        double target[6] = {point[0], point[1], point[2], targetRPY[0], targetRPY[1], targetRPY[2]};
        double targetUp[6] = {pointUp[0], pointUp[1], pointUp[2], targetRPY[0], targetRPY[1], targetRPY[2]};

        // MoveJ到目标点上方20mm
        int rst = Robot::getInstance()->moveJwithPose(targetUp, true);
        if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
            std::cerr << "运动到指定目标点上方失败：" << i << " 错误码：" << rst << std::endl;
        }
        
        // MoveL下降到目标点
        rst = Robot::getInstance()->moveL(target, true);
        if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
            std::cerr << "下降到目标点失败：" << i << " 错误码：" << rst << std::endl;
        }

        // 夹爪夹取

        // MoveL从目标点抬起20mm
        rst = Robot::getInstance()->moveL(targetUp, true);
        if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
            std::cerr << "从目标点抬起失败：" << i << " 错误码：" << rst << std::endl;
        }

    }

    // 回到初始位置
    int return_rst = Robot::getInstance()->moveJ(initial_joints, true);
    if (return_rst != aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cerr << "回到初始位置失败，错误码：" << return_rst << std::endl;
    }
}

/**
 *  眼在手外的标定验证，为了确保外参无误（相机与机械臂的位置关系）
 *
 *  1. 获取目标标定板在相机下的位姿            ①
 *  2. 读取相机的外参（在基坐标系下的位姿）      ②
 *  3. 初始化标定枪位姿（在法兰盘坐标系下的位姿） ③
 *  4. 求：机械臂需要运动到的位姿 ④ = ② * ① * inv(③)
 *
 *  显示摄像头看到的内容，用户按下了空格，开始进行标定验证
 *  目标：标定枪尖端指向第一个点
 */
int main(int argc, char *argv[]) {

    // ----------------------------- 连接 Kinect2相机 ----------------------2
    KinectCamera *camera = new KinectCamera();
    if (!camera->isOpened()) {
        std::cerr << "相机打开失败" << std::endl;
        return -1;
    }

    // ----------------------------- 连接 Aubo 机械臂-----------------------3
    char *ip = "192.168.36.21";
    int rst = Robot::getInstance()->connect(ip, 8899);
    if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cerr << "连接机械臂失败： " << ip << std::endl;
        camera->release();
        return -1;
    }

    Robot::getInstance()->setOffset(-0.002, 0, 0); // 设置偏移量

    std::cout << "--------------------相机和机械臂连接成功，开始采集数据，数据将会自动保存" << std::endl;


    // 标定板对象的坐标
    vector<Point3f> objectPoints;
    calcChessboardPoints(patternSize, squareSize, objectPoints);

    // 相机的内参&畸变系数
    FileStorage fs(in_calib_file_path, FileStorage::READ);
    Mat cameraMatrix, distCoeffs;
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;
    fs.release();


    while (true) {
        Mat colorMat, gray;
        camera->capture(colorMat);

        // 保证画面里边有标定板，角点被识别到
        cvtColor(colorMat, gray, cv::COLOR_BGR2GRAY);

        vector<Point2f> corners;
        bool patternfound = findChessboardCorners(gray, patternSize, corners,
                                                  CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                  + CALIB_CB_FAST_CHECK);

        if (patternfound) {
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                         TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        }

        drawChessboardCorners(colorMat, patternSize, Mat(corners), patternfound);

        int action = waitKey(30) & 0xFF;
        if (action == 27 || action == 'q') { //esc
            std::cout << "退出验证" << std::endl;
            break;
        } else if (action == 32) { // space
            if (patternfound) {
                bitwise_not(colorMat, colorMat);
                std::cout << "开始验证" << std::endl;
//                *  1. 获取目标标定板在相机下的位姿            ①
                Mat rvec = Mat::zeros(3, 1, CV_64FC1);
                Mat tvec = Mat::zeros(3, 1, CV_64FC1);
                solvePnPRansac(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);

                Mat R;
                Rodrigues(rvec, R);

                vector<Point3d> points3d;
                points3d.emplace_back(tvec.at<double>(0), tvec.at<double>(1), tvec.at<double>(2));

                startVerify(R, points3d);

            }else {
                std::cerr << "未发现标定板，请确认" << std::endl;
            }
        }

        resize(colorMat, colorMat, Size(), 0.6, 0.6);
        imshow("image", colorMat);

    }

    camera->release();
    Robot::getInstance()->disConnect();


}



