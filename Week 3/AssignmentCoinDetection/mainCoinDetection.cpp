
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
//using namespace cv;

cv::Mat displayConnectedComponents(cv::Mat&); 

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

#pragma region Find the best threshold level
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
    //quickShow(threshold60ImageG, "Image Green Threshold 60");
#pragma endregion

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

#pragma region Morphalogical operations
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
    
    cv::Mat imageFinal;
    cv::Mat imageDilate, imageErode;
    cv::erode(openingImage2x2, imageErode, element, cv::Point(-1, -1), 1);
    cv::dilate(imageErode, imageFinal, element, cv::Point(-1, -1), 2);
    quickShow(imageFinal, "Image erode - FINAL Morph Operation");
#pragma endregion

#pragma region find the blobs that meet the filter criteria

    //Setup a blob detector with default parameters
    cv::SimpleBlobDetector::Params params;

    //by threshold
    //params.minThreshold = 10;
    //params.maxThreshold = 100;

    //by area
    params.filterByArea = true;
    params.minArea = 1500;
    params.maxArea = 40000;

    //by circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.5;
    //params.maxCircularity = 1.0;

    //by convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.7;

    //by inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.7;

    //by Color
    //params.blobColor = 0;

    //by distance apart
    params.minDistBetweenBlobs = 2;

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
        cv::circle(imageCopy, cv::Point(x, y), 5, cv::Scalar(0, 0, 0), -1);

        //get the radius
        diameter = k.size;
        radius = (int)diameter / 2.0;

        //mark the blob in green
        cv::circle(imageCopy, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 5);
    }
    quickShow(imageCopy, "Filtered blobs");

#pragma endregion

#pragma region Color the blobs
    cv::Mat ccaThreshold;
    cv::threshold(imageFinal, ccaThreshold, 127, 255, cv::THRESH_BINARY_INV);

    cv::Mat ccaImage;
    int nComponents = cv::connectedComponents(ccaThreshold, ccaImage);
    cv::Mat ccaImageCopy = ccaImage.clone();
    cv::Mat ccaColorMap = displayConnectedComponents(ccaImageCopy);
    quickShow(ccaColorMap, "Connected Components as Blobs");
#pragma endregion

#pragma region Contour Time

    cv::Mat contourImage = image.clone();

    vector<vector<cv::Point>> contours, filteredContours;
    vector<cv::Vec4i> hierarchy;

    cv::findContours(imageFinal, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cout << "Number of contours found: " << contours.size() << endl << endl;
    
    for (int c = 0; c < contours.size(); c++) {
        if (contours[c].size() > 140) {
            filteredContours.push_back(contours[c]);
        }
    }

    cv::drawContours(contourImage, filteredContours, -1, cv::Scalar(0, 0, 0), 5);
    quickShow(contourImage, "Contours");

    cv::Moments M;
    //int x, y;

    //use the contour moments to find the centroid
    for (size_t i = 0; i < contours.size(); i++) {
        if (contours[i].size() > 125) {
            //moments are weighted averages of pixel intensities and return certain properties
            M = cv::moments(contours[i]);
            x = int(M.m10 / double(M.m00));
            y = int(M.m01 / double(M.m00));

            //mark the center of each contour
            cv::circle(contourImage, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 1);
        }
    }
    quickShow(contourImage, "Marked Contours");




#pragma endregion



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


cv::Mat displayConnectedComponents(cv::Mat& im)
{
    // Make a copy of the image
    cv::Mat imLabels = im.clone();

    // First let's find the min and max values in imLabels
    cv::Point minLoc, maxLoc;
    double min, max;

    // The following line finds the min and max pixel values
    // and their locations in an image.
    cv::minMaxLoc(imLabels, &min, &max, &minLoc, &maxLoc);

    // Normalize the image so the min value is 0 and max value is 255.
    imLabels = 255 * (imLabels - min) / (max - min);

    // Convert image to 8-bits
    imLabels.convertTo(imLabels, CV_8U);

    // Apply a color map
    cv::Mat imColorMap;
    applyColorMap(imLabels, imColorMap, cv::COLORMAP_JET);

    return imColorMap;
}