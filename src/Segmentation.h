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
#include <vector>
#include <boost/shared_ptr.hpp>

#include "ClassSegmentation.h"
#include "Threshold.h"

class Segmentation {
public:
	Segmentation(cv::Size imageSize, const std::string outDir);
	virtual ~Segmentation();

	void segmentImage(cv::Mat& image);

	SegmentsVector& getFoundSegments();

	void setMinVariance(double minVariance);
	void setMinSegmentArea(int minSegmentArea);
private:
	double minVariance;
	int minSegmentArea;
	cv::Size imageSize;

	std::string outDir;
	static int imageCnt;

	Threshold th;

	int recurseLevel;

	cv::Mat image;

	SegmentsVector foundSegments;

	void segmentRecursive(cv::Mat& mask);

	bool checkTerminationCondition(int *histogram);
};

#endif /* SEGMENTATION_H_ */
