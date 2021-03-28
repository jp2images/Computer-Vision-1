#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp"

using namespace std;
using namespace cv;

void quickShow(cv::Mat, std::string);

int main() {
    string imageName = DATA_PATH + "images/dilation_example.jpg";
    string sourceWindow = "Source Image";
    string dilatedImageWindow = "Dilated Image";
    string erodedImageWindow = "Eroded Image";

    cv::Mat source = cv::imread(imageName, IMREAD_COLOR);

    cv::namedWindow(sourceWindow, cv::WINDOW_AUTOSIZE);
    quickShow(source, sourceWindow);

    int kernelSize = 7;
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(kernelSize, kernelSize));

    cv::Mat imageDilated;
    cv::dilate(source, imageDilated, kernel1); //iterations is 1 from a default parameter.
    quickShow(imageDilated, "Dilated Image");

    kernelSize = 3;
    cv::Mat kernel2 = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(kernelSize, kernelSize));
    //quickShow(kernel2*255, "Kernel 2"); //Multiply by 255 to make the kernel white

    cv::Mat imageDilated1, imageDilated2;
    cv::dilate(source, imageDilated1, kernel2, cv::Point(-1, -1), -1); //one iteration
    cv::dilate(source, imageDilated2, kernel2, cv::Point(-1, -1), 2); // 2 iterations
    quickShow(imageDilated1, "First Dilation 1 iteration");
    quickShow(imageDilated2, "Second Dilation 2 iterations");


    //Erosion
    imageName = DATA_PATH + "images/erosion_example.jpg";
    source = cv::imread(imageName, cv::IMREAD_COLOR);
    quickShow(source, "Source Image Erode");

    cv::Mat imageEroded;
    cv::erode(source, imageEroded, kernel1);
    quickShow(imageEroded, "Eroded image");

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}

void quickShow(cv::Mat source, std::string windowName) {
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, source);
}
