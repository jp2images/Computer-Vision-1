
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "dataPath.hpp"

using namespace std;
using namespace cv;

int maxScale = 100;
int scaleFactor = 0;
int scaleType = 0;
int maxType = 1;
string windowName = "Resize the Image";
string trackbarValue = "Scale";
string trackbarType = "Up/Down";

cv::Mat source;

const int ESC_KEY = 27;

void scaleImage(int, void*);


int main() {

    //read in the image
    source = cv::imread(DATA_PATH + "truth.png");
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::createTrackbar(trackbarValue, windowName, &scaleFactor, maxScale, scaleImage);
    cv::createTrackbar(trackbarType, windowName, &scaleType, maxType, scaleImage);

    scaleImage(25, 0);

    while (true) {
        int c;
        c = cv::waitKey(20);
        if (static_cast<char>(c) == 27) break;
    }

    return 0;
}

void scaleImage(int, void*) {
    double scaleFactorDouble;

    cv::Mat scaledImage;
    if (scaleType == 0) {
        scaleFactorDouble = 1 + scaleFactor / 100.0;
    }
    else {
        scaleFactorDouble = 1 - scaleFactor / 100.0;
    }

    if (scaleFactorDouble == 0) {
        scaleFactorDouble = 1;
    }

    cv::resize(source, scaledImage, cv::Size(), scaleFactorDouble, scaleFactorDouble, cv::INTER_LINEAR);
    cv::imshow(windowName, scaledImage);
}
