#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "avg_accumulator.hpp"
#include "color_detector.hpp"

#define RESULT "Result"
#define BACKGROUND "Background"
#define MASK "Mask"

#define LOW_HUE "Lower hue"
#define LOW_SAT "Lower saturation"
#define LOW_VAL "Lower value"
#define HIGH_HUE "Higher hue"
#define HIGH_SAT "Higher saturation"
#define HIGH_VAL "Higher value"
#define KERNEL_SIZE "Kernel size"

#define EXIT_IF_EMPTY(frame) if(frame.empty()) { cerr << "Could not read frame"; return 1; }

#define LOG(message) cout << (message) << endl;

#define FRAMES_TO_COMPUTE_BACKGROUND 30 //TODO: Parameter?

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    AvgAccumulator accumulator;
    ColorDetector colorDetector;
    Mat frame;
    Mat mask;
    Mat background;

    int lowHue = 25, 
        highHue = 126, 
        lowSat = 0, 
        highSat = 255, 
        lowVal = 0, 
        highVal = 255, 
        kernelSize = 3;

    // Creating GUI

    namedWindow(MASK,       WINDOW_AUTOSIZE);
    namedWindow(RESULT,     WINDOW_AUTOSIZE);
    namedWindow(BACKGROUND, WINDOW_AUTOSIZE);

    createTrackbar(LOW_HUE, MASK, &lowHue, 180);
    createTrackbar(HIGH_HUE, MASK, &highHue, 180);
    createTrackbar(LOW_SAT, MASK, &lowSat, 255);
    createTrackbar(HIGH_SAT, MASK, &highSat, 255);
    createTrackbar(LOW_VAL, MASK, &lowVal, 255);
    createTrackbar(HIGH_VAL, MASK, &highVal, 255);
    createTrackbar(KERNEL_SIZE, MASK, &kernelSize, 7);

    VideoCapture capture;
    capture.open(0);

    LOG("Estimating initial background")
    for(int i = 0; i < FRAMES_TO_COMPUTE_BACKGROUND; i++) {
        capture >> frame;
        EXIT_IF_EMPTY(frame)
        flip(frame, frame, 1);
        accumulator.add(frame);
    }
    accumulator.getAvg(background);
    
    LOG("Regular loop")
    for(;;) {

        capture >> frame;
        EXIT_IF_EMPTY(frame)
        flip(frame, frame, 1);

        colorDetector.setHueRange(lowHue, max(lowHue, highHue));
        colorDetector.setSaturationRange(lowSat, max(lowSat, highSat));
        colorDetector.setValueRange(lowVal, max(lowVal, highVal));
        colorDetector.setKernelSize(kernelSize);
        colorDetector.getMask(frame, mask);

        background.copyTo(frame, mask);

        imshow(RESULT, frame);
        imshow(BACKGROUND, background);
        imshow(MASK, mask);

        //Keyboard interaction
        int keyCode = waitKey(5);
        if (keyCode == 'q' || keyCode == 27) {
            break;
        }
    }
    return 0;
}
