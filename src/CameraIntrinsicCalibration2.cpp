//
// Created by ty on 20-9-26.
/**
 * OpenCV
 * freenect2
 */


#include <iostream>
#include <opencv2/opencv.hpp>
#include <KinectCamera.h>

using namespace std;
using namespace cv;

const int ACTION_ESC = 27;
const int ACTION_SPACE = 32;
std::string image_save_path = "./images";
string in_calib_file_path = "./calibration_in_params.yml";


void runAndSave(const Size &patternSize, const Size &imageSize, float square_size,
                vector<vector<Point2f>> &corners_list) {//    * 6. 开始标定（内参）

    vector<vector<Point3f>> objects_points;

    vector<Point3f> obj_points;
    /**
     * [
     *      [0,0,0], [1,0,0], [2,0,0]........[5,0,0]
     *      [0,1,0], [1,1,0], [2,1,0]........
     *      ...
     *      [0,8,0], [1,8,0], [2,8,0]........[5,8,0]
     * ]
     */
    // 遍历所有行 9
    for (int i = 0; i < patternSize.height; ++i) {
        // 遍历所有列 6
        for (int j = 0; j < patternSize.width; ++j) {
            obj_points.emplace_back(j * square_size, i * square_size, 0);
        }
    }
    // 根据corners_list的个数，填充objects_points， 内容为obj_points
    objects_points.resize(corners_list.size(), obj_points);

    // 输入：自己创建的对象点集合，角点集合
// 输出：相机内参，畸变系数
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F); // out
    Mat distCoeffs = Mat::zeros(5, 1, CV_64F); // out
    vector<Mat> rvecs, tvecs; // out
    double rms = calibrateCamera(objects_points, corners_list, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs);

    cout << "标定完成，误差的均方根: " << rms << endl;

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

    if (ok) {
        cout << "相机内参：" << endl;
        cout << cameraMatrix << endl;

        cout << "畸变系数：" << endl;
        cout << distCoeffs << endl;


        // 生成当前时间

        time_t tm;
        time(&tm);
        struct tm *t2 = localtime(&tm);
        char buf[1024];
        strftime(buf, sizeof(buf), "%c", t2);

        FileStorage fs(in_calib_file_path, FileStorage::WRITE);
        fs << "calibration_time" << buf;
        fs << "frame_count" << (int) corners_list.size();
        fs << "image_width" << imageSize.width;
        fs << "image_height" << imageSize.height;
        fs << "patternSize" << patternSize;
        fs << "square_size" << square_size;
        fs << "rms" << rms;

        fs << "cameraMatrix" << cameraMatrix;
        fs << "distCoeffs" << distCoeffs;
        fs.release();

        std::cout << "标定结果保存完毕！" << std::endl;

    } else {
        cerr << "标定结果有误，请重新标定" << endl;
    }

//    * 7. 保存标定的结果（内参）

}
/**
 * 内参标定 （实时采集相机数据）
 *
 * 1. 初始化相机
 * 2. 循环接收相机数据rgb，depth
 *     3. 在rgb彩色图里查找角点
 *     4. 接收用户输入： space保存照片，q停止采集执行标定，Esc退出标定
 *     5. 在合适的条件下结束循环
 * 6. 开始标定（内参）
 * 7. 保存标定的结果（内参）
 */

int main(int argc, char *argv[]) {


    KinectCamera* camera = new KinectCamera();

    if (!camera->isOpened()) {
        std::cerr << "相机打开失败" << std::endl;
        return -1;
    }

    Size patternSize(6, 9);
    float square_size = 20.0f;
    int num_boards = 20;
    Size imageSize;


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
            return -1;
        } else if (action == 'q') {
            std::cerr << "停止数据采集" << std::endl;
            break;
        } else {
            if (action == ACTION_SPACE) { // Space
    //    *     5. 在合适的条件下结束循环
                if (patternfound) {
                    bitwise_not(colorMat, colorMat);

                    corners_list.push_back(corners);

                    int size = (int)corners_list.size();

                    stringstream ss;
                    ss << image_save_path << "/image_" << size << ".jpg";

                    bool rst = cv::imwrite(ss.str(), srcMat);
                    if (!rst) {
                        std::cerr << "图片保存失败，请确保此目录存在，并可读写：" << image_save_path << std::endl;
                        return -1;
                    }

                    printf("保存角点及图片成功 %d/%d \n", size, num_boards);

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

    cv::destroyAllWindows();
    // 设备使用完毕后，及时关闭
    camera->release();

    std::cout << "开始执行相机标定-------------------------" << std::endl;

    runAndSave(patternSize, imageSize, square_size, corners_list);


}
