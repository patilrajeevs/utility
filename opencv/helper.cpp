#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

class OpencvHelper{

  public:  
    static void display(const Mat &image, string window_name = "Display window"){
      namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
      imshow("Display window", image);
      waitKey(0);
    }

    static void display_file(const string &path){
	    Mat image = imread(path);
	    display(image, path);
    }

    static Mat convertColor(const Mat &image, int code){
      Mat dest_image;
      cvtColor(image, dest_image, code);
      return dest_image;
    }

    static Mat convertToGrayScale(const Mat &image){
      return convertColor(image, CV_BGR2GRAY);
    }

    static Mat gaussianBlur(const Mat &image_source, int kernel_height, int kernel_width,  double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT){
      Mat dest_image;
      Size kernel = Size(kernel_height, kernel_width);
      GaussianBlur(image_source, dest_image, kernel, sigmaX, sigmaY, borderType);
      return dest_image;
    }
    static Mat canny_edge(const Mat &image_source, int lowThreshold, int ratio){
      Mat dest_image;
      Canny(image_source, dest_image, lowThreshold, lowThreshold*ratio);
      return dest_image;
    }

    static vector<Vec4i> GetHoughLines(const Mat & image, double rho, double theta, int threshold, double minLineLength,\
       double maxLineGap, bool display = false){
      vector<Vec4i> lines;
      HoughLinesP(image, lines, rho, theta, threshold, minLineLength, maxLineGap);

      if (display){
        Mat display_image;
        cvtColor( image, display_image, CV_GRAY2BGR );
				for( size_t i = 0; i < lines.size(); i++ )
				{
						line( display_image, Point(lines[i][0], lines[i][1]),
								Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
						namedWindow( "Hough_lines_on_image", 1 );
						imshow("Hough_lines_on_image", image );
				}
        OpencvHelper::display(display_image);
      }
      return lines;
    }

    static Mat getRoI(const Mat &image,vector <vector<Point> > pts){
      Mat dest;
      Mat mask(image.size(), image.type(), Scalar(0,0,0));
      fillPoly(mask, pts, Scalar(255,255,255));
      bitwise_and(image, mask, dest);
      return dest;
    }
};
