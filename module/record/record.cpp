/**
 * @file record.cpp
 * @author SMS (2436210442@qq.com)
 * @brief 视频保存
 * @date 2021-08-28
 * @copyright Copyright (c) 2021 GUCROBOT_WOLF
 *
 */
#include "record.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <string>
#include <ctime>
#include <chrono>
#include<fstream>
namespace RecordMode {
Record::Record(){}
Record::Record(std::string path_in, cv::Size size) : capture(0), mv_capture_(mindvision::CameraParam(0, mindvision::RESOLUTION_1280_X_800, mindvision::EXPOSURE_600)) {
  //video_save_path_ = path_input;
  //printf(CONFIG_FILE_PATH);
  std::string out_path =path_in + std::to_string(Record::getFileSizeInOrder(path_in)) + ".avi";  //目标路径                                                                                //要求与摄像头参数一致
  // int fourcc = writer.fourcc('X', 'V', 'I', 'D');   // 设置avi文件对应的编码格式 66 67
  int fourcc = writer.fourcc('M', 'J', 'P', 'G');  // 33 30 48Flv1
  writer.open(out_path, fourcc, 66, size, true);   //CAP_DSHOW = true
  if (writer.isOpened()) {
    std::cout << "正在录制" << std::endl;
  } else {
    std::cout << "录制失败" << std::endl;
  }
}

void Record::Run(cv::Mat cap) {
  //get Image
  // if (cap->isindustryimgInput()) {
  //   src_img = cv::cvarrToMat(cap->iplImage, true);  //这里只是进行指针转换，将IplImage转换成Mat类型
  // } else {
  //   capture >> src_img;
  // }
  //imshow("src_img", src_img);
  writer << cap;

  // cap->cameraReleasebuff();
}
int Record::getFileSizeInOrder(const std::string& path) {
  std::string filename;
  std::string format = ".avi";  //avi
    while (true) {
      filename = path + std::to_string(path_) + format;
      std::fstream file_;
      file_.open(filename, std::ios::in);
      if (!file_) {
        break;
      }
      path_++;
    }
   return path_;
}
// 
void Record::close(std::string path_in, cv::Mat src_img) {
  writer.release();
  std::string out_path = path_in + std::to_string(Record::getFileSizeInOrder(path_in)) + ".avi";           //目标路径
  cv::Size  size(1280, 800);                                                                           //要求与摄像头参数一致
  // int fourcc = writer.fourcc('X', 'V', 'I', 'D');   // 设置avi文件对应的编码格式 66 67
  int fourcc = writer.fourcc('M', 'J', 'P', 'G');  // 33 30 48Flv1
  writer.open(out_path, fourcc, 66, size, true);   //CAP_DSHOW = true
  if (writer.isOpened()) {
    std::cout << "正在录制" << std::endl;
  } else {
    std::cout << "录制失败" << std::endl;
  }
  writer << src_img;
}
Record::~Record() {
  writer.release();
}

}  // namespace RecordMode
