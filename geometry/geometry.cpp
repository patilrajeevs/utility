#include "geometry.h"

using namespace cv;
using namespace std;

Line::Line(){}

Line::Line(float x1, float y1, float x2, float y2){
    px1 = x1;
    py1 = y1;
    px2 = x2;
    py2 = y2;
}

Line::Line(Vec4i points){
    px1 = points[0];
    px2 = points[2];
    py1 = points[1];
    py2 = points[3];
    init();
}

void Line::init(){
    if (abs((py2-py1)) < 0.001){
        cout << "Extremely high slope. setting to NAN";
        vertical_line = true;
    }else{
        //slope = y2-y1/x2-x1
        slope = (py2-py1)/(px2-px1);
        // y = mx + c; so, c = y - mx
        intercept = py2 - slope* px2;
        vertical_line = false;
    }
    length = sqrt((py2-py1)*(py2-py1) + (px2-px1)*(px2-px1));
}

float Line::GetXInterceptAt(float y){
    if (slope != NAN && intercept != NAN){
        return (y - intercept)/slope; 
    }else{
        return NAN;
    }
}

void Geometry::GroupLinesBySlopeIntercept(vector <Line> lines, map <int, vector <Line> > &line_group, int no_of_groups){
    vector<Vec2f> s_i;
    Mat labels, centers;
    for (vector<Line>::iterator it = lines.begin() ; it != lines.end(); ++it){
        Vec2f temp((*it).slope, (*it).intercept);
        s_i.push_back(temp);
    }
    kmeans(s_i, 2, labels,   TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0), 10, KMEANS_RANDOM_CENTERS, centers);
    for (int i=0; i<s_i.size();i++){
        line_group[labels.at<int>(i)].push_back(lines[i]);
    }
}
Line SumOfLine(Line line1, Line line2){
    Line l1 = line1;
    if (isnan(line1.slope) || isnan(line1.intercept)){
        l1.slope = line2.slope;
        l1.intercept = line2.intercept;
    }else{
        l1.slope = l1.slope + line2.slope;
        l1.intercept = l1.intercept + line2.intercept;
    }
    return l1;
}
Line Geometry::AverageLines(vector <Line> lines){
    Line average_line(0,0,0,0);
    for(vector<Line>::iterator it = lines.begin(); it != lines.end(); ++it){
        average_line = SumOfLine(average_line, *it);
    }
    average_line.slope = average_line.slope/lines.size();
    average_line.intercept = average_line.intercept/lines.size();
    return average_line;
}
