/*
 * Segmentation.cpp
 *
 *  Created on: Nov 10, 2010
 *      Author: mboryn
 */

#include <iostream>
#include <sstream>
#include "Segmentation.h"

using namespace cv;
using namespace std;

Segmentation::Segmentation(cv::Size imageSize, const std::string outDir) :
	imageSize(imageSize), outDir(outDir + "/")
{
}

Segmentation::~Segmentation()
{
}

void Segmentation::segmentImage(const cv::Mat& image, SegmentsCollection& segments)
{
	if (image.size() != imageSize) {
		throw logic_error("image.size() != imageSize");
	}
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}

	Mat mask(imageSize, CV_8U);

	int histogram[Threshold::histogramSize];

	th.histogram(image, mask, histogram);

	int threshold = th.findOptimalThreshold(histogram);

	Mat thresholded(imageSize, CV_8U);
	th.thresholdImage(image, cv::Mat(imageSize, CV_8U), threshold, 127, 255, thresholded);

	SegmentsCollection sc;
	cs.segmentation(result, sc, 100);

	recurseLevel = 0;
}

void Segmentation::segmentRecursive(const cv::Mat& image, cv::Mat& mask,
		SegmentsCollection& segments)
{

}
