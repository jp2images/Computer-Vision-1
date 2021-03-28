
#include <iostream>
#include <stdio.h>
#include <time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "dataPath.hpp"

using namespace std;
using namespace cv;

void thresholdingUsingForLoop(cv::Mat, cv::Mat, int, int);


int main() {
    string imagePath = DATA_PATH + "images/threshold.png";
    
    string sourceWindwow = "Source Image";
    string destinationWindow = "Destination Image";
    string windowName = "OpenCV Threshold";
  
    cv::Mat source = cv::imread(imagePath, IMREAD_GRAYSCALE);

    int threshold = 100;
    int maxValue = 255;
    
    //cv::namedWindow(sourceWindwow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(sourceWindwow, source);
    //cv::waitKey(0);
    //cv::destroyWindow(sourceWindwow);

    cv::Mat dest = source.clone();

    clock_t clockTime;
    double cpu_time_used;

    cv::namedWindow(destinationWindow, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    clockTime = clock();
    thresholdingUsingForLoop(source, dest, threshold, maxValue);

    clockTime = clock() - clockTime;
    cpu_time_used = ((double)clockTime / CLOCKS_PER_SEC);
    cout << endl << "Time Taken: " << cpu_time_used << " seconds." << endl << endl;

    clockTime = clock();
    cv::threshold(source, dest, threshold, maxValue, cv::THRESH_BINARY);
    clockTime = clock() - clockTime;
    cpu_time_used = ((double)clockTime / CLOCKS_PER_SEC);
    cout << endl << "Time Taken: " << cpu_time_used << " seconds." << endl << endl;

    cv::imshow(destinationWindow, dest);
    cv::imshow(windowName, dest);



    cv::Mat dst_binary;
    cv::threshold(source, dst_binary, threshold, maxValue, cv::THRESH_BINARY);
    cv::imshow("Binary Threshold", dst_binary);

    cv::Mat dst_binary_inverse;
    cv::threshold(source, dst_binary_inverse, threshold, maxValue, cv::THRESH_BINARY_INV);
    cv::imshow("Binary Inverse Threshold", dst_binary_inverse);

    cv::Mat dst_truncate;
    cv::threshold(source, dst_truncate, threshold, maxValue, cv::THRESH_TRUNC);
    cv::imshow("Truncate Threshold", dst_truncate);

    cv::Mat dst_to_zero;
    cv::threshold(source, dst_to_zero, threshold, maxValue, cv::THRESH_TOZERO);
    cv::imshow("Threshold to Zero", dst_to_zero);

    cv::Mat dst_to_zero_inv;
    cv::threshold(source, dst_to_zero_inv, threshold, maxValue, cv::THRESH_TOZERO);
    cv::imshow("Threshold to Zero Inverted", dst_to_zero_inv);


    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

/// <summary>
/// Implement the threshold manually
/// </summary>
/// <param name="source"></param>
/// <param name="destination"></param>
/// <param name="threshold"></param>
/// <param name="maxValue"></param>
void thresholdingUsingForLoop(cv::Mat source, cv::Mat destination, int threshold, int maxValue) {
    int height = source.size().height;
    int width = source.size().width;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (source.at<uchar>(y, x) > threshold) {
                destination.at<uchar>(y, x) = maxValue;
            }
            else {
                destination.at<uchar>(y, x) = 0;
            }
        }
    }
}