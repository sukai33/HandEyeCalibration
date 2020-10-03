# 眼在手外相机标定

- Kinect2相机眼在手外标定 aubo机械臂
    - CameraIntrinsicCalibration.cpp 内参标定
    - CameraIntrinsicCalibration2.cpp 内参标定
    - CameraIntrinsicFromFiles.cpp 内参标定写出数据
    - HandToEyeCapture.cpp 数据采集保存图片及机械臂关节参数,方便HandToEyeCaptureAuto自动标定
    - HandToEyeCalibration.cpp 眼在手外的机械臂外参标定
    - HandToEyeCaptureAuto.cpp 眼在手外的机械臂自动标定
    - HandToEyeVerify.cpp  眼在手外的标定验证
    - HandToEyeVerify2.cpp 眼在手外的标定验证
- astra奥比中光相机眼在手上标定 aubo机械臂
    - HandInEyeCapture.cpp 数据采集保存图片及机械臂关节参数,方便HandInEyeCaptureAuto自动标定
    - HandInEyeCalibration.cpp 眼在手上的机械臂外参标定
    - HandInEyeCaptureAuto.cpp 眼在手上的机械臂自动标定
    - HandInEyeVerify.cpp  眼在手上外的标定验证
    - HandInEyeVerify2.cpp 眼在手上的标定验证
 
- 具体眼在手外的机械臂标定操作操作 
  - 1.先进行图片采集 HandToEyeCapture.cpp
  - 2.CameraTotrinsicFromFiles.cpp 内参标定写出数据得到内参文件 [眼在外与眼在手上同一个代码标定内参,眼在手外读的是images文件夹,眼在手上读的是images2的文件夹]
  - 3.HandToEyeCaptureAuto.cpp 眼在手外的机械臂自动外参标定 
  - 4.HandToEyeVerify2.cpp 眼在手外的标定验证
