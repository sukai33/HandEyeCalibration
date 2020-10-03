//
// Created by ty on 20-9-27.
//

#ifndef HANDEYECALIBRATION_XMLUTIL_H
#define HANDEYECALIBRATION_XMLUTIL_H


#include <tinyxml2.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace tinyxml2;

typedef struct {

    std::string image_path; // 保存图片路径

    double joints[6]; // 保存关节角信息

    double pose[6];   // 保存位姿数据

} Extrinsic;

vector<Extrinsic> readXml(char* extrinsic_param_path) {// 读取xml
    XMLDocument doc;
    doc.LoadFile(extrinsic_param_path);
    XMLElement *root = doc.RootElement();

    XMLElement *child = root->FirstChildElement("extrinsic");

    vector<Extrinsic> exts;

//    int counter = 0;

    while (child) {
        const char *image_path = child->FirstChildElement("Limage_color_path")->GetText();

        double joint1 = atof(child->FirstChildElement("joint1")->GetText());
        double joint2 = atof(child->FirstChildElement("joint2")->GetText());
        double joint3 = atof(child->FirstChildElement("joint3")->GetText());
        double joint4 = atof(child->FirstChildElement("joint4")->GetText());
        double joint5 = atof(child->FirstChildElement("joint5")->GetText());
        double joint6 = atof(child->FirstChildElement("joint6")->GetText());

        double pose1 = atof(child->FirstChildElement("pose1")->GetText());
        double pose2 = atof(child->FirstChildElement("pose2")->GetText());
        double pose3 = atof(child->FirstChildElement("pose3")->GetText());
        double pose4 = atof(child->FirstChildElement("pose4")->GetText());
        double pose5 = atof(child->FirstChildElement("pose5")->GetText());
        double pose6 = atof(child->FirstChildElement("pose6")->GetText());

//        std::cout << "image_path: " << image_path << " joint1: " << joint1 << std::endl;
        exts.push_back((Extrinsic) {
                std::string(image_path),
                {joint1, joint2, joint3, joint4, joint5, joint6},
                {pose1, pose2, pose3, pose4, pose5, pose6},
        });

        child = child->NextSiblingElement();

//        counter++;
//        if (counter == 5) {
//            break;
//        }
    }

    doc.Clear();
    return exts;
}

void writeXml(vector<Extrinsic> &exts, char *extrinsic_output_param_path) {// 写出xml
    XMLDocument *doc = new XMLDocument();

    XMLDeclaration *declaration = doc->NewDeclaration(R"(xml version="1.0" encoding="UTF-8" standalone="yes")");
    doc->InsertEndChild(declaration);

    XMLElement *root = doc->NewElement("ExtrinsicParams");
    doc->InsertEndChild(root);

    // 向root中添加数据
    unsigned long size = exts.size();
    for (int i = 0; i < size; ++i) {
        Extrinsic &ext = exts[i];
        // 创建子元素并添加给root
        XMLElement *child = doc->NewElement("extrinsic");
        child->SetAttribute("name", i + 1);
        root->InsertEndChild(child);

        // 图片路径
        XMLElement *imageElement = doc->NewElement("Limage_color_path");
        imageElement->SetText(ext.image_path.c_str());
        child->InsertEndChild(imageElement);

        // 关节角
        for (int j = 0; j < 6; ++j) {
            double joint = ext.joints[j];
            XMLElement *jointEle = doc->NewElement(("joint" + to_string(j + 1)).c_str());
            jointEle->SetText(joint);
            child->InsertEndChild(jointEle);
        }

        // 位姿
        for (int j = 0; j < 6; ++j) {
            double pose = ext.pose[j];
            XMLElement *poseEle = doc->NewElement(("pose" + to_string(j + 1)).c_str());
            poseEle->SetText(pose);
            child->InsertEndChild(poseEle);
        }
    }

    XMLError error = doc->SaveFile(extrinsic_output_param_path);
    if (error == XML_SUCCESS) {
        cout << "写出成功！" << endl;
    } else {
        cerr << "写出失败：" << error << endl;
    }

    doc->Clear();
}

#endif //HANDEYECALIBRATION_XMLUTIL_H
