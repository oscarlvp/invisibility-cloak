#include <iostream>
#include "avg_accumulator.hpp"


void AvgAccumulator::add(InputArray frame) {
    if (frameCount == 0 || accumulator.empty() || accumulator.size() != frame.size()) {
        accumulator = Mat::zeros(frame.size(), CV_MAKETYPE(CV_32F, frame.channels()));
        originalDepth = frame.depth();
    }

    frameCount++;
    accumulate(frame, accumulator);
}

void AvgAccumulator::clear() {
    frameCount = 0;
}

void AvgAccumulator::getAvg(OutputArray avg) {
    Mat result = accumulator / frameCount;
    result.convertTo(avg, originalDepth);
}

VideoCapture& operator >> (VideoCapture& capture, AvgAccumulator& accumulator) {
    Mat frame;
    capture >> frame;
    accumulator.add(frame);
    return capture;
}