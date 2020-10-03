//
// Created by ty on 20-9-27.
//


#include <iostream>
#include <vector>
#include <XmlUtil.h>

using namespace std;

//char *extrinsic_param_path = "./extrinsic_param.xml";
char *extrinsic_param_path = "./extrinsic_param_hand_to_eye_refer.xml";


/**
 * 
 */
int main(int argc, char *argv[]) {
    vector<Extrinsic> exts = readXml(extrinsic_param_path);

    char *extrinsic_output_param_path = "./extrinsic_param_hand_to_eye__.xml";
    for (auto & ext : exts) {
        std::cout << "image: " << ext.image_path << std::endl;
    }

//    writeXml(exts, extrinsic_output_param_path);

}





















