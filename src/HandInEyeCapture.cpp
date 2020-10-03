/**
 * @Author: PoplarTang
 * @CreateTime: 2019-12-16
 * @Description:
 */
#include "AstraCamera.h"
#include <opencv2/opencv.hpp>
#include <Robot.h>
#include <XmlUtil.h>

using namespace std;
using namespace cv;

const int ACTION_ESC = 27;
const int ACTION_SPACE = 32;

// 输出的图片路径
std::string image_save_path = "./images2";
// 输出的配置文件路径
char *extrinsic_output_param_path = "./extrinsic_param_hand_in_eye.xml";

AstraCamera* astraCamera;
Size patternsize(6,9); //interior number of corners
vector<vector<Point2f>> corners_list; //this will be filled by the detected corners
vector<Extrinsic> exts;
int num_boards = 20;

void handle_image_data(cv::Mat &rgb, cv::Mat &depth){
//    cv::imshow("depth", depth / 4500);
    Mat gray, srcMat;
    rgb.copyTo(srcMat);

    cvtColor(rgb, gray, COLOR_BGR2GRAY);
    vector<Point2f> corners; //this will be filled by the detected corners
    bool patternfound = findChessboardCorners(gray, patternsize, corners,
                                              CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                              + CALIB_CB_FAST_CHECK);
    drawChessboardCorners(rgb, patternsize, Mat(corners), patternfound);

    int key = cv::waitKey(30) & 0xFF;
    if (key == ACTION_ESC || key == 'q') {
        astraCamera->release();
    } else if (key == ACTION_SPACE) {
        std::cout << "------------------- 保存图片和关节------------------" << std::endl;
        // 确保图像中包含角点
        if (patternfound) {
            // 2. 保存关节信息
            aubo_robot_namespace::wayPoint_S wayPoint;
            int robotRst = Robot::getInstance()->robotServiceGetCurrentWaypointInfo(wayPoint);
            if (robotRst != aubo_robot_namespace::ErrnoSucc) {
                std::cerr << "当前的关节信息获取失败，不保存任何信息" << std::endl;
                return;
            }

            bitwise_not(rgb, rgb);

            // 采集足够的数量自动停止。num_board = 20
            corners_list.push_back(corners);
            int count = corners_list.size();

            stringstream ss;
            ss << image_save_path << "/image_" << count << ".jpg";
            // 1. 保存图片到文件
            bool rst = imwrite(ss.str(), srcMat, (vector<int>{CV_IMWRITE_JPEG_QUALITY, 100}));
            if (!rst) {
                std::cerr << "文件保存失败，请确保指定目录存在并可写：" << image_save_path << std::endl;
                astraCamera->release();
                return;
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

            printf("保存角点图片&机械臂信息成功 %d/%d \n", count, num_boards);

            if (count >= num_boards) {
                std::cout << "标定板数量已满足需要，开始标定" << std::endl;

                writeXml(exts, extrinsic_output_param_path);

                astraCamera->release();
                return;
            }

        }else {
            std::cerr << "未发现标定板！" << std::endl;
        }

    }

    cv::imshow("rgb", rgb);
}


//astraCamera->setListener([&](cv::Mat& rgb, cv::Mat& depth){
//cv::imshow("rgb", rgb);
//cv::imshow("depth", depth / 4500);
//cv::waitKey(50);
//});

/**
 * 眼在手上的数据采集
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
//    std::cout << "opencv:" << cv::getVersionString() << std::endl;

    // 机械臂连接必须放到上边初始化

    // ----------------------------- 连接 Aubo 机械臂-----------------------3
    char *ip = "192.168.36.23";
    int rst = Robot::getInstance()->connect(ip, 8899);
    if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cerr << "连接机械臂失败： " << ip << std::endl;
        return -1;
    }

    // ----------------------------- 连接 Astra 相机 ----------------------2
    // 相机初始化
    astraCamera = new AstraCamera();
    astraCamera->setListener(&handle_image_data);
    // 阻塞式 -> true代表获取彩色图， false不获取深度图
    astraCamera->start(true, false);


    cv::destroyAllWindows();
    Robot::getInstance()->disConnect();
    return 0;
}
