
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp> //imwrite

#include "dataPath.hpp"

using namespace std;

int main(void)
{
    std::string imagePath = "../../Week 1/DataFiles/Data";
    std::string imageResults = "../../Week 1/DataFiles/results/";

    cv::Mat glassMask1 = cv::imread(imageResults + "sunglassesAlpha.png", 0);
    cv::Mat glassBGR = cv::imread(imageResults + "sunglassesRGB.png");

    //const string glassesWindow = "Elon's Glasses";
    //cv::namedWindow(glassesWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(glassesWindow, glassMask1);
    //cv::waitKey(0);
    //cv::destroyWindow(glassesWindow);



    //Get the glasses mask and increace the number of channels to match the input image.
    cv::Mat glassMask;
    cv::Mat glassMaskChannels[] = { glassMask1, glassMask1, glassMask1 };
    cv::merge(glassMaskChannels, 3, glassMask);

    //convert the for the mask [0,1] since we are performing arithmatic operations.
    glassMask = glassMask / 255;

    //Get and Load Elon's image
    std::string faceImagePath = imagePath + "/images/musk.jpg";
    cv::Mat faceImage = cv::imread(faceImagePath);

    //Make a copy of Elon's image
    cv::Mat faceWithGlassesArithmetic = faceImage.clone();

    //get the eye region from the face image. This was found via trial and error.
    cv::Mat eyeROI = faceWithGlassesArithmetic(cv::Range(150, 250), cv::Range(140, 440));

    cv::Mat eyeROIChannels[3];
    cv::split(eyeROI, eyeROIChannels);
    cv::Mat maskedEyeChannels[3];
    cv::Mat maskedEye;

    for (int i = 0; i < 3; i++) {
        //use the mask to create the masked eye region
        cv::multiply(eyeROIChannels[i], (1 - glassMaskChannels[i]), maskedEyeChannels[i]);
    }

    cv::merge(maskedEyeChannels, 3, maskedEye);

    cv::Mat maskedGlass;
    //use the mask to create the masked sunglass region
    cv::multiply(glassBGR, glassMask, maskedGlass);

    cv::Mat eyeRoiFinal;
    cv::add(maskedEye, maskedGlass, eyeRoiFinal);


    cv::imwrite(imageResults + "maskedEyeRegion.png", maskedEye);
    cv::imwrite(imageResults + "maskedSunglassRegion.png", maskedGlass);
    cv::imwrite(imageResults + "augmentedEyeAndSunglass.png", eyeRoiFinal);

    eyeRoiFinal.copyTo(eyeROI);
    
    cv::imwrite(imageResults = "withSunglasses.png", faceWithGlassesArithmetic);

    




    const string elonWindow = "Elon Musk with Shapdes";
    cv::namedWindow(elonWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(elonWindow, faceWithGlassesArithmetic);
    cv::waitKey(0);
    //cv::destroyWindow(elonWindow);

    return 0;

    ////Get and Load the Sungrlasses
    //std::string glassImagePath = imagePath + "/images/sunglass.png";
    //cv::Mat glassPNG = cv::imread(glassImagePath, -1);
    //resize(glassPNG, glassPNG, cv::Size(300, 100));

    //cout << "Image Dimensions: " << glassPNG.size() << endl;
    //cout << "Number of Channels: " << glassPNG.channels() << endl;

    //cv::Mat glassBGRAChannels[4];
    //cv::Mat glassBGRChannels[3];
    ////Seperate the image into individual channels
    //cv::split(glassPNG, glassBGRAChannels);

    //for (int i = 0; i < 3; i++) {
    //    //Copy the B, G, R channels and drop the alpha
    //    glassBGRChannels[i] = glassBGRAChannels[i];
    //}

    ////Put the image back together without the alpha channel
    //merge(glassBGRChannels, 3, glassBGR);
    ////Create a mask with the alpha channel
    //glassMask1 = glassBGRAChannels[3];


    //const string glassesWindow = "Elon's Glasses";
    //cv::namedWindow(glassesWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(glassesWindow, glassPNG);
    //cv::waitKey(0);
    ////cv::destroyWindow(glassesWindow);


    //cv::imwrite(imageResults + "sunglassesRGB.png", glassBGR);
    //cv::imwrite(imageResults + "sunglassesAlpha.png", glassMask1);


    //Close the original image
    //cv::destroyWindow(elonWindow);
    //cv::destroyWindow(glassesWindow);


    ////Make a copy fo the image to "mess with"
    //cv::Mat faceWithGlassesNaive = faceImage.clone();
    //cv::Mat roiFace = faceWithGlassesNaive(cv::Range(150, 250), cv::Range(140, 440));
    ////put the glasses over the eye area of the image of Elon.
    //glassBGR.copyTo(roiFace);

    //const string elonWithGlassesWindow = "Elon with Glasses";
    //cv::namedWindow(elonWithGlassesWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(elonWithGlassesWindow, faceWithGlassesNaive);
    //cv::waitKey(0);
    //cv::destroyWindow(elonWithGlassesWindow);





    //const string elonWithMaskedGlassesWindow = "Elon with cool glasses";
    //cv::namedWindow(elonWithMaskedGlassesWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(elonWithMaskedGlassesWindow, eyeRoiFinal);
    //cv::waitKey(0);
    //cv::destroyWindow(elonWithMaskedGlassesWindow);






    //const string elonWithGlassesWindow = "Elon with Glasses";
    //cv::namedWindow(elonWithGlassesWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(elonWithGlassesWindow, faceWithGlassesNaive);
    //cv::waitKey(0);
    //cv::destroyWindow(elonWithGlassesWindow);






    return 0;
}

