/**
 * @Author: PoplarTang
 * @CreateTime: 2019-12-16
 * @Description:
 */
#include "AstraCamera.h"

const int ACTION_ESC = 27;
const int ACTION_SPACE = 32;

AstraCamera* astraCamera;

void handle_image_data(cv::Mat &rgb, cv::Mat &depth){
    cv::imshow("rgb", rgb);
//    cv::imshow("depth", depth / 4500);

    int key = cv::waitKey(30) & 0xFF;

    if (key == ACTION_ESC || key == 'q') {
        astraCamera->release();
        cv::destroyAllWindows();

    } else if (key == ACTION_SPACE) {
        std::cout << "------------------- 保存图片和关节" << std::endl;
    }
}

//astraCamera->setListener([&](cv::Mat& rgb, cv::Mat& depth){
//cv::imshow("rgb", rgb);
//cv::imshow("depth", depth / 4500);
//cv::waitKey(50);
//});

int main(int argc, char **argv) {
    std::cout << "opencv:" << cv::getVersionString() << std::endl;
    astraCamera = new AstraCamera();
    astraCamera->setListener(&handle_image_data);
    astraCamera->start(true, false);
    return 0;
}
