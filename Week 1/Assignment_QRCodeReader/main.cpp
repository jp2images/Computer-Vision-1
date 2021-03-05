
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp> //imwrite
#include <opencv2/imgproc/imgproc.hpp>

#include "dataPath.hpp";
//#include "../../resource/lib/public/includeLibraries.h"
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    std::string imagePath = "../../Week 1/DataFiles/Data";

    cv::Mat bbox;
    cv::Mat rectifiedImage;

    cv::Mat img = cv::imread(imagePath + "/images/IDCard-Satya.png");

    //cv::imshow("qrcode", img);
    //cv::waitKey(0);

    cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();
    string opencvData = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);

    if (opencvData.length() > 0) {
        cout << "QR Code detected!" << endl << endl;
    }
    else {
        cout << "QR Code NOT detected!" << endl << endl;
    }
    
    int n = bbox.cols;
    for (int i = 0; i < n; i++) {
        cv::line(img,
            cv::Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)),
            cv::Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)),
                cv::Scalar(255, 0, 0), 3, LINE_AA);
    }


    cv::imshow("Result", img);
    cv::waitKey(0);

    return 0;
}
