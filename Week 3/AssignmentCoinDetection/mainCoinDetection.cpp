
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

void quickShow(cv::Mat, std::string = "Quick Show");

int main() {
    string imagePath = DATA_PATH + "images/CoinsA.png";
    cv::Mat image = cv::imread(imagePath);
    int imageWidth = image.size().width;
    int imageHeight = image.size().height;
    cout << "Image Dimensions: W" << imageWidth << " x H" << imageHeight << endl << endl;
    quickShow(image, "Original");
    //cv::imshow("Original", image);
    //cv::waitKey(0);
    //cv::destroyWindow("Original");

    //Make a copy so we don't mess up the original
    cv::Mat imageCopy = image.clone();

    cv::Mat imageGray;
    cv::cvtColor(imageCopy, imageGray, cv::COLOR_BGR2GRAY);
    quickShow(imageGray, "Monochrome");

    //cv::imshow("Monochrome", imageGray);
    //cv::waitKey(0);
    //cv::destroyWindow("Monochrome");

    //Split the image into channels
    cv::Mat imageB, imageG, imageR;
    cv::Mat imageChannels[3];
    cv::split(imageCopy, imageChannels);
    imageB = imageChannels[0];
    imageG = imageChannels[1];
    imageR = imageChannels[2];

    cv::imshow("Image B", imageB);
    cv::imshow("Image G", imageG);
    cv::imshow("Image R", imageR);
    cv::waitKey(0);
    cv::destroyAllWindows();


    cv::Mat thresholdImageGray;
    cv::threshold(imageGray, thresholdImageGray, 70, 255, cv::THRESH_BINARY_INV);
    quickShow(thresholdImageGray, "Image Basic Gray Threshold");
    //cv::imshow("Image Basic Gray Threshold", thresholdImageGray);
    //cv::waitKey(0);
    //cv::destroyWindow("Image Basic Gray Threshold");

    cv::Mat thresholdImageG;
    cv::threshold(imageG, thresholdImageG, 60, 255, cv::THRESH_BINARY_INV);
    quickShow(thresholdImageG, "Image Green Threshold");
    //cv::imshow("Image Green Threshold", thresholdImageG);
    //cv::waitKey(0);
    //cv::destroyWindow("Image Green Threshold");

    cv::Mat thresholdImageBlue;
    cv::threshold(imageB, thresholdImageBlue, 70, 255, cv::THRESH_BINARY_INV);
    quickShow(thresholdImageBlue, "Image Blue Threshold");
    //cv::imshow("Image Blue Threshold", thresholdImageBlue);
    //cv::waitKey(0);
    //cv::destroyWindow("Image Blue Threshold");

#pragma region Some testing
    //cv::Mat blurredImage;
    //cv::GaussianBlur(imageG, blurredImage, cv::Size(11, 11), 0.8 );
    //cv::imshow("Image Blurred", blurredImage);
    //cv::waitKey(0);
    
    //cv::Mat thresholdblurredImage;
    //cv::threshold(blurredImage, thresholdblurredImage, 80, 255, cv::THRESH_BINARY_INV);
    //cv::imshow("Image Blurred Threshold", thresholdblurredImage);
    //cv::waitKey(0);

    //cv::Mat imageMedian;
    //cv::medianBlur(imageG, imageMedian, 11);
    //cv::imshow("Image Median Blur", imageMedian);
    //cv::waitKey(0);

    //cv::threshold(imageMedian, thresholdblurredImage, 60, 255, cv::THRESH_BINARY_INV);
    //cv::imshow("Image Median Blurred Threshold", thresholdblurredImage);
    //cv::waitKey(0);
#pragma endregion

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));


    cv::Mat imageErode;
    cv::erode(thresholdImageG, imageErode, element, cv::Point(-1, -1), 1);
    quickShow(imageErode, "Image erode 1 iteration");
    //cv::imshow("Image erode 1 iteration", imageErode);
    //cv::waitKey(0);
    //cv::destroyWindow("Image erode 1 iteration");


    //*************************************************************************
    //*************************************************************************
    // Morphalogical operations.
    //*************************************************************************
    //*************************************************************************
    cv::Mat openingImage;
    cv::morphologyEx(thresholdImageG, openingImage, cv::MORPH_OPEN, element, cv::Point(-1, -1), 2);
    quickShow(openingImage, "Image Opening");
    //cv::imshow("Image Opening", openingImage);
    //cv::waitKey(0);
    //cv::destroyWindow("Image Blue Threshold");

    // seperately 

    //cv::Mat imageErode;
    cv::erode(openingImage, imageErode, element, cv::Point(-1, -1), 1);
    quickShow(imageErode, "Image erode after opening");
    //cv::imshow("Image open and erode", imageErode);
    //cv::waitKey(0);
    //cv::destroyWindow("Image Blue Threshold");

    // WINNER WINNER WINNER
    cv::Mat closingAfterErodeImage;
    cv::Mat closeEoredSe = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(4, 4));
    cv::morphologyEx(imageErode, closingAfterErodeImage, cv::MORPH_CLOSE, closeEoredSe, cv::Point(-1, -1), 2);
    quickShow(closingAfterErodeImage, "Image Close After Erode");
    //cv::imshow("Image Close After Erode", closingAfterErodeImage);
    //cv::waitKey(0);
    //cv::destroyWindow("Image Blue Threshold");




    //*******************************************************
    //*******************************************************
    //Copied from the jupyter notebook
    cv::Mat openAndCloseImage;
    element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    cv::morphologyEx(openingImage, openAndCloseImage, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 2);
    quickShow(openAndCloseImage, "Image Close");

    //erode the image
    cv::Mat fillCoinsImage;
    cv::erode(openAndCloseImage, fillCoinsImage, element, cv::Point(-1, -1), 2);
    quickShow(fillCoinsImage, "Image Eroded after a close");




    //Setup a blob detector with default parameters
    cv::SimpleBlobDetector::Params params;

    //by threshold
    //params.minThreshold = 10;
    //params.maxThreshold = 100;

    //by area
    //params.filterByArea = true;
    params.minArea = 200;
    params.maxArea = 50000;

    //by circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.7;
    //params.maxCircularity = 1.0;

    ////by convexity
    //params.filterByConvexity = true;
    //params.minConvexity = 0.87;

    ////by inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.8;


    cv::Ptr<cv::SimpleBlobDetector> custDetector = cv::SimpleBlobDetector::create(params);
    vector<cv::KeyPoint> keypoints;
    custDetector->detect(closingAfterErodeImage, keypoints);

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
        cv::circle(closingAfterErodeImage, cv::Point(x, y), 5, cv::Scalar(0, 0, 0), -1);

        //get the radius
        diameter = k.size;
        radius = (int)diameter / 2.0;

        //mark the blob in green
        cv::circle(closingAfterErodeImage, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 2);
    }

    cv::imshow("Filtered blobs", closingAfterErodeImage);
    cv::waitKey(0);

    return 0;
}



void quickShow(cv::Mat source, std::string windowName) { //Default parameter is in the prototype/forward declaration.
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, source);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
}