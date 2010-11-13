/*
 * Segmentation.h
 *
 *  Created on: Nov 10, 2010
 *      Author: mboryn
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <cv.h>
#include <highgui.h>
#include <string>
#include <stdexcept>

#include "ClassSegmentation.h"
#include "Threshold.h"

class Segmentation {
public:
	Segmentation(cv::Size imageSize, const std::string outDir);
	virtual ~Segmentation();

	void segmentImage(const cv::Mat& image, SegmentsCollection& segments);

private:
	cv::Size imageSize;

	std::string outDir;
	int imageCnt;

	ClassSegmentation cs;
	Threshold th;

	int recurseLevel;

	void segmentRecursive(const cv::Mat& image, cv::Mat& mask, SegmentsCollection& segments);

	bool checkTerminationCondition(const cv::Mat& image, cv::Mat& mask);
};

#endif /* SEGMENTATION_H_ */
