
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

int main() {
    cv::Mat img = cv::imread(DATA_PATH + "images/blob_detection.jpg", cv::IMREAD_GRAYSCALE);
    //cv::imshow("Starting Image", img);
    //cv::waitKey(0);

    //Setup a blob detector with default parameters
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create();
    vector<cv::KeyPoint> keypoints;
    detector->detect(img, keypoints);

    int x, y;
    int radius;
    double diameter;

    //cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

    //for (int i = 0; i < keypoints.size(); i++) {
    //    cv::KeyPoint k = keypoints[i];
    //    cv::Point keyPt;
    //    keyPt = k.pt;
    //    x = (int)keyPt.x;
    //    y = (int)keyPt.y;

    //    //mark the center in black
    //    cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 0, 0), -1);

    //    //get the radius
    //    diameter = k.size;
    //    radius = (int)diameter / 2.0;

    //    //mark the blob in green
    //    cv::circle(img, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 2);
    //    cv::imshow("Found blobs", img);
    //}
    //cv::waitKey(0);



    //Setup a blob detector with custom parameters

    //configure the detection parameters
    cv::SimpleBlobDetector::Params params;
    
    //by threshold
    params.minThreshold = 10;
    params.maxThreshold = 100;

    //by area
    params.filterByArea = true;
    params.minArea = 150;

    //by circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;
    params.maxCircularity = 0.9;

    ////by convexity
    //params.filterByConvexity = true;
    //params.minConvexity = 0.87;

    ////by inertia
    //params.filterByInertia = true;
    //params.minInertiaRatio = 0.01;


    cv::Ptr<cv::SimpleBlobDetector> custDetector = cv::SimpleBlobDetector::create(params);
    //vector<cv::KeyPoint> keypoints;
    custDetector->detect(img, keypoints);

    //int x, y;
    //int radius;
    //double diameter;

    cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

    for (int i = 0; i < keypoints.size(); i++) {
        cv::KeyPoint k = keypoints[i];
        cv::Point keyPt;
        keyPt = k.pt;
        x = (int)keyPt.x;
        y = (int)keyPt.y;

        //mark the center in black
        cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 0, 0), -1);

        //get the radius
        diameter = k.size;
        radius = (int)diameter / 2.0;

        //mark the blob in green
        cv::circle(img, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 2);
    }
    
    cv::imshow("Filtered blobs", img);
    cv::waitKey(0);


    return 0;
}
