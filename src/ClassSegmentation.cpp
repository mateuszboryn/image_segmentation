/*
 * ClassSegmentation.cpp
 *
 *  Created on: 13-11-2010
 *      Author: mateusz
 */

#include "ClassSegmentation.h"

using namespace std;
using namespace cv;

ClassSegmentation::ClassSegmentation(cv::Size imageSize) :
	imageSize(imageSize)
{
	if(imageSize.width < 1 || imageSize.height < 1){
		throw logic_error("imageSize.width < 1 || imageSize.height < 1");
	}
}

ClassSegmentation::~ClassSegmentation()
{
}

void ClassSegmentation::segmentation(cv::Mat& image, SegmentsCollection& segments,
		int minSegmentArea)
{
	if (image.size() != imageSize) {
		throw logic_error("image.size() != visitedPixels.size()");
	}
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}
	if(image.size() != segments.getImageSize()){
		throw logic_error("image.size() != segments.getImageSize()");
	}

	segments.clear();

	int w = image.size().width;
	int h = image.size().height;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			u_int8_t colorClass = image.at<u_int8_t> (y, x);
			if (colorClass != 0) {
				boost::shared_ptr<Segment> s = segments.createSegment();
				extractSegment(image, y, x, colorClass, s);
				if (s->segmentArea < minSegmentArea) {
					segments.removeRecentlyCreatedSegment();
				}
			}
		}
	}
}

void ClassSegmentation::extractSegment(cv::Mat& image, int y, int x, u_int8_t colorClass,
		boost::shared_ptr<Segment> s)
{
	int w = image.size().width - 1, h = image.size().height - 1;

	s->segmentArea = 0;

	while (!points.empty()) {
		points.pop();
	}

	points.push(Point(x, y));
	image.at<u_int8_t> (points.top()) = 0;

	while (!points.empty()) {
		Point p = points.top();
		points.pop();

		s->image.at<u_int8_t> (p) = 255;
		++s->segmentArea;
		if (p.x > 0) { // left
			Point newP(p.x - 1, p.y);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x > 0 && p.y > 0) { // left upper
			Point newP(p.x - 1, p.y - 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.y > 0) { // upper
			Point newP(p.x, p.y - 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x < w && p.y > 0) { // right upper
			Point newP(p.x + 1, p.y - 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x < w) { // right
			Point newP(p.x + 1, p.y);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x < w && p.y < h) { // right lower
			Point newP(p.x + 1, p.y + 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.y < h) { // lower
			Point newP(p.x, p.y + 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x > 0 && p.y < h) { // left lower
			Point newP(p.x - 1, p.y + 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
	}
}
