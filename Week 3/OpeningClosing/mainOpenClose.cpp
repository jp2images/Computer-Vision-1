
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
//using namespace cv;

int main() {

    //Image location
    string imageName = DATA_PATH + "images/opening.png";
    cv::Mat img = cv::imread(imageName, cv::IMREAD_GRAYSCALE);
    cv::imshow("Opening", img);
    cv::waitKey(0);

    //create a structuring element for use with the dilation and erosion
    int kernelSize = 10;
    cv::Mat element = getStructuringElement(cv::MORPH_ELLIPSE, 
        cv::Size(2 * kernelSize + 1, 2 * kernelSize + 1),
        //Anchor point is primarily used for the cross shapped element. (-1,-1 = center)
        //In our case it is used to determine how much of the operation is shifted.
        cv::Point(kernelSize, kernelSize));
    //cv::imshow("Element", element*255);
    //cv::waitKey(0);

    //First we do an erosion
    int morphIterations = 1;
    cv::Mat imErode;
    cv::erode(img, imErode, element, cv::Point(-1, -1), morphIterations);
    //cv::imshow("Eroded Image", imErode*255);
    //cv::waitKey(0);
    
    //Then we do a dilation
    cv::Mat imOpen;
    cv::dilate(imErode, imOpen, element, cv::Point(-1, -1), morphIterations);
    //cv::imshow("Dilated after Eroded Image", imOpen * 255);
    //cv::waitKey(0);


    //Now lets do this again using the openCV morphologyEx function
    int openingSize = 3;
    morphIterations = 3;
    element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
        cv::Size(2 * openingSize + 1, 2 * openingSize + 1),
        cv::Point(openingSize, openingSize));

    cv::Mat imageMorphOpened;
    cv::morphologyEx(img, imageMorphOpened, cv::MORPH_OPEN, element, cv::Point(-1, -1), morphIterations);
    //cv::imshow("MorphologyEx Open Image", imageMorphOpened * 255);
    //cv::waitKey(0);


    //Show the closing operation
    imageName = DATA_PATH + "images/closing.png";
    img = cv::imread(imageName, cv::IMREAD_GRAYSCALE);
    cv::imshow("Closing starting Image", img);
    cv::waitKey(0);

    kernelSize = 10;
    element = cv::getStructuringElement(cv::MORPH_ELLIPSE, 
        cv::Size(2 * kernelSize + 1, 2 * kernelSize + 1), 
        cv::Point(kernelSize, kernelSize));

    cv::Mat imDilated;
    cv::dilate(img, imDilated, element);
    cv::imshow("Closing with Dilate Image", imDilated);
    cv::waitKey(0);

    cv::Mat imClose;
    cv::erode(imDilated, imClose, element);
    cv::imshow("Close with dilate Image", imClose);
    cv::waitKey(0);

    //Using the morphologyEx Function
    int closingSize = 10;
    element = cv::getStructuringElement(cv::MORPH_ELLIPSE, 
        cv::Size(2 * closingSize + 1, 2 * closingSize + 1),
        cv::Point(closingSize, closingSize));
    cv::imshow("Closing with MorphEx", imClose);
    cv::waitKey(0);


    return 0;
}
