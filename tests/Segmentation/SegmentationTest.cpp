#include <unistd.h>
#include <iostream>
#include <sstream>
#include "ImageComparator.h"

#include "Segmentation.h"
#include <highgui.h>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace cv;

#define DATA_DIR "../../../tests/data/Segmentation/"
#define RESULTS_DIR "../../../tests/results/Segmentation/"

using namespace cv;

BOOST_AUTO_TEST_CASE( PWD )
{
	char *pwd = get_current_dir_name();
	cout << "Current working directory: \"" << pwd << "\"\n";
	// workspace/image_segmentation/build/tests/Threshold
	free(pwd);
}

BOOST_AUTO_TEST_CASE( White_50x50 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.1);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "1.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "1.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "White_50x50_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( Black_50x50 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.1);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "2.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "1.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "Black_50x50_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( BlackWhite_50x50 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.1);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "3.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "20.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "3.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "BlackWhite_50x50_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( WhiteRectangle_50x50 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.1);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "4.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "21.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "4.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "WhiteRectangle_50x50_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( WhiteRectangle_50x50_minArea_1 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.1);
	seg.setMinSegmentArea(25 * 15);

	Mat image = imread(DATA_DIR "4.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "21.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "4.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "WhiteRectangle_50x50_minArea_1_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( WhiteRectangle_50x50_minArea_2 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.1);
	seg.setMinSegmentArea(25 * 15 + 1);

	Mat image = imread(DATA_DIR "4.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "21.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "WhiteRectangle_50x50_minArea_2_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( BlackWhite_50x50_minVariance_1 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.24);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "3.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "20.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "3.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "BlackWhite_50x50_minVariance_1_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( BlackWhite_50x50_minVariance_2 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	seg.setMinVariance(0.25);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "3.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "1.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "BlackWhite_50x50_minVariance_2_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( GrayGray_50x50_minVariance_3 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	// 2^-18 ~~ 3.81469726562500e-06
	seg.setMinVariance(3.8146e-6);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "22.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "20.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "3.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "GrayGray_50x50_minVariance_3_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( GrayGray_50x50_minVariance_4 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);
	// 2^-18 ~~ 3.81469726562500e-06
	seg.setMinVariance(3.8147e-6);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "22.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "1.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "GrayGray_50x50_minVariance_4_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( Multimodal_50x50_1 )
{
	Size s(50, 50);
	Segmentation seg(s, RESULTS_DIR);

	seg.setMinVariance(3e-4);
	seg.setMinSegmentArea(4);

	Mat image = imread(DATA_DIR "23.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	seg.segmentImage(image);

	vector<Mat> expectedResult;
	expectedResult.push_back(imread(DATA_DIR "24.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "25.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "26.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "28.bmp", -1));
	expectedResult.push_back(imread(DATA_DIR "27.bmp", -1));

	BOOST_CHECK_EQUAL(expectedResult.size(), seg.getFoundSegments().size());

	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		cout << "Comparing: " << i << endl;
		BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(seg.getFoundSegments()[i], expectedResult[i]));
		stringstream ss;
		ss << RESULTS_DIR << "Multimodal_50x50_1_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_1 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_01.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_1_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_2 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_02.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_2_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}


BOOST_AUTO_TEST_CASE( RealImage_3 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_03.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_3_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_4 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_04.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_4_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_5 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_05.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_5_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_6 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_06.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_6_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_7 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_07.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_7_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}

BOOST_AUTO_TEST_CASE( RealImage_8 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "kostka_08.png"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_8_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}


BOOST_AUTO_TEST_CASE( RealImage_9 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "2010-06-13-150236.jpg"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_9_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}


BOOST_AUTO_TEST_CASE( RealImage_10 )
{
	Mat image;
	cvtColor(imread(DATA_DIR "2010-06-13-154350.jpg"), image, CV_BGR2GRAY);
	Segmentation seg(image.size(), RESULTS_DIR);

	seg.setMinVariance(5e-3);
	seg.setMinSegmentArea(100);

	seg.segmentImage(image);
	for (int i = 0; i < seg.getFoundSegments().size(); ++i) {
		stringstream ss;
		ss << RESULTS_DIR << "RealImage_10_" << i << ".bmp";
		imwrite(ss.str().c_str(), seg.getFoundSegments()[i]);
	}
}
