#ifndef COLOR_DETECTOR_HPP
#define COLOR_DETECTOR_HPP

#include <opencv2/imgproc.hpp>

using namespace cv;

class ColorDetector {
    
    public:
        ColorDetector();
        void getMask(InputArray frame, OutputArray result);
        void setHueRange(int lowHue, int highHue);
        void setSaturationRange(int lowSat, int highSat=255);
        void setValueRange(int lowVal, int highVal=255);
        void setKernelSize(int size);
        Scalar getLow();
        Scalar getHigh();
        int getKernelSize();
    
    private:
        Scalar low;
        Scalar high;
        Mat hsv;
        Mat kernel;
};

#endif