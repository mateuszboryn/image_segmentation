#include <unistd.h>
#include <iostream>

#include "Threshold.h"
#include "ImageComparator.h"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace cv;

#define DATA_DIR "../../../tests/data/Threshold/"

BOOST_AUTO_TEST_CASE( PWD )
{
	char *pwd = get_current_dir_name();
	cout << "Current working directory: \"" << pwd << "\"\n";
	// workspace/image_segmentation/build/tests/Threshold
	free(pwd);
}

BOOST_AUTO_TEST_CASE( SameImage )
{
	Mat image1 = imread(DATA_DIR "1.bmp");
	Mat image2 = imread(DATA_DIR "1.bmp");

	BOOST_CHECK(image1.size() == Size(50, 50));
	BOOST_CHECK(image2.size() == Size(50, 50));

	BOOST_CHECK( ImageComparator::isEqual<u_char>(image1, image2) );
}

BOOST_AUTO_TEST_CASE( DifferentImages )
{
	Mat image1 = imread(DATA_DIR "1.bmp");
	Mat image2 = imread(DATA_DIR "2.bmp");

	BOOST_CHECK(image1.size() == Size(50, 50));
	BOOST_CHECK(image2.size() == Size(50, 50));

	BOOST_CHECK( ImageComparator::isEqual<u_char>(image1, image2) == false );
}


