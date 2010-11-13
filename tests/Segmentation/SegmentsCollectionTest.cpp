#include <unistd.h>
#include <iostream>

#include "SegmentsCollection.h"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace cv;

BOOST_AUTO_TEST_CASE( Params )
{
	Size size(20, 30);
	SegmentsCollection sc(size);

	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 0);
	BOOST_CHECK_THROW(sc.getSegment(0), logic_error);
	BOOST_CHECK_THROW(sc.removeRecentlyCreatedSegment(), logic_error);

	boost::shared_ptr<Segment> s, s1, s2;

	s = sc.createSegment();

	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	BOOST_CHECK(s == sc.getSegment(0));
	BOOST_CHECK(s->image.size() == size);
	BOOST_CHECK(s->image.type() == CV_8U);
	BOOST_CHECK(sc.getSegment(0)->image.size() == size);

	BOOST_CHECK_THROW(sc.getSegment(1), logic_error);

	sc.removeRecentlyCreatedSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 0);
	BOOST_CHECK_THROW(sc.getSegment(0), logic_error);
	BOOST_CHECK_THROW(sc.removeRecentlyCreatedSegment(), logic_error);

	s = sc.createSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	s1 = sc.createSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 2);
	s2 = sc.createSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 3);

	BOOST_CHECK(s == sc.getSegment(0));
	BOOST_CHECK(s->image.size() == size);
	BOOST_CHECK(s->image.type() == CV_8U);
	BOOST_CHECK(s1 == sc.getSegment(1));
	BOOST_CHECK(s1->image.size() == size);
	BOOST_CHECK(s1->image.type() == CV_8U);
	BOOST_CHECK(s2 == sc.getSegment(2));
	BOOST_CHECK(s2->image.size() == size);
	BOOST_CHECK(s2->image.type() == CV_8U);
	BOOST_CHECK_THROW(sc.getSegment(3), logic_error);

	sc.removeRecentlyCreatedSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 2);
	BOOST_CHECK(s == sc.getSegment(0));
	BOOST_CHECK(s1 == sc.getSegment(1));
	BOOST_CHECK_THROW(sc.getSegment(2), logic_error);

	sc.removeRecentlyCreatedSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	BOOST_CHECK(s == sc.getSegment(0));
	BOOST_CHECK_THROW(sc.getSegment(1), logic_error);

	sc.removeRecentlyCreatedSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 0);
	BOOST_CHECK_THROW(sc.getSegment(0), logic_error);
	BOOST_CHECK_THROW(sc.removeRecentlyCreatedSegment(), logic_error);

	s = sc.createSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	s1 = sc.createSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 2);
	s2 = sc.createSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 3);

	BOOST_CHECK(s == sc.getSegment(0));
	BOOST_CHECK(s->image.size() == size);
	BOOST_CHECK(s->image.type() == CV_8U);
	BOOST_CHECK(s1 == sc.getSegment(1));
	BOOST_CHECK(s1->image.size() == size);
	BOOST_CHECK(s1->image.type() == CV_8U);
	BOOST_CHECK(s2 == sc.getSegment(2));
	BOOST_CHECK(s2->image.size() == size);
	BOOST_CHECK(s2->image.type() == CV_8U);
	BOOST_CHECK_THROW(sc.getSegment(3), logic_error);

	sc.removeRecentlyCreatedSegment();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 2);
	BOOST_CHECK(s == sc.getSegment(0));
	BOOST_CHECK(s1 == sc.getSegment(1));
	BOOST_CHECK_THROW(sc.getSegment(2), logic_error);

	sc.clear();
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 0);
	BOOST_CHECK_THROW(sc.getSegment(0), logic_error);
	BOOST_CHECK_THROW(sc.removeRecentlyCreatedSegment(), logic_error);
}

