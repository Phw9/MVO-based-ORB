#pragma once

#include <vector>
#include "Triangulate.h"
#include "eigen3/Eigen/Dense"
#include "opencv2/features2d.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/video.hpp"

#define ERRORSIZE 25
#define MAXCORNER 1000
#define QUALITYLEVEL 0.01
#define MINDISTANCE 8


namespace mvo
{
    class Feature_KLT
    {
    public:
        Feature_KLT();
        ~Feature_KLT()=default;
        

        
        bool GoodFeaturesToTrack(const cv::Mat& src);
        bool OpticalFlowPyrLK(const cv::Mat& src1, const cv::Mat& src2, mvo::Feature_KLT& next);

        std::vector<uchar> mstatus;
        std::vector<float> merr;
        std::vector<cv::Point2f> mfeatures;
    };
}//namespace mvo

void ManageTrackPoints(const mvo::Feature_KLT& present, mvo::Feature_KLT& before);
bool ManageMapPoints(const std::vector<uchar>& mstatus, std::vector<cv::Point3f>& map);
bool ManageMinusZ(mvo::Triangulate& map, cv::Mat& R, std::vector<int>& id);
bool ManageMinusZSFM(mvo::Triangulate& map, cv::Mat& R, std::vector<int>& id);
bool ManageMinusLocal(std::vector<mvo::Feature_KLT>& localTrackPoints, const std::vector<int>& id);
void ManageInlier(std::vector<mvo::Feature_KLT>& features2d, std::vector<cv::Point3f>& mapPoints3d, const cv::Mat& inlier);