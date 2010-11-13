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

#include "SegmentsCollection.h"

class ClassSegmentation {
public:
	ClassSegmentation(cv::Size imageSize);
	virtual ~ClassSegmentation();

	void segmentation(cv::Mat& image, SegmentsCollection& segments, int minSegmentArea);
private:
	void extractSegment(cv::Mat& image, int y, int x, u_int8_t colorClass, boost::shared_ptr<Segment> s);
	cv::Size imageSize;
	std::stack<cv::Point> points;
};

#endif /* CLASSSEGMENTATION_H_ */
