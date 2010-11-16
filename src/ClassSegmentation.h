/*
 * ClassSegmentation.h
 *
 *  Created on: 13-11-2010
 *      Author: mateusz
 */

#ifndef CLASSSEGMENTATION_H_
#define CLASSSEGMENTATION_H_

#include <cv.h>
#include <stdexcept>
#include <stack>
#include <vector>
#include <boost/shared_ptr.hpp>

//#include "SegmentsCollection.h"

typedef std::vector<cv::Mat> SegmentsVector;

class ClassSegmentation {
public:
	ClassSegmentation(cv::Size imageSize);
	virtual ~ClassSegmentation();

	void segmentation(const cv::Mat& originalImage, int minSegmentArea);

	SegmentsVector& getSegments();
private:
	cv::Mat image;

	cv::Mat extractSegment(int y, int x, int& area);
	cv::Size imageSize;
	std::stack<cv::Point> points;

	SegmentsVector segments;
};

#endif /* CLASSSEGMENTATION_H_ */
