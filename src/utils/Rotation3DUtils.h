//
// Created by ty on 20-6-30.
//

#ifndef CALIBRATIONHANDEYE_ROTATION3DUTILS_H
#define CALIBRATIONHANDEYE_ROTATION3DUTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 * 检查是否是旋转矩阵
 *
 * 齐次正交矩阵
 * 矩阵的转置T 等于 矩阵的逆inv
**/
bool isRotationMatrix(Mat &R) {
    Mat Rt;
    transpose(R, Rt);
    // 应该得到单位矩阵
    Mat shouldBeIdentity = Rt * R;
    Mat I = Mat::eye(3, 3, shouldBeIdentity.type());

    return norm(I, shouldBeIdentity) < 1e-6;
}

/**
 * 将旋转矩阵和平移向量转成4x4的齐次变换矩阵
 * @param rotationMat    旋转矩阵
 * @param translationMat 平移向量
 * @return 齐次变换矩阵
 */
static Mat toHomogeneousMat(const Mat &rotationMat, const Mat &translationMat){
    Mat m = Mat::eye(4, 4, CV_64FC1); // rotationMat.type()

    Mat R = m(Rect(0, 0, 3, 3));
    rotationMat.convertTo(R, CV_64F);

    Mat t = m(Rect(3, 0, 1, 3));
    translationMat.convertTo(t, CV_64F);
    return m;
}

/**
 * 求齐次矩阵的逆矩阵
 * @param T
 * @return
 */
static Mat homogeneousInverse(const Mat &T) {
    CV_Assert(T.rows == 4 && T.cols == 4);

    Mat R = T(Rect(0, 0, 3, 3));
    Mat t = T(Rect(3, 0, 1, 3));

    Mat Rt = R.t();
    Mat tinv = -Rt * t;

    Mat Tinv = Mat::eye(4, 4, T.type());

    Rt.copyTo(Tinv(Rect(0, 0, 3, 3)));
    tinv.copyTo(Tinv(Rect(3, 0, 1, 3)));

    return Tinv;
}

/**
 * 取出齐次变换矩阵的旋转矩阵和平移向量
 * @param T 4x4变换矩阵
 * @param outputRotation 旋转矩阵
 * @param outputTranslation 平移向量
 */
static void splitHomogeneousMat(Mat &T, Mat& outputRotation, Mat& outputTranslation){
    CV_Assert(T.rows == 4 && T.cols == 4);

    Mat R = T(Rect(0, 0, 3, 3));
    Mat t = T(Rect(3, 0, 1, 3));

    R.copyTo(outputRotation);
    t.copyTo(outputTranslation);
};

/**
 * 欧拉角转旋转矩阵
 * @param theta
 * @return
 */
Mat eulerAnglesToRotationMatrix(cv::Vec3f &theta){

    // X轴旋转矩阵
    Mat R_x = (Mat_<double>(3, 3) <<
            1, 0, 0,
            0, cos(theta[0]), -sin(theta[0]),
            0, sin(theta[0]), cos(theta[0])  );
    // Y轴旋转矩阵
    Mat R_y = (Mat_<double>(3, 3) <<
            cos(theta[1]), 0, sin(theta[1]),
            0, 1, 0,
            -sin(theta[1]), 0, cos(theta[1]));
    // Z轴旋转矩阵
    Mat R_z = (Mat_<double>(3, 3) <<
            cos(theta[2]), -sin(theta[2]), 0,
            sin(theta[2]), cos(theta[2]) , 0,
            0, 0, 1
    );

    Mat R = R_z * R_y * R_x;
    return R;
}
/**
 * 将旋转矩阵转成欧拉角
 * @param R 旋转矩阵
 * @return  欧拉角
 */
Vec3f rotationMatrixToEulerAngles(cv::Mat &R){
    assert(isRotationMatrix(R));

    float sy = sqrt(R.at<double>(0, 0) * R.at<double>(0, 0) + R.at<double>(1, 0) * R.at<double>(1, 0));

    bool singular = sy < 1e-6; // If

    float x, y, z;
    if (!singular) {
        x = atan2(R.at<double>(2, 1), R.at<double>(2, 2));
        y = atan2(-R.at<double>(2, 0), sy);
        z = atan2(R.at<double>(1, 0), R.at<double>(0, 0));
    } else {
        x = atan2(-R.at<double>(1, 2), R.at<double>(1, 1));
        y = atan2(-R.at<double>(2, 0), sy);
        z = 0;
    }
    return Vec3f(x, y, z);
};

#endif //CALIBRATIONHANDEYE_ROTATION3DUTILS_H
