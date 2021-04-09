
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp> //imwrite
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
//using namespace cv;

void quickShow(cv::Mat, std::string = "Quick Show", bool = false);

int main() {
    //Assignment Part A
    //STEP 1: Read the image
    string imagePath = DATA_PATH + "images/CoinsA.png";
    cv::Mat image = cv::imread(imagePath);
    int imageWidth = image.size().width;
    int imageHeight = image.size().height;
    cout << "Image Dimensions: W" << imageWidth << " x H" << imageHeight << endl << endl;
    //quickShow(image, "Original");

    //Make a copy so we don't mess up the original
    cv::Mat imageCopy = image.clone();

    //STEP 2.1: Covert image to gray scale
    cv::Mat imageGray;
    cv::cvtColor(imageCopy, imageGray, cv::COLOR_BGR2GRAY);
    //quickShow(imageGray, "Monochrome");

    //STEP 2.2: Split the image into R,G,B channels
    cv::Mat imageB, imageG, imageR;
    cv::Mat imageChannels[3];
    cv::split(imageCopy, imageChannels);
    imageB = imageChannels[0];
    imageG = imageChannels[1];
    imageR = imageChannels[2];

    //cv::imshow("Image B", imageB);
    //cv::imshow("Image G", imageG);
    //cv::imshow("Image R", imageR);
    //cv::waitKey(0);
    //cv::destroyAllWindows();

    //STEP 3.1: Perform the Thresholding
    cv::Mat threshold70ImageGray;
    cv::threshold(imageGray, threshold70ImageGray, 70, 255, cv::THRESH_BINARY_INV);
    //quickShow(threshold70ImageGray, "Image Basic Gray Threshold 70");

    cv::Mat threshold70ImageG;
    cv::threshold(imageG, threshold70ImageG, 70, 255, cv::THRESH_BINARY_INV);
    //quickShow(threshold70ImageG, "Image Green Threshold 70");

    cv::Mat threshold70ImageBlue;
    cv::threshold(imageB, threshold70ImageBlue, 70, 255, cv::THRESH_BINARY_INV);
    //quickShow(threshold70ImageBlue, "Image Blue Threshold 70");

    //WINNER WINNER
    cv::Mat threshold60ImageG;
    cv::threshold(imageG, threshold60ImageG, 60, 255, cv::THRESH_BINARY_INV);
    quickShow(threshold60ImageG, "Image Green Threshold 60");


#pragma region Some testing outside assignment requirements
    //cv::Mat blurredImage;
    //cv::GaussianBlur(imageG, blurredImage, cv::Size(11, 11), 0.8 );
    //quickShow(blurredImage, "Image Blurred");
    
    //cv::Mat thresholdblurredImage;
    //cv::threshold(blurredImage, thresholdblurredImage, 80, 255, cv::THRESH_BINARY_INV);
    //quickShow(thresholdblurredImage, "Image Blurred Threshold");

    //cv::Mat imageMedian;
    //cv::medianBlur(imageG, imageMedian, 11);
    //quickShow(imageMedian, "Image Median Blur");

    //cv::threshold(imageMedian, thresholdblurredImage, 60, 255, cv::THRESH_BINARY_INV);
    //quickShow(thresholdblurredImage, "Image Median Blurred Threshold");
#pragma endregion

    //*************************************************************************
    //*************************************************************************
    // Morphalogical operations.
    //*************************************************************************
    //*************************************************************************
    
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    cv::Mat element2x2 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2, 2));
    cv::Mat element4x4 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(4, 4));
    cv::Mat elementEllipse = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));

    cv::Mat openingImage, openingImage2x2, openingImage4x4;
    cv::Mat closingImage, closingImage2x2, closingImage4x4;

    cv::morphologyEx(threshold60ImageG, openingImage, cv::MORPH_OPEN, element, cv::Point(-1, -1), 1);
    //quickShow(openingImage, "Image Opening se3x3", true);
    cv::morphologyEx(threshold60ImageG, openingImage2x2, cv::MORPH_OPEN, element2x2, cv::Point(-1, -1), 1);
    //quickShow(openingImage2x2, "Image Opening se2x2", true);
    cv::morphologyEx(threshold60ImageG, openingImage4x4, cv::MORPH_OPEN, element4x4, cv::Point(-1, -1), 1);
    //quickShow(openingImage4x4, "Image Opening se4x4", true);

    cv::morphologyEx(threshold60ImageG, closingImage, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 1);
    //quickShow(openingImage, "Image Closing se3x3", true);
    cv::morphologyEx(threshold60ImageG, closingImage4x4, cv::MORPH_CLOSE, element4x4, cv::Point(-1, -1), 1);
    //quickShow(openingImage4x4, "Image Closing se4x4", true);

    //WINNER WINNER
    cv::morphologyEx(threshold60ImageG, closingImage2x2, cv::MORPH_CLOSE, element2x2, cv::Point(-1, -1), 1);
    //quickShow(openingImage2x2, "Image Closing se2x2", true);
    
    
    cv::Mat imageDilate;
    //cv::dilate(openingImage2x2, imageDilate, element, cv::Point(-1, -1), 1);
    //quickShow(imageDilate, "Image Dilation with 1 iteration");
    
    cv::Mat imageFinal;
    cv::erode(closingImage2x2, imageFinal, element, cv::Point(-1, -1), 1);
    //cv::erode(imageDilate, imageFinal, element, cv::Point(-1, -1), 1);
    quickShow(imageFinal, "Image erode - FINAL Morph Operation");





    //Setup a blob detector with default parameters
    cv::SimpleBlobDetector::Params params;

    //by threshold
    //params.minThreshold = 10;
    //params.maxThreshold = 100;

    //by area
    //params.filterByArea = true;
    params.minArea = 250;
    params.maxArea = 50000;

    //by circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.7;
    //params.maxCircularity = 1.0;

    //by convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.7;

    ////by inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.7;


    cv::Ptr<cv::SimpleBlobDetector> custDetector = cv::SimpleBlobDetector::create(params);
    vector<cv::KeyPoint> keypoints;
    custDetector->detect(imageFinal, keypoints);

    cout << "Blob count: " << keypoints.size() << endl << endl;

    int x, y;
    int radius;
    double diameter;

    for (int i = 0; i < keypoints.size(); i++) {
        cv::KeyPoint k = keypoints[i];
        cv::Point keyPt;
        keyPt = k.pt;
        x = (int)keyPt.x;
        y = (int)keyPt.y;

        //mark the center in black
        cv::circle(image, cv::Point(x, y), 5, cv::Scalar(0, 0, 0), -1);

        //get the radius
        diameter = k.size;
        radius = (int)diameter / 2.0;

        //mark the blob in green
        cv::circle(image, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 5);
    }
    quickShow(image, "Filtered blobs");


    cv::destroyAllWindows();

    return 0;
}



void quickShow(cv::Mat source, std::string windowName, bool keepWindow) { //Default parameter is in the prototype/forward declaration.
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, source);
    cv::waitKey(0);
    if(!keepWindow)
        cv::destroyWindow(windowName);
    return;
}
