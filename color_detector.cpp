#include "color_detector.hpp"

#define HUE 0
#define SATURATION 1
#define VALUE 2

ColorDetector::ColorDetector() {
    low = Scalar(10, 52, 72);
    high = Scalar(100, 255, 255);
    setKernelSize(3);
}

void ColorDetector::getMask(InputArray frame, OutputArray result) {
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    inRange(hsv, low, high, result);
    morphologyEx(result, result, MORPH_OPEN, kernel);
    morphologyEx(result, result, MORPH_DILATE, kernel);
}

void ColorDetector::setHueRange(int lowHue, int highHue) {
    low[HUE] = lowHue;
    high[HUE] = highHue;
}

void ColorDetector::setSaturationRange(int lowSat, int highSat) {
    //TODO: Check range
    low[SATURATION] = lowSat;
    high[SATURATION] = highSat;
}

void ColorDetector::setValueRange(int lowVal, int highVal) {
    //TODO: Check range
    low[VALUE] = lowVal;
    high[VALUE] = highVal;
}

void ColorDetector::setKernelSize(int size) {
    //TODO: Check range
    if (kernel.cols == size) {
        return;
    }
    kernel = Mat::ones(size, size, CV_32F);
}

Scalar ColorDetector::getLow() { return low; }

Scalar ColorDetector::getHigh() { return high; }

int ColorDetector::getKernelSize() { return kernel.cols; }