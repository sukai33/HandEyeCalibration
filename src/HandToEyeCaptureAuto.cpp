//
// Created by ty on 20-9-27.
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include <KinectCamera.h>
#include <Robot.h>
#include <XmlUtil.h>
#include <thread>

using namespace std;
using namespace cv;

// input 参考文件
char *extrinsic_param_path_refer = "./extrinsic_param_hand_to_eye_refer.xml";

// output
char *extrinsic_output_param_path = "./extrinsic_param_hand_to_eye.xml";

KinectCamera * camera;

vector<Extrinsic> exts_refer; // 参考输入列表

vector<Extrinsic> exts; // 输出列表

std::string image_save_path = "./images";

Size patternSize(6, 9);

int captureAndSave(string image_path) {
    Mat colorMat;
    camera->capture(colorMat);
    // 如果在拍照的时候，发现此位置的照片找不到角点，跳过此位置, return -2, continue

    Mat gray;
    cvtColor(colorMat, gray, COLOR_BGR2GRAY);
    vector<Point2f> corners;
    bool patternfound = findChessboardCorners(gray, patternSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                                          + CALIB_CB_FAST_CHECK);
    if (!patternfound) {
        // 未发现角点，跳过当前循环
        return -2;
    }


    bool rst = imwrite(image_path, colorMat);
    if (!rst) {
        return -1;
    }

    return 0;
}

/**
 * 机械臂按照参考列表运动
 */

void robotRun() {

    int currentPositionIndex = 0;

    unsigned long size = exts_refer.size();
    while (true) {
        // 判断结束情况
        if (currentPositionIndex >= size){
            std::cout << "全部数据采集完毕！" << std::endl;
            break;
        }

        Extrinsic &ext_refer = exts_refer[currentPositionIndex];

        // 休息一会儿，确保拍照完成
        currentPositionIndex++;


        double joints[6] = {ext_refer.joints[0] * DE2RA,ext_refer.joints[1] * DE2RA,ext_refer.joints[2] * DE2RA,
                            ext_refer.joints[3] * DE2RA,ext_refer.joints[4] * DE2RA,ext_refer.joints[5] * DE2RA,};

        // 获取joints, 让机械臂运动
        int move_rst = Robot::getInstance()->moveJ(joints, true);
        if (move_rst != aubo_robot_namespace::InterfaceCallSuccCode) {
            std::cerr << "运动到指定位置失败 err: " << move_rst << " index: " << currentPositionIndex << std::endl;
            continue;
        }

        // 睡眠500ms
        std::this_thread::sleep_for(1000ms);

        stringstream ss;
        ss << image_save_path << "/image_" << exts.size() + 1 << ".jpg";

        // --------------------------------------------- 拍照 (最好确保角点存在)
        int capture_rst = captureAndSave(ss.str());

        if (capture_rst == -2) {
            std::cerr << "跳过当前循环，图片未发现角点" << std::endl;
            continue;
        } else if (capture_rst == -1) {
            std::cerr << "图片保存失败，请确保此目录存在，并可读写：" << image_save_path << std::endl; // return
            return;
        }
        // ---------------------------------------------- 保存当前机械臂的位姿Pose，关节角Joints

        aubo_robot_namespace::wayPoint_S wayPoint;
        int way_point_rst = Robot::getInstance()->robotServiceGetCurrentWaypointInfo(wayPoint);
        if (way_point_rst != aubo_robot_namespace::InterfaceCallSuccCode) {
            std::cerr << "获取当前路点信息失败，请重试" << std::endl;
            continue;
        }
        double* current_joints = wayPoint.jointpos;

        aubo_robot_namespace::Pos &pos = wayPoint.cartPos.position;
        aubo_robot_namespace::Rpy rpy;
        Robot::getInstance()->quaternionToRPY(wayPoint.orientation, rpy);

        // 创建保存的数据对象，
        Extrinsic ext{
                ss.str(),
                {current_joints[0] * RA2DE, current_joints[1]* RA2DE, current_joints[2]* RA2DE,
                 current_joints[3] * RA2DE, current_joints[4]* RA2DE, current_joints[5]* RA2DE},
                {pos.x * 1000,pos.y * 1000,pos.z * 1000,
                 rpy.rx, rpy.ry, rpy.rz}
        };

        exts.push_back(ext);

        printf("保存角点图片&机械臂信息成功 %d/%d \n", (int)exts.size(), (int)size);


    }

    writeXml(exts, extrinsic_output_param_path);

    std::cout << "数据保存成功！" << std::endl;

}
/**
 * 
 */
int main(int argc, char *argv[]) {

    // ---------------------------- 读取 参考数据 -------------------------1
    exts_refer = readXml(extrinsic_param_path_refer);

    if (exts_refer.empty()) {
        std::cerr << "参考路径没有数据" << std::endl;
        return -1;
    }

    std::cout << "获取到参考数据列表：" << exts_refer.size() << std::endl;

    // ----------------------------- 连接 Kinect2相机 ----------------------2
    camera = new KinectCamera();
    if (!camera->isOpened()) {
        std::cerr << "相机打开失败" << std::endl;
        return -1;
    }

    // ----------------------------- 连接 Aubo 机械臂-----------------------3
    char *ip = "192.168.36.23";
    int rst = Robot::getInstance()->connect(ip, 8899);
    if (rst != aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cerr << "连接机械臂失败： " << ip << std::endl;
        camera->release();
        return -1;
    }

    std::cout << "--------------------相机和机械臂连接成功，开始采集数据，数据将会自动保存" << std::endl;

    robotRun();

    camera->release();
    Robot::getInstance()->disConnect();


}
