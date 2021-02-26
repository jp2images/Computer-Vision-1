#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "dataPath.hpp"



using namespace std;
using namespace cv;

string type2str(int);

int main() {
    const string myWindow = "myWindow";
    string imagePath = "number_zero.jpg";

    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    cv::Mat testImage = cv::imread(imagePath, cv::IMREAD_COLOR);

    cout << testImage << endl << endl;
    cout << testImage.size() << endl << endl;

    cout << "Data Type = " << type2str(testImage.type()) << endl;
    
    testImage.at<Vec3b>(0, 0) = Vec3b(0, 255, 255); //At cell 0, 0 set the color B,G,R = Yellow (Mixture of red and green)
    testImage.at<Vec3b>(1, 1) = Vec3b(255, 255, 0); //At cell 1, 1 set the color B,G,R = Cyan (Mixture of blue and green)
    testImage.at<Vec3b>(2, 2) = Vec3b(255, 0, 255); //At cell 2, 2 set the color B,G,R = Magenta (Mixture of blue and red)
    cout << "Pixel at Row 0, Column 0: " << testImage.at<Vec3b>(0, 0) << endl;
    cout << "Pixel at Row 0, Column 0: " << testImage.at<Vec3b>(1, 1) << endl;
    cout << "Pixel at Row 0, Column 0: " << testImage.at<Vec3b>(2, 2) << endl << endl;
    
    testImage(cv::Range(0, 3), cv::Range(0, 3)).setTo(255, 0);

    cout << testImage << endl << endl;

    cv::namedWindow(myWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(myWindow, testImage);
    cv::waitKey(0);
    cv::destroyWindow(myWindow);


    return 0;
}

string type2str(int type) {
    string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar channels = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
    }

    r += "C";
    r += (channels + '0');

    return r;
}