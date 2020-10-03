add_library(kinect_camera KinectCamera.cpp KinectCamera.h)
target_link_libraries(kinect_camera ${OpenCV_LIBRARIES} ${freenect2_LIBRARIES})

set(ASTRA_CAMERA_SOURCES AstraCamera.cpp AstraCamera.h)

add_library(astra_camera ${ASTRA_CAMERA_SOURCES} )
target_link_libraries(astra_camera ${ASTRA_LIBRARIES})

add_executable(AstraMain AstraMain.cpp )
target_link_libraries(AstraMain ${ASTRA_LIBRARIES} ${OpenCV_LIBRARIES} astra_camera)
