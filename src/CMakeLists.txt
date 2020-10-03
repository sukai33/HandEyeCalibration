include_directories(./camera)
include_directories(./robot)
include_directories(./tinyxml)
include_directories(./utils)

add_executable(CameraIntrinsicCalibration CameraIntrinsicCalibration.cpp)
target_link_libraries(CameraIntrinsicCalibration ${OpenCV_LIBRARIES} ${freenect2_LIBRARIES})

#MESSAGE(STATUS freenect2_LIBRARIES: ${freenect2_LIBRARIES})

add_executable(CameraIntrinsicCalibration2 CameraIntrinsicCalibration2.cpp)
target_link_libraries(CameraIntrinsicCalibration2 ${OpenCV_LIBRARIES} ${freenect2_LIBRARIES} kinect_camera)

add_executable(CameraIntrinsicFromFiles CameraIntrinsicFromFiles.cpp)
target_link_libraries(CameraIntrinsicFromFiles ${OpenCV_LIBRARIES})


#-------------------------------------------------------- 眼在手外
add_executable(HandToEyeCapture HandToEyeCapture.cpp)
target_link_libraries(HandToEyeCapture kinect_camera aubo tinyxml)
add_executable(HandToEyeCaptureAuto HandToEyeCaptureAuto.cpp)
target_link_libraries(HandToEyeCaptureAuto kinect_camera aubo tinyxml)
add_executable(HandToEyeCalibration HandToEyeCalibration.cpp)
target_link_libraries(HandToEyeCalibration ${OpenCV_LIBRARIES} tinyxml util)
add_executable(HandToEyeVerify HandToEyeVerify.cpp)
target_link_libraries(HandToEyeVerify ${OpenCV_LIBRARIES} kinect_camera aubo tinyxml util)
add_executable(HandToEyeVerify2 HandToEyeVerify2.cpp)
target_link_libraries(HandToEyeVerify2 ${OpenCV_LIBRARIES} kinect_camera aubo tinyxml util)

#-------------------------------------------------------- 眼在手上
add_executable(HandInEyeCapture HandInEyeCapture.cpp)
target_link_libraries(HandInEyeCapture ${OpenCV_LIBRARIES} astra_camera aubo tinyxml)
add_executable(HandInEyeCaptureAuto HandInEyeCaptureAuto.cpp)
target_link_libraries(HandInEyeCaptureAuto ${OpenCV_LIBRARIES} astra_camera aubo tinyxml)
add_executable(HandInEyeCalibration HandInEyeCalibration.cpp)
target_link_libraries(HandInEyeCalibration ${OpenCV_LIBRARIES} tinyxml util)
add_executable(HandInEyeVerify2 HandInEyeVerify2.cpp)
target_link_libraries(HandInEyeVerify2 ${OpenCV_LIBRARIES} astra_camera aubo tinyxml util)