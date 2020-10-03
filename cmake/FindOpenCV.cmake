
# once done, this will define
#OpenCV_FOUND        -  whether there is OpenCV in the prebuilt libraries
#OpenCV_INCLUDE_DIRS -  include directories for OpenCV
#OpenCV_LIBRARY_DIRS -  library directories for OpenCV
#OpenCV_LIBRARIES    -  link this to use OpenCV

# 库在本地时
#set(OpenCV_DIR ~/3rdparty/OpenCV-3.4.9)
#库在项目中
set(OpenCV_DIR ${PREBUILD_DIR}/OpenCV-3.4.9)


unset(OpenCV_FOUND)

MESSAGE(STATUS "OpenCV_DIR TEST  ${PREBUILT_DIR}")

set(OpenCV_INCLUDE_DIRS "${OpenCV_DIR}/include" "${OpenCV_DIR}/include/opencv")
set(OpenCV_LIB_COMPONENTS opencv_core;opencv_ml;opencv_calib3d;opencv_highgui;opencv_superres;opencv_photo;
        opencv_imgcodecs;opencv_features2d;opencv_viz;opencv_flann;opencv_shape;opencv_stitching;opencv_dnn;
        opencv_videostab;opencv_imgproc;opencv_objdetect;opencv_video;opencv_videoio;opencv_reg;opencv_aruco;
        opencv_dpm;opencv_xobjdetect;opencv_xfeatures2d;opencv_surface_matching;opencv_plot;opencv_hfs;
        opencv_tracking;opencv_rgbd;opencv_text;opencv_dnn_objdetect;opencv_face;opencv_optflow;opencv_bgsegm;
        opencv_bioinspired;opencv_ximgproc;opencv_saliency;opencv_freetype;opencv_stereo;opencv_img_hash;
        opencv_fuzzy;opencv_ccalib;opencv_line_descriptor;opencv_hdf;opencv_datasets;opencv_phase_unwrapping;
        opencv_xphoto;opencv_structured_light)

find_path(OpenCV_INCLUDE_DIRS NAMES opencv.h HINTS ${OpenCV_DIR}/include NO_SYSTEM_ENVIRONMENT_PATH)

set(OpenCV_LIBRARY_DIRS ${OpenCV_DIR}/lib)

FOREACH(cvcomponent ${OpenCV_LIB_COMPONENTS})
  find_library(lib_${cvcomponent} NAMES ${cvcomponent} HINTS ${OpenCV_DIR}/lib NO_DEFAULT_PATH)

  set(OpenCV_LIBRARIES ${OpenCV_LIBRARIES};${lib_${cvcomponent}})
ENDFOREACH()

set(OpenCV_LIBS ${OpenCV_LIBRARIES})

set(OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS};${OpenCV_INCLUDE_DIRS}/opencv)

if (OpenCV_INCLUDE_DIRS AND OpenCV_LIBRARIES)
  set(OpenCV_FOUND TRUE)
endif (OpenCV_INCLUDE_DIRS AND OpenCV_LIBRARIES)

if (OpenCV_FOUND)
  if (NOT OpenCV_FIND_QUIETLY)
    message(STATUS "Found OpenCV: ${OpenCV_LIBRARIES}")
  endif (NOT OpenCV_FIND_QUIETLY)
else(OpenCV_FOUND)
  if (OpenCV_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find the OpenCV library")
  endif ()
endif (OpenCV_FOUND)
