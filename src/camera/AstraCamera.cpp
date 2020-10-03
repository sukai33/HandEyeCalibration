//
// Created by ty on 20-7-2.
//

#include "AstraCamera.h"
#include <key_handler.h>

AstraCamera::AstraCamera() {

}
function<void(cv::Mat &, cv::Mat &)> astra_data_callback;

class SampleFrameListener : public astra::FrameListener {
private:
    using buffer_ptr = std::unique_ptr<astra::RgbPixel[]>;
    using buffer_depth_ptr = std::unique_ptr<int16_t[]>;
    buffer_ptr buffer_;
    buffer_depth_ptr buffer_depth_;
    int lastWidth_{};
    int lastHeight_{};
    int lastWidth_depth_{};
    int lastHeight_depth_{};

public:

    void on_frame_ready(astra::StreamReader &reader,
                        astra::Frame &frame) override {
        shared_ptr<cv::Mat> img = nullptr, depth = nullptr;

        const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();
        get_color(colorFrame, img);

        const astra::DepthFrame depthFrame = frame.get<astra::DepthFrame>();
        auto depthStream = reader.stream<astra::DepthStream>();
        get_depth(depthFrame, depthStream.coordinateMapper(), depth);

        astra_data_callback(*img, *depth);
    }

    void get_color(const astra::ColorFrame &colorFrame, shared_ptr<cv::Mat> &img) {

        if (colorFrame.is_valid()) {
            int width = colorFrame.width();
            int height = colorFrame.height();
            // cout << "宽度:" << width << "---高度:" << height << endl;

            if (width != lastWidth_ || height != lastHeight_) {
                buffer_ = buffer_ptr(new astra::RgbPixel[colorFrame.length()]);
                lastWidth_ = width;
                lastHeight_ = height;
            }
            colorFrame.copy_to(buffer_.get());

//            int frameIndex = colorFrame.frame_index();
//            size_t index = ((width * (height / 2.0f)) + (width / 2.0f));
//            cout << "index为：" << index << endl;
//            astra::RgbPixel middle = buffer_[index];

//            std::cout << "color frameIndex: " << frameIndex
//                      << " r: " << static_cast<int>(middle.r)
//                      << " g: " << static_cast<int>(middle.g)
//                      << " b: " << static_cast<int>(middle.b)
//                      << " width: " << width << " height: " << height << std::endl;

            // 将buffer_ptr 中astra::RgbPixel[]数据类型转成Mat
//            shared_ptr<cv::Mat> img = new shared_ptr<cv::Mat>(new cv::Mat(height, width, CV_8UC3, cv::Scalar::all(0)));
            img = std::make_shared<cv::Mat>(height, width, CV_8UC3, cv::Scalar::all(0));
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    img->at<cv::Vec3b>(i, j)[0] = buffer_[i * width + j].b;
                    img->at<cv::Vec3b>(i, j)[1] = buffer_[i * width + j].g;
                    img->at<cv::Vec3b>(i, j)[2] = buffer_[i * width + j].r;
                }
            }

            cv::flip(*img, *img, 0);

        }
    }

    void get_depth(const astra::DepthFrame &depthFrame,
                   const astra::CoordinateMapper &mapper, shared_ptr<cv::Mat> &depthMat) {
        if (depthFrame.is_valid()) {
            int width = depthFrame.width();
            int height = depthFrame.height();
            int frameIndex = depthFrame.frame_index();

            //determine if buffer needs to be reallocated
            if (width != lastWidth_depth_ || height != lastHeight_depth_) {
                buffer_depth_ = buffer_depth_ptr(new int16_t[depthFrame.length()]);
                lastWidth_depth_ = width;
                lastHeight_depth_ = height;

            }
            depthFrame.copy_to(buffer_depth_.get());

//            float x = width / 2.0f + 10;
//            float y = height / 2.0f + 10;
//            size_t index = width * y + x;
//            short middle = buffer_depth_[index];

//            float worldX, worldY, worldZ;
//            float depthX, depthY, depthZ;
//            mapper.convert_depth_to_world(x, y, middle, worldX, worldY, worldZ);
//            mapper.convert_depth_to_world(0, 0, middle, worldX, worldY, worldZ);
//            mapper.convert_world_to_depth(worldX, worldY, worldZ, depthX, depthY, depthZ);


            // buffer_depth_ptr 中astra::int16_t[]数据类型转成Mat
            depthMat = std::make_shared<cv::Mat>(height, width, CV_32FC1, cv::Scalar::all(0));
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    short depth = buffer_depth_[i * width + j];
                    if (fpclassify(depth) == FP_INFINITE || fpclassify(depth) == NAN) {
                        depth = 0;
                    }
                    depthMat->at<float>(i, j) = depth;
                }
            }

        }
    }
};

SampleFrameListener listener;
astra::StreamReader reader;

int AstraCamera::start(bool getColor, bool getDepth) {


    //初始化库
    astra::initialize();

    set_key_handler();
    astra::StreamSet streamSet;
    reader = streamSet.create_reader();

    if (getColor) {
        // 配置并启动Color数据流
        astra::ColorStream colorStream = reader.stream<astra::ColorStream>();
        astra::ImageStreamMode colorMode;
        colorMode.set_width(1280);
        colorMode.set_height(720);
        colorMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
        colorMode.set_fps(30);
        colorStream.set_mode(colorMode);
        colorStream.start();
        std::cout << "colorStream -- hFov: " << colorStream.hFov() << " vFov: " << colorStream.vFov() << std::endl;
    }


    if (getDepth) {
        // 配置并启动Depth数据流
        auto depthStream = reader.stream<astra::DepthStream>();
        astra::ImageStreamMode depthMode;
        depthMode.set_width(640);
        depthMode.set_height(480);
        depthMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
        depthMode.set_fps(30);
        depthStream.set_mode(depthMode);
        depthStream.start();

        char serialnumber[256];
        depthStream.serial_number(serialnumber, 256);

        const astra_conversion_cache_t &data = depthStream.depth_to_world_data();

        //16082610454
        // conversion_data.xz: 1.12213 conversion_data.yz: 0.8416 conversion_data.hX: 320 conversion_data.hY: 240 - ty
        std::cout << "depthStream --"
                     " hFov: " << depthStream.hFov() << " vFov: " << depthStream.vFov() <<
                  " serial number: " << serialnumber <<
                  " serial number[0]: " << serialnumber[0] <<
                  " conversion_data.xz: " << data.xzFactor <<
                  " conversion_data.yz: " << data.yzFactor <<
                  " conversion_data.hX: " << data.halfResX <<
                  " conversion_data.hY: " << data.halfResY <<
                  std::endl;

    }


    //监听摄像头画面
    reader.add_listener(listener);

    // 循环更新数据
    do {
        astra_update();
    } while (shouldContinue);

    // 移除数据监听
    reader.remove_listener(listener);
    astra::terminate();
    return 0;
}

void AstraCamera::setListener(function<void(cv::Mat &, cv::Mat &)> lis) {
    astra_data_callback = lis;
}

void AstraCamera::release() {
    shouldContinue = false;
}

AstraCamera::~AstraCamera() {
    shouldContinue = false;
}
