include_directories("../tinyxml")

add_executable(TestXml TestXml.cpp)
target_link_libraries(TestXml tinyxml)