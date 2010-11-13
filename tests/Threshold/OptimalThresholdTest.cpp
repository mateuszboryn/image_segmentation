#include <unistd.h>
#include <iostream>

#include "Threshold.h"
#include "ImageComparator.h"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace cv;

#define DATA_DIR "../../../tests/data/Threshold/"
#define RESULTS_DIR "../../../tests/results/Threshold/"

BOOST_AUTO_TEST_CASE( PWD )
{
	char *pwd = get_current_dir_name();
	cout << "Current working directory: \"" << pwd << "\"\n";
	// workspaParamsce/image_segmentation/build/tests/Threshold
	free(pwd);
}

BOOST_AUTO_TEST_CASE( OptimalThreshold )
{
	Threshold t;
	int histogram[Threshold::histogramSize];
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		histogram[i] = 0;
	}

	BOOST_CHECK_THROW(t.findOptimalThreshold(histogram), logic_error);

	for (int i = 0; i < Threshold::histogramSize; ++i)
		histogram[i] = 0;

	histogram[0] = 1;

	BOOST_CHECK_EQUAL(t.findOptimalThreshold(histogram), 127);

	for (int i = 0; i < Threshold::histogramSize; ++i)
		histogram[i] = 0;

	histogram[255] = 1;

	BOOST_CHECK_EQUAL(t.findOptimalThreshold(histogram), 255);

	for (int i = 0; i < Threshold::histogramSize; ++i)
		histogram[i] = 0;

	histogram[0] = 1;
	histogram[1] = 1;

	BOOST_CHECK_EQUAL(t.findOptimalThreshold(histogram), 0);

	for (int i = 0; i < Threshold::histogramSize; ++i)
		histogram[i] = 0;

	histogram[100] = 100;
	histogram[200] = 100;

	BOOST_CHECK_EQUAL(t.findOptimalThreshold(histogram), 150);

	for (int i = 0; i < Threshold::histogramSize; ++i)
		histogram[i] = 0;

	histogram[0] = 100;
	histogram[255] = 100;

	BOOST_CHECK_EQUAL(t.findOptimalThreshold(histogram), 127);
}
