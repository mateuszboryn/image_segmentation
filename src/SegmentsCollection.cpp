/*
 * SegmentsCollection.cpp
 *
 *  Created on: 13-11-2010
 *      Author: mateusz
 */

#include "SegmentsCollection.h"

using namespace std;

SegmentsCollection::SegmentsCollection(cv::Size imageSize) :
	imageSize(imageSize)
{
}

SegmentsCollection::~SegmentsCollection()
{
}

boost::shared_ptr<Segment> SegmentsCollection::createSegment()
{
	boost::shared_ptr<Segment> segment = boost::shared_ptr<Segment>(new Segment);
	segment->image = cv::Mat(imageSize, CV_8U);
	segment->segmentClass = 0;

	segments.push_back(segment);

	return segment;
}

void SegmentsCollection::removeRecentlyCreatedSegment()
{
	if (segments.size() == 0) {
		throw logic_error("segments.size() == 0");
	}
	segments.pop_back();
}

boost::shared_ptr<Segment> SegmentsCollection::getSegment(size_t index)
{
	if (index >= segments.size()) {
		throw logic_error("index >= segments.size()");
	}
	return segments[index];
}

size_t SegmentsCollection::getSegmentsCount() const
{
	return segments.size();
}

cv::Size SegmentsCollection::getImageSize() const
{
	return imageSize;
}

void SegmentsCollection::clear()
{
	segments.clear();
}

void SegmentsCollection::merge(const SegmentsCollection& sc)
{

}
