
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

    string videoDilationName = "dilationScratch.avi";
    int videoFPS = 10;

    cv::VideoWriter videoDilationOut(videoDilationName,
        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
        videoFPS, cv::Size(50, 50), true);

    if (!videoDilationOut.isOpened()) {
        std::cout << endl << "Dilation Video Writer is not OPEN" << endl << endl;
        return -1;
    }
    
    int x = demoImage.size().height;
    int y = demoImage.size().width;
   
    cv::Mat imageCropped;

    //Begin dilation of the image.
    //for (int h_i = border; h_i < height + border; h_i++) {
    //    for (int w_i = border; w_i < width + border; w_i++) {
    //        if (demoImage.at<uchar>(h_i - border, w_i - border)) {
    //            //Or the structuring element with the the image and write the result to the mask.
    //            cv::bitwise_or(paddedDilatedImage(
    //                cv::Range(h_i - border, h_i + border + 1),
    //                cv::Range(w_i - border, w_i + border + 1)), element, mask);
    //            //Copy the mask back to the image
    //            mask.copyTo(paddedDilatedImage(cv::Range(h_i - border, h_i + border + 1),
    //                cv::Range(w_i - border, w_i + border + 1)));
    //        }
    //        imageCropped = paddedDilatedImage(cv::Rect(1, 1, x, y));
    //        cv::resize(imageCropped * 255, resizedFrame, cv::Size(50, 50), 0, 0, cv::INTER_NEAREST);
    //        cv::cvtColor(resizedFrame, resizedFrame, cv::COLOR_GRAY2BGR);
    //        videoDilationOut.write(resizedFrame);
    //        cv::imshow("Video Dilation", resizedFrame);
    //        cv::waitKey(50);
    //    } 
    //}      

    //videoDilationOut.release();
    //cv::waitKey(0);
    //cv::destroyWindow("Video Dilation");


    cv::Mat invertedMask = cv::Mat::ones(cv::Size(3, 3), CV_8U);
    cv::Mat erosionElement;// = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

    cv::bitwise_xor(element, invertedMask, erosionElement);
    cout << erosionElement << endl << endl;

    cv::Mat paddedErodedImage = paddedDemoImage.clone();
    //cv::Mat mask;
    //cv::Mat resizedFrame;

    string videoErosionName = "erosionScratch.avi";
    //int videoFPS = 10;

    cv::VideoWriter videoErosionOut(videoErosionName,
        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
        videoFPS, cv::Size(50, 50), true);

    if (!videoErosionOut.isOpened()) {
        std::cout << endl << "Erosion Video Writer is not OPEN" << endl << endl;
        return -1;
    }

    double  minVal, maxVal;
    cv::Point erodeRow, erodeCol;

    //Begin erosion of the image.
    for (int h_i = border; h_i < height + border; h_i++) {
        for (int w_i = border; w_i < width + border; w_i++) {
            if (demoImage.at<uchar>(h_i - border, w_i - border)) {

                //Or the structuring element with the the image and write the result to the mask.
                cv::bitwise_and(paddedErodedImage(
                    cv::Range(h_i - border, h_i + border + 1),
                    cv::Range(w_i - border, w_i + border + 1)), element, mask);
                
                cv::minMaxLoc(mask, &minVal, &maxVal);
                cout << "Max:" << maxVal << endl << endl;
                if (maxVal == 1) {
                    //Copy the mask back to the image
                    mask.copyTo(paddedErodedImage(
                        cv::Range(h_i - border, h_i + border + 1),
                        cv::Range(w_i - border, w_i + border + 1)));
                }
            }

            imageCropped = paddedErodedImage(cv::Rect(1, 1, x, y));
            cv::resize(imageCropped * 255, resizedFrame, cv::Size(50, 50), 0, 0, cv::INTER_NEAREST);
            cv::cvtColor(resizedFrame, resizedFrame, cv::COLOR_GRAY2BGR);
            videoErosionOut.write(resizedFrame);
            cv::imshow("Video Erosion", resizedFrame);
            cv::waitKey(20);
        }
    }

    videoErosionOut.release();
    cv::waitKey(0);
    cv::destroyWindow("Video Erosion");



    //Play the video back
    cv::VideoCapture myVid(videoDilationName);

    if (!myVid.isOpened()) {
        std::cout << std::endl << "Error opening video stream or file" << std::endl << std::endl;
        return -1;
    }
    cv::Mat frame;
    int videoWidth = myVid.get(cv::CAP_PROP_FRAME_WIDTH);
    int videoHeight = myVid.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << std::endl << std::endl << "Width: " << videoWidth << " Height: " << videoHeight << std::endl << std::endl;
    //Start at a different position of the video
    myVid.set(cv::CAP_PROP_POS_MSEC, 0);

    while (myVid.isOpened()) {
        myVid >> frame;

        if (frame.empty()) {
            break;
        }
        cv::imshow("Playback", frame);
        //cv::waitKey(50);
    }

    return 0;
}

void quickShow(cv::Mat source, std::string windowName) { //Default parameter is in the prototype/forward declaration.
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, source);
    cv::waitKey(0);

    cv::destroyWindow(windowName);
}
