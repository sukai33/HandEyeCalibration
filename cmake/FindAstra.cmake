set(Astra_DIR ${PREBUILD_DIR}/astra)

# 声明头文件h所在目录
set(ASTRA_INCLUDE_DIRS ${Astra_DIR}/include)

# 声明so库文件所在目录
set(ASTRA_LINK_DIRS ${Astra_DIR}/lib)

# libastra.so, libastra_core.so ...
set(ASTRA_LIBRARIES astra;astra_core;astra_core_api;pthread)
