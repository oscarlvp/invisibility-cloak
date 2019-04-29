#ifndef AVG_ACCUMULATOR_HPP
#define AVG_ACCUMULATOR_HPP


#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


using namespace cv;

class  AvgAccumulator {

    public:
        void add(InputArray frame);
        void clear();
        void getAvg(OutputArray avg);
    
    private:
        int frameCount;
        int originalDepth;
        Mat accumulator;

};

VideoCapture& operator >> (VideoCapture& capture, AvgAccumulator& accumulator);

#endif