#ifndef OPENCVHELPER_H
#define OPENCVHELPER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <cv.h>
//#include <highgui.hpp>

#include <iostream>
#include <string>
#include <vector>
#include "geometry_helper.h"

using namespace std;
using namespace cv;

class OpencvHelper{
public:
    static void display(const Mat &image, string window_name = "Display window");
    void display_temp();
    static void display_file(const string &path);
    static Mat convertColor(const Mat &image, int code);
    static Mat convertToGrayScale(const Mat &image);
    static Mat gaussianBlur(const Mat &image_source, int kernel_height, int kernel_width,  double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
    static Mat canny_edge(const Mat &image_source, int lowThreshold, int ratio);
    static vector<Vec4i> GetHoughLines(const Mat & image, double rho, double theta, int threshold, double minLineLength,double maxLineGap, bool display = false);
    static Mat getRoI(const Mat &image,vector <vector<Point> > pts);
    static vector <vector<Vec4i> > grouplines(const vector<Vec4i> &lines, int no_groups);
};

#endif
