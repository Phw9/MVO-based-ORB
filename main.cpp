#include "Config.h"
#include "Feature.h"
#include "Init.h"
#include "PoseEstimation.h"
#include "Triangulate.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char** argv)
{
	std::ofstream rawData ("./image.txt", rawData.out | rawData.trunc);
	std::ifstream read ("./image.txt", read.in);
	std::ifstream readGTtvec ("../image/GTpose.txt", readGTtvec.in);

    if(!read.is_open())
	{
		std::cerr << "file can't read image" << std::endl;
		return 0;
	}
	
	MakeTextFile(rawData, IMAGENUM);
	FileRead(readImageName, read);
	GTPoseRead(readtvecOfGT, readGTtvec);

	Viewer::MyVisualize pangolinViewer=Viewer::MyVisualize(WINDOWWIDTH, WINDOWHEIGHT);
    pangolinViewer.initialize();
    pangolin::OpenGlRenderState s_cam(
    pangolin::ProjectionMatrix(WINDOWWIDTH, WINDOWHEIGHT, VIEWPOINTF, VIEWPOINTF, 512, 389, 0.1, 1000),
    pangolin::ModelViewLookAt(VIEWPOINTX, VIEWPOINTY, VIEWPOINTZ, 0, 0, 0, 0.0, -1.0, 0.0));
    pangolin::View &d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -pangolinViewer.window_ratio)
                                .SetHandler(new pangolin::Handler3D(s_cam));

	while(true)
	{
		while(realFrame < ESSENTIALFRAME)
		{
			img = cv::imread(readImageName.at(imageCurNum), 
								cv::ImreadModes::IMREAD_UNCHANGED);
			if (img.empty())
			{
				std::cerr << "frame upload failed" << std::endl;
			}
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			d_cam.Activate(s_cam);
			pangolinViewer.DrawPoint(globalTVec, tvecOfGT, globalLandMark, mapPointsA.mworldMapPointsV);
			pangolin::FinishFrame();
			
			cv::imshow("img", img);
			if(cv::waitKey(0) == 27) break; // ESC key
		} // 2view SFM, Track(A,B) make, generate LandMark = current localFeature size

		// Start

		img = cv::imread(readImageName.at(imageCurNum), 
						cv::ImreadModes::IMREAD_UNCHANGED);
		
		// if(keyframe gen){ generate Pose, MapPoints, new Track}

		// if num of Feature_KLT is less than NUMOFPOINTS, GFTT
		// while(localTrackPointsA[lTPA].mfeatures.size() < NUMOFPOINTS || localTrackPointsB[lTPB].mfeatures.size() < NUMOFPOINTS)
		while(true)
		{
			img = cv::imread(readImageName.at(imageCurNum), 
						cv::ImreadModes::IMREAD_UNCHANGED);


		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		d_cam.Activate(s_cam);
    	pangolin::FinishFrame();
		cv::imshow("img", img);
		if(cv::waitKey(0) == 27) break; // ESC key
		}

    return 0;
}

