
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp"

using namespace std;
using namespace cv;


int main() {
        
    cv::VideoCapture usbCam(0);
    cv::Mat frame;
    int k = 0;

    if (!usbCam.isOpened()) {
        cout << "USBCam failed to open" << endl << endl;
        return -1;
    }
    else {

        int usbVideoWidth = usbCam.get(CAP_PROP_FRAME_WIDTH);
        int usbVideoHeight = usbCam.get(CAP_PROP_FRAME_HEIGHT);
        cout << endl << endl << "USB Width: " << usbVideoWidth << " USB Height: " << usbVideoHeight << endl << endl;

        cv::Mat usbFrame;
        cv::Mat grayFrame;

        usbCam >> usbFrame;
        cv::imshow("USB Frame", usbFrame);
        cv::waitKey(0);

        while (1) {
            //start capturing the data from the usb camera
            usbCam >> usbFrame;

            if (k == 27) break; //ESC key was pressed

            //The e or the E key was pressed
            if (k == 101 || k == 69) {                
                cv::putText(usbFrame, "E is pressed, press Z or Esc", cv::Point(100, 180),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 3, LINE_AA);
            }

            //The z or the Z key was pressed
            if (k == 90 || k == 122) {                
                cv::putText(usbFrame, "Z is pressed, press E or Esc", cv::Point(100, 180),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 3, LINE_AA);
            }

            //Open two windows one color and one gray scale
            cv::cvtColor(usbFrame, grayFrame, cv::COLOR_BGR2GRAY);
            cv::imshow("USB Frame", usbFrame);
            cv::imshow("USB Gray", grayFrame);
            k = cv::waitKey(10000) & 0xFF;
        }
        
        usbCam.release();
        cv::destroyAllWindows();
    }

    return 0;
}
