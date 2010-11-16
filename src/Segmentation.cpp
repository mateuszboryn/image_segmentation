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
	imageSize(imageSize), outDir(outDir + "/") //, cs(imageSize)
{
}

Segmentation::~Segmentation()
{
}

void Segmentation::segmentImage(cv::Mat& image)
{
	if (image.size() != imageSize) {
		throw logic_error("image.size() != imageSize");
	}
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}

	this->image = image;

	recurseLevel = 0;
	foundSegments.clear();

	Mat mask = Mat::ones(imageSize, CV_8U);
	segmentRecursive(mask);
}

void Segmentation::segmentRecursive(cv::Mat& mask)
{
	int histogram[Threshold::histogramSize];
	th.histogram(image, mask, histogram);
	if (checkTerminationCondition(histogram)) {
		foundSegments.push_back(mask);
		return;
	}

	int threshold = th.findOptimalThreshold(histogram);
	Mat thresholded(imageSize, CV_8U);
	th.thresholdImage(image, mask, threshold, 127, 255, thresholded);

	ClassSegmentation cs(imageSize);
	cs.segmentation(thresholded, minSegmentArea);

	for (int i = 0; i < cs.getSegments().size(); ++i) {
		segmentRecursive(cs.getSegments()[i]);
	}
}

bool Segmentation::checkTerminationCondition(int *histogram)
{
	// TODO: policzyc wariancje

	// TODO: porwonac wariancje
	return true;
}

SegmentsVector& Segmentation::getFoundSegments()
{
	return foundSegments;
}
