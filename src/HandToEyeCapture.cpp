//
// Created by ty on 20-9-26.
/**
 * OpenCV
 * freenect2
 */


#include <iostream>
#include <opencv2/opencv.hpp>
#include <KinectCamera.h>
#include <Robot.h>
#include <XmlUtil.h>

using namespace std;
using namespace cv;

const int ACTION_ESC = 27;
const int ACTION_SPACE = 32;

std::string image_save_path = "./images";

// 输出的配置文件路径
char *extrinsic_output_param_path = "./extrinsic_param_hand_to_eye.xml";


/**
 *
 * 手眼标定数据采集
 *
 *
 */

int main(int argc, char *argv[]) {


    // ----------------------------- 连接 Kinect2相机 -----------------------
    auto camera = new KinectCamera();
    if (!camera->isOpened()) {
        std::cerr << "相机打开失败" << std::endl;
        return -1;
    }

    // ----------------------------- 连接 Aubo 机械臂-----------------------
    char *ip = "192.168.36.25";
    int rst = Robot::getInstance()->connect(ip, 8899);
    if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cerr << "连接机械臂失败： " << ip << std::endl;
        camera->release();
        return -1;
    }

    std::cout << "--------------------相机和机械臂连接成功，开始采集数据，按【空格键】保存数据" << std::endl;


    Size patternSize(6, 9);
    float square_size = 20.0f;
    int num_boards = 20;
    Size imageSize;

    vector<Extrinsic> exts;

    vector<vector<Point2f>> corners_list;
    while (true) {
//    * 2. 循环接收相机数据rgb，depth (一定要在下次wait之前释放掉frames.   listener.release(frames);)

        Mat colorMat, srcMat, gray;

        camera->capture(colorMat);

        // 备份一份原图
        colorMat.copyTo(srcMat);

//    *     3. 在rgb彩色图里查找角点
        cvtColor(colorMat, gray, COLOR_BGR2GRAY);

        imageSize = gray.size();

        vector<Point2f> corners;
        bool patternfound = findChessboardCorners(gray, patternSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                         + CALIB_CB_FAST_CHECK);

        if(patternfound)
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                         TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

        drawChessboardCorners(colorMat, patternSize, corners, patternfound);


//    *     4. 接收用户输入： space保存照片，q停止采集执行标定，Esc退出标定
        int action = waitKey(30) & 0xff;
        if (action == ACTION_ESC) { // Esc
            std::cerr << "用户主动退出标定" << std::endl;
            camera->release();
            Robot::getInstance()->disConnect();
            return -1;
        } else if (action == 'q') {
            std::cerr << "停止数据采集" << std::endl;
            break;
        } else {
            if (action == ACTION_SPACE) { // Space
    //    *     5. 在合适的条件下结束循环
                if (patternfound) {
                    bitwise_not(colorMat, colorMat);


                    aubo_robot_namespace::wayPoint_S wayPoint;
                    int way_point_rst = Robot::getInstance()->robotServiceGetCurrentWaypointInfo(wayPoint);
                    if (way_point_rst != aubo_robot_namespace::InterfaceCallSuccCode) {
                        std::cerr << "获取当前路点信息失败，请重试" << std::endl;
                        continue;
                    }

                    corners_list.push_back(corners);
                    int size = (int)corners_list.size();

                    // -------------------------------------- 保存图片
                    stringstream ss;
                    ss << image_save_path << "/image_" << size << ".jpg";

                    bool rst = cv::imwrite(ss.str(), srcMat);
                    if (!rst) {
                        std::cerr << "图片保存失败，请确保此目录存在，并可读写：" << image_save_path << std::endl;
                        return -1;
                    }


                    // ------------------------------------- 保存当前机械臂的位姿Pose，关节角Joints
                    double* joints = wayPoint.jointpos;
                    printf("Joints: %f, %f, %f, %f, %f, %f \n",
                           joints[0] * RA2DE, joints[1]* RA2DE, joints[2]* RA2DE,
                           joints[3] * RA2DE, joints[4]* RA2DE, joints[5]* RA2DE);


                    aubo_robot_namespace::Pos &pos = wayPoint.cartPos.position;
                    aubo_robot_namespace::Rpy rpy;
                    Robot::getInstance()->quaternionToRPY(wayPoint.orientation, rpy);

                    cout << "Pose x: " << pos.x << " y: " << pos.y << " z: " << pos.z
                         <<  " rx: " << rpy.rx * RA2DE << " ry: " << rpy.ry * RA2DE<< " rz: " << rpy.rz * RA2DE << endl;

//                        printf("Pose: %f, %f, %f, %f, %f, %f \n"); std::string
                    // 创建保存的数据对象，
                    // 关节角度数单位degree
                    // 位姿距离单位mm， 度数单位radius
                    Extrinsic ext{
                            ss.str(),
                            {joints[0] * RA2DE, joints[1]* RA2DE, joints[2]* RA2DE,
                             joints[3] * RA2DE, joints[4]* RA2DE, joints[5]* RA2DE},
                            {pos.x * 1000,pos.y * 1000,pos.z * 1000,
                             rpy.rx, rpy.ry, rpy.rz}
                    };

                    exts.push_back(ext);

                    printf("保存角点图片&机械臂信息成功 %d/%d \n", size, num_boards);

                    if (size >= num_boards) {
                        std::cout << "标定板数量已满足需要，开始标定" << std::endl;
                        break;
                    }


                }else {
                    std::cerr << "未发现标定板" << std::endl;
                }

            }
        }
        resize(colorMat, colorMat, Size(), 0.5, 0.5);
        imshow("image", colorMat);

    }
    writeXml(exts, extrinsic_output_param_path);

    cv::destroyAllWindows();
    // 设备使用完毕后，及时关闭
    camera->release();

    Robot::getInstance()->disConnect();

    std::cout << "开始执行相机标定-------------------------" << std::endl;

}
