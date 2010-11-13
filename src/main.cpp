/*
 * main.cpp
 *
 *  Created on: Nov 10, 2010
 *      Author: mboryn
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <cv.h>
#include <highgui.h>
#include "Threshold.h"

namespace po = boost::program_options;
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	try {
		string inputImageFilename;
		string outputDir;

		po::options_description programOptions("");
		programOptions.add_options()("help", "print help");
		programOptions.add_options()("image,i", po::value<string>(&inputImageFilename), "image file to load");
		programOptions.add_options()("output,o", po::value<string>(&outputDir), "output directory for result images");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, programOptions), vm);
		po::notify(vm);
		if (vm.count("help")) {
			cout << programOptions << "\n";
			return 0;
		}
		if (vm.count("image") != 1) {
			cout << "No image specified.\n";
			cout << programOptions << "\n";
			return 1;
		}
		if (vm.count("output") != 1) {
			cout << "No dir specified.\n";
			cout << programOptions << "\n";
			return 1;
		}

		Mat image = imread(inputImageFilename.c_str());
		if(image.data == NULL){
			throw runtime_error(string("Failed to load file \"") + inputImageFilename + "\".");
		}
		Mat imageGray;
		cvtColor(image, imageGray, CV_BGR2GRAY, 1);

//		Threshold t;
//		Mat mask(imageGray.size(), CV_8U);
//		ThresholdedImage ti = t.thresholdImageOptimal(imageGray, mask, 100, 1);
//		imwrite(outputDir + "/maskAbove.png", ti.maskAbove);
//		imwrite(outputDir + "/maskBelow.png", ti.maskBelow);
	} catch (const exception& ex) {
		cout << "Error: " << ex.what() << endl;
		return 1;
	}
	return 0;
}
