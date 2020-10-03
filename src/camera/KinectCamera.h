//
// Created by ty on 20-9-26.
//

#ifndef HANDEYECALIBRATION_KINECTCAMERA_H
#define HANDEYECALIBRATION_KINECTCAMERA_H


#include <iostream>
#include <opencv2/opencv.hpp>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/frame_listener_impl.h>

using namespace std;
using namespace cv;


class KinectCamera {

private:
    int status = -2; // -2 初始状态， -1 出现错误， 0 正常可用

    // 1. 初始化Kinect2相机对象
    libfreenect2::Freenect2 freenect2;

    libfreenect2::Freenect2Device *device = nullptr;

    libfreenect2::SyncMultiFrameListener listener;

    libfreenect2::FrameMap frames;

public:
    KinectCamera(): listener(libfreenect2::Frame::Color | libfreenect2::Frame::Depth) {
        status = init();
    }

    virtual ~KinectCamera();

    // 判断设备是否开启
    bool isOpened() {
        return status == 0;
    }

    virtual int init();

    virtual void release();

    void capture(Mat& colorMat);

    void capture(Mat& colorMat, Mat& depthMat);
};


#endif //HANDEYECALIBRATION_KINECTCAMERA_H
