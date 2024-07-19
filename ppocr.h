#ifndef __PPOCR_H_
#define __PPOCR_H_
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <vector>
#include "utility.h"
using namespace PaddleOCR;

std::vector<std::vector<OCRPredictResult>> detectAll(std::vector<cv::String> &cv_all_img_names);
#endif