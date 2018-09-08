#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

#include <vector>
#include <cv.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Line{
public:
    float px1,px2,py1,py2;
    float slope = NAN;
    float intercept = NAN;
    float length;
    bool vertical_line;
    Line(Vec4i points);
    Line();
    Line(float x1, float y1, float x2, float y2);
    void init();
    float GetXInterceptAt(float y);

};

class Geometry{
public:
	static void GroupLinesBySlopeIntercept(vector <Line> lines, map <int, vector <Line> > &line_group, int no_of_groups);
    static Line AverageLines(const vector <Line> lines);
};

#endif
