#include <Threshold.h>

#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace std;
using namespace cv;

BOOST_AUTO_TEST_CASE( EmptyImage )
{
	Mat image;
	Mat mask = Mat::zeros(Size(10, 10), CV_8U);
	Mat result = Mat::zeros(Size(10, 10), CV_8U);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);

}

BOOST_AUTO_TEST_CASE( EmptyMask )
{
	Mat image = Mat::zeros(Size(10, 10), CV_8U);
	Mat mask;
	Mat result = Mat::zeros(Size(10, 10), CV_8U);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);

}

BOOST_AUTO_TEST_CASE( ImageMaskDifferent )
{
	Mat image = Mat::zeros(Size(10, 10), CV_8U);
	Mat mask = Mat::zeros(Size(10, 9), CV_8U);
	Mat result = Mat::zeros(Size(10, 10), CV_8U);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);

	image = Mat::zeros(Size(10, 10), CV_8U);
	mask = Mat::zeros(Size(9, 10), CV_8U);
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);
}

BOOST_AUTO_TEST_CASE( ResultSizeDifferent )
{
	Mat image = Mat::zeros(Size(10, 10), CV_8U);
	Mat mask = Mat::zeros(Size(10, 10), CV_8U);
	Mat result = Mat::zeros(Size(10, 9), CV_8U);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);

	result = Mat::zeros(Size(9, 10), CV_8U);
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);
}

BOOST_AUTO_TEST_CASE( ResultTypeDifferent )
{
	Mat image = Mat::zeros(Size(10, 10), CV_8U);
	Mat mask = Mat::zeros(Size(10, 10), CV_8U);
	Mat result = Mat::zeros(Size(10, 10), CV_8UC3);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);
}

BOOST_AUTO_TEST_CASE( ImageType )
{
	Mat image = Mat::zeros(Size(10, 10), CV_8UC3);
	Mat mask = Mat::zeros(Size(10, 10), CV_8U);
	Mat result = Mat::zeros(Size(10, 10), CV_8U);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);

	image = Mat::zeros(Size(10, 10), CV_8U);
	mask = Mat::zeros(Size(10, 10), CV_8UC3);

	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 155, 20, 200, result), logic_error);
}

BOOST_AUTO_TEST_CASE( ThresholdRange )
{
	Mat image = Mat::zeros(Size(10, 10), CV_8U);
	Mat mask = Mat::zeros(Size(10, 10), CV_8U);
	Mat result = Mat::zeros(Size(10, 10), CV_8U);
	Threshold t;
	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, -1, 20, 200, result), logic_error);
	t.thresholdImage(image, mask, 0, 20, 200, result);

	image = Mat::zeros(Size(10, 10), CV_8U);
	mask = Mat::zeros(Size(10, 10), CV_8U);

	BOOST_REQUIRE_THROW(t.thresholdImage(image, mask, 256, 20, 200, result), logic_error);
	t.thresholdImage(image, mask, 255, 20, 200, result);

	t.thresholdImage(image, mask, 100, 20, 200, result);
}

