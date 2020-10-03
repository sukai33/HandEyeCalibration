//
// Created by ty on 20-9-26.
//

#include "KinectCamera.h"


int KinectCamera::init() {


    // 判断已连接的设备个数
    if (freenect2.enumerateDevices() == 0) {
        std::cerr << "未发现Kinect2设备" << std::endl;
        return -1;
    }

    const string &serial = freenect2.getDefaultDeviceSerialNumber();

    if (serial.empty()) {
        std::cerr << "设备序列号不存在" << std::endl;
        return -1;
    }

    std::cout << "设备序列号: " << serial << std::endl;

    // 创建pipeline接收并处理数据
//    auto *pipeline = new libfreenect2::CpuPacketPipeline();
    auto pipeline = new libfreenect2::OpenGLPacketPipeline();

    // 根据序列号开启设备，并设定数据处理通道
    device = freenect2.openDevice(serial, pipeline);

    // 创建数据接收器（监听器），给设备执行监听;
    device->setColorFrameListener(&listener);
    device->setIrAndDepthFrameListener(&listener);

    device->start();

    return 0;
}

void KinectCamera::capture(Mat& outputMat) {

    listener.waitForNewFrame(frames);

    libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
    libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];

    Mat colorMat = Mat(rgb->height, rgb->width, CV_8UC4, rgb->data);
    // 图像进行镜像处理
    flip(colorMat, colorMat, 1);

    colorMat.copyTo(outputMat);

    listener.release(frames);

}


void KinectCamera::release() {
    device->stop();
    device->close();
}

KinectCamera::~KinectCamera() {

}


