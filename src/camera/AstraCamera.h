//
// Created by ty on 20-7-2.
//

#ifndef CALIBRATIONHANDEYE_ASTRACAMERA_H
#define CALIBRATIONHANDEYE_ASTRACAMERA_H

#include <astra/astra.hpp>
#include <cstdio>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace cv;

class AstraCamera {

public:
    AstraCamera();

    virtual ~AstraCamera();

public:

    virtual int start(bool getColor = true, bool getDepth = true);

    void setListener(function<void(cv::Mat&, cv::Mat&)>);

    virtual void release();

};

#endif //CALIBRATIONHANDEYE_ASTRACAMERA_H
