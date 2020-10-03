# 查找依赖库
# 头文件include: freenect2_INCLUDE_DIRS
# 依赖库：       freenect2_LIBRARIES

# 库在本地时
#FIND_LIBRARY(freenect2_LIBRARY freenect2
#        PATHS ~/freenect2/lib
#        NO_DEFAULT_PATH
#        )

#库在项目中
FIND_LIBRARY(freenect2_LIBRARY freenect2
        PATHS ${PREBUILD_DIR}/freenect2/lib
        NO_DEFAULT_PATH
        )
SET(freenect2_LIBRARIES ${freenect2_LIBRARY} pthread)

# 查找路径
FIND_PATH(freenect2_INCLUDE_DIR libfreenect2/libfreenect2.hpp
        PATHS ~/freenect2/include
        NO_DEFAULT_PATH
        )
SET(freenect2_INCLUDE_DIRS ${freenect2_INCLUDE_DIR})
