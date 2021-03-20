
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
//using namespace cv;

void quickShow(cv::Mat, std::string = "Quick Show");

int main() {

    //Create the demo image
    cv::Mat demoImage = cv::Mat::zeros(cv::Size(10, 10), CV_8U);
    //cout << demoImage << endl << endl;;
    //quickShow(demoImage);

    //change the demo image to have some features
    demoImage.at<uchar>(0, 1) = 1;
    demoImage.at<uchar>(9, 0) = 1;
    demoImage.at<uchar>(8, 9) = 1;
    demoImage.at<uchar>(2, 2) = 1;

    demoImage(cv::Range(5, 8), cv::Range(5, 8)).setTo(1);
    //cout << demoImage << endl << endl;;
    //quickShow(demoImage*255);

    //Create the structyring element for the Dilation and Erosion functions
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    //cout << element << endl << endl;
    //quickShow(element * 255);

    int ksize = element.size().height;
    int height = demoImage.size().height;
    int width = demoImage.size().width;

    //cv::Mat dilatedCrossKernel;
    //cv::dilate(demoImage, dilatedCrossKernel, element);
    //cout << dilatedCrossKernel << endl << endl;
    //quickShow(dilatedCrossKernel * 255);

    int border = ksize / 2;
    cv::Mat paddedDemoImage = cv::Mat::zeros(cv::Size(height + (border * 2), width + (border * 2)), CV_8UC1);
    cv::copyMakeBorder(demoImage, paddedDemoImage, border, border, border, border, cv::BORDER_CONSTANT, 0);

    cv::Mat paddedDilatedImage = paddedDemoImage.clone();
    cv::Mat mask;
    cv::Mat resizedFrame;

    double minVal, maxVal;

    string videoName = "dilationScratch.avi";
    int vidHeight = paddedDilatedImage.size().height;
    int vidWidth = paddedDilatedImage.size().width;
    int videoFPS = 5;


    cv::VideoWriter videoOut(videoName,
        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
        videoFPS, cv::Size(vidHeight, vidWidth), false);

    if (!videoOut.isOpened()) {

        cout << endl << "Video Writer is not OPEN" << endl << endl;
        return -1;
    }

    //quickShow(paddedDemoImage * 255);
    //quickShow(element * 255);
    cv::Mat bigPicture;

    videoOut.write(paddedDemoImage * 255);
    for (int h_i = border; h_i < height + border; h_i++) {
        for (int w_i = border; w_i < width + border; w_i++) {
            if (demoImage.at<uchar>(h_i - border, w_i - border)) {
                //Or the structuring element with the the image and write the result to the mask.
                cv::bitwise_or(paddedDilatedImage(
                    cv::Range(h_i - border, h_i + border + 1),
                    cv::Range(w_i - border, w_i + border + 1)), element, mask);
                //Copy the mask back to the image
                mask.copyTo(paddedDilatedImage(cv::Range(h_i - border, h_i + border + 1),
                    cv::Range(w_i - border, w_i + border + 1)));

                cv::resize(paddedDilatedImage, resizedFrame, cv::Size(50, 50), 0, 0, cv::INTER_CUBIC);
                videoOut.write(resizedFrame * 255);
                cv::imshow("video", resizedFrame * 255);

                //videoOut.write(paddedDilatedImage * 255);
                //videoOut.write(paddedDilatedImage * 255);
                //cv::imshow("video", paddedDilatedImage * 255);
                //cv::imshow("video", paddedDilatedImage * 255);
            }
            cv::waitKey(100);                
        } 
    }      
    videoOut.write(paddedDilatedImage * 255);

    videoOut.release();
    cv::waitKey(0);
    cv::destroyWindow("video");

    //Play the video back
    cv::VideoCapture myVid(videoName);

    if (!myVid.isOpened()) {
        cout << endl << "Error opening video stream or file" << endl << endl;
        return -1;
    }
    cv::Mat frame;
    int videoWidth = myVid.get(cv::CAP_PROP_FRAME_WIDTH);
    int videoHeight = myVid.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << endl << endl << "Width: " << videoWidth << " Height: " << videoHeight << endl << endl;
    //Start at a different position of the video
    myVid.set(cv::CAP_PROP_POS_MSEC, 0);

    while (myVid.isOpened()) {
        myVid >> frame;

        if (frame.empty()) {
            break;
        }
        cv::imshow("Frame", frame);
        cv::waitKey(500);
    }

    return 0;
}

void quickShow(cv::Mat source, std::string windowName) { //Default parameter is in the prototype/forward declaration.
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, source);
    cv::waitKey(0);

    cv::destroyWindow(windowName);
}
