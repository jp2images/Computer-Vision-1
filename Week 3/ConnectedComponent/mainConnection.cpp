
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp> //imwrite
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    cv::Mat img = cv::imread(DATA_PATH + "images/truth.png", IMREAD_GRAYSCALE);
    cv::imshow("Starting Image", img);
    cv::waitKey(0);
    
    cv::Mat imThresh;
    cv::threshold(img, imThresh, 127, 255, cv::THRESH_BINARY);

    cv::Mat imLabels;
    int ncomponents = cv::connectedComponents(imThresh, imLabels);
    cv::Mat imLabelsCopy = imLabels.clone();

    cv::Point minLoc, maxLoc;
    double minVal, maxVal;

    //find the min and max pixel values and their location in an image
    cv::minMaxLoc(imLabels, &minVal, &maxVal, &minLoc, &maxLoc);

    //normalize the image so min is 0 and max is 255
    imLabels = 255 * (imLabels - minVal) / (maxVal - minVal);

    //then convert the image to 8 bits
    imLabels.convertTo(imLabels, CV_8U);

    //each label is a different color/gray scale
    cv::imshow("display labeded image", imLabels);
    cv::waitKey(0);

    imLabels = imLabelsCopy.clone();
    cout << endl << endl << "Number of components: " << ncomponents << endl << endl;

    //Each of the imLabels
    for (int x = 0; x < ncomponents; x++) {
        cv::imshow("Compenent #" + x, imLabels == x);        
    }

    double minValue2, maxValue2;
    cv::minMaxLoc(imLabels, &minValue2, &maxValue2, &minLoc, &maxLoc);

    //normalize the image to values between 0 and 255
    imLabels = 255 * (imLabels - minValue2) / (maxValue2 - minValue2);
    imLabels.convertTo(imLabels, CV_8U);
    cv::Mat colorMap;
    cv::applyColorMap(imLabels, colorMap, cv::COLORMAP_JET);
    cv::imshow("Color Map", colorMap);

    ncomponents = cv::connectedComponents(imThresh, imLabels);
    cout << endl << endl << "Number of color components: " << ncomponents << endl << endl;
    cv::waitKey(0);

    return 0;
}
