#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string path = "./images";
    int index = 3;
    std::cout << printf("%s/image_%d.jpg", path.c_str(), index) << std::endl;
    return 0;
}