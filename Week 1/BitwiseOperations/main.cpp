
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp> //imread and imwrite flags
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp"

using namespace std;

int main() {
    std::string imagePath = "../../Week 1/DataFiles/Data";
    std::string imageResults = "../../Week 1/DataFiles/results/";

    //Read in the starting image from disk.
    string faceImagePath = imagePath + "/images/musk.jpg";
    cv::Mat faceImage = cv::imread(faceImagePath);

    //Make a copy so as not mess up the original
    cv::Mat faceWithGlassesBitwise = faceImage.clone();

    //const string faceBitwise = "Sun Glasses";
    //cv::namedWindow(faceBitwise, cv::WINDOW_AUTOSIZE);
    //cv::imshow(faceBitwise, faceWithGlassesBitwise);
    //cv::waitKey(0);
    //cv::destroyWindow(faceBitwise);

    //Read the oringal sunglasses image
    string glassImagePath = imagePath + "/images/sunglass.png";

    // The flag cv::IMREAD_UNCHANGED = -1
    cv::Mat glassPNG = cv::imread(glassImagePath, cv::IMREAD_UNCHANGED); 
    cv::resize(glassPNG, glassPNG, cv::Size(300, 100));
    cout << " Glasses Image Dimensions: " << glassPNG.size() << endl << endl;

    //Seperate the image into the different color and alpha channels
    cv::Mat glassBGRAChannels[4];
    cv::Mat glassBGRChannels[3];
    cv::split(glassPNG, glassBGRAChannels);
    for (int i = 0; i < 3; i++) {
        //remove the alpha channel and leave only BGR
        glassBGRChannels[i] = glassBGRAChannels[i];
    }
    cv::Mat glassBGR, glassMask1;
    //Create the BGR image in memory
    cv::merge(glassBGRChannels, 3, glassBGR);

    //retrieve the alpha channel which will become the mask.
    glassMask1 = glassBGRAChannels[3];

    //save the resulting in memory images to disk.
    cv::imwrite(imageResults + "sunglasses1.png", glassBGR);
    cv::imwrite(imageResults + "sunglassesAlpha1.png", glassMask1);

    const string glassesWindow = "Sun Glasses";
    cv::namedWindow(glassesWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(glassesWindow, glassBGR);
    cv::waitKey(0);

    const string glassesMaskWindow = "Sun Glasses Mask";
    cv::namedWindow(glassesMaskWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(glassesMaskWindow, glassMask1);
    cv::waitKey(0);


    // Get the eye region from the face image.
    cv::Mat eyeROI = faceWithGlassesBitwise(cv::Range(150, 250), cv::Range(140, 440));

    //const string testImage = "Test";
    //cv::namedWindow(testImage, cv::WINDOW_AUTOSIZE);
    //cv::imshow(testImage, eyeROI);
    //cv::waitKey(0);
    //cv::destroyWindow(testImage);

    // Make the dimensions of the mask the same as the input image
    // Since the face image is a 3-channel image, we create a 3 channel image for the mask.
    cv::Mat glassMask;
    cv::Mat glassMaskChannels[] = { glassMask1, glassMask1, glassMask1 };
    cv::merge(glassMaskChannels, 3, glassMask);

    //Use the new mask to create the masked eye region in the copied face image
    cv::Mat eye;
    cv::Mat glassMaskNOT;
    cv::bitwise_not(glassMask1, glassMaskNOT);

    cv::Mat eyeChannels[3];
    cv::Mat eyeROIChannels[3];
    cv::Mat maskedGlass;
    cv::Mat eyeRoiFinal;

    // Seperate the eye region into color channels
    cv::split(eyeROI, eyeROIChannels);

    for (int i = 0; i < 3; i++) {
        cv::bitwise_and(eyeROIChannels[i], glassMaskNOT, eyeChannels[i]);
    }

    cv::merge(eyeChannels, 3, eye);
    cv::imwrite(imageResults + "glassMaskNOT.png", glassMaskNOT);
        
    cv::Mat glassMaskNOTChannels[] = {glassMaskNOT, glassMaskNOT, glassMaskNOT};
    cv::Mat glassMaskNOTMerged;

    // This code is an alternative way fo merging the 3 channels
    // Another way was shown in the code above. Mat glassMaskNOTChannels[] = {glassMaskNOT,glassMaskNOT,glassMaskNOT};
    cv::merge(glassMaskNOTChannels, 3, glassMaskNOTMerged);
    cv::bitwise_and(eyeROI, glassMaskNOTMerged, eye);

    cv::Mat sunglass;
    cv::Mat sunglassChannels[3];
    cv::Mat glassBGRChannels1[3];

    cv::split(glassBGR, glassBGRChannels1);

    for (int i = 0; i < 3; i++) {
        cv::bitwise_and(glassBGRChannels1[i], glassMask1, sunglassChannels[i]);
    }
    cv::merge(sunglassChannels, 3, sunglass);

    //The following is an alternative to the bitwise_and apprach
    // from above.
    cv::multiply(glassBGR, glassMask, maskedGlass);
    cv::bitwise_or(eye, sunglass, eyeRoiFinal);




    cv::imwrite(imageResults + "maskedEyeRegionBitwise.png", eye);
    cv::imwrite(imageResults + "maskedSunglassRegionBitwise.png", sunglass);
    cv::imwrite(imageResults + "augmentedEyeAndSunglassBitwise.png", eyeRoiFinal);
    
    //Copy the region created of the eyes and the glasses back to the image of Elon
    //to complete the the change.
    eyeRoiFinal.copyTo(eyeROI);





    const string maskedEyeRegionBitwise = "maskedEyeRegionBitwise";
    cv::namedWindow(maskedEyeRegionBitwise, cv::WINDOW_AUTOSIZE);
    cv::imshow(maskedEyeRegionBitwise, eye);
    cv::waitKey(0);

    const string maskedSunglassRegionBitwise = "maskedSunglassRegionBitwise";
    cv::namedWindow(maskedSunglassRegionBitwise, cv::WINDOW_AUTOSIZE);
    cv::imshow(maskedSunglassRegionBitwise, sunglass);
    cv::waitKey(0);

    const string augmentedEyeAndSunglassBitwise = "augmentedEyeAndSunglassBitwise";
    cv::namedWindow(augmentedEyeAndSunglassBitwise, cv::WINDOW_AUTOSIZE);
    cv::imshow(augmentedEyeAndSunglassBitwise, eyeRoiFinal);
    cv::waitKey(0);

    const string EyeAndSunglassBitwise = "ElonGlassesBitwise";
    cv::namedWindow(EyeAndSunglassBitwise, cv::WINDOW_AUTOSIZE);
    cv::imshow(EyeAndSunglassBitwise, faceWithGlassesBitwise);
    cv::waitKey(0);




    cv::destroyWindow(glassesWindow);
    cv::destroyWindow(glassesMaskWindow);

    cv::destroyWindow(maskedEyeRegionBitwise);
    cv::destroyWindow(maskedSunglassRegionBitwise);
    cv::destroyWindow(augmentedEyeAndSunglassBitwise);
    cv::destroyWindow(EyeAndSunglassBitwise);

    return 0;
}
