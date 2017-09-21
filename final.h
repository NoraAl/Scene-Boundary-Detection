//
//  final.h
//  xcodefinal
//
//  Created by Nora Alosily on 4/7/17.
//  Copyright © 2017 NoraAlosily. All rights reserved.
//

#ifndef final_h
#define final_h


#include<iostream>
#include <opencv2/opencv.hpp>


#define YUVBINS 96 /* total bins for the three channels */
#define YUVsinglechannel 32 /*a single channel size YUVBINS/3 */
#define Ystart 0 /* index of Y channel at the globle histogram (out of 96 bins)*/
#define Ustart 32 /* index of U channel at the globle histogram (out of 96 bins) */
#define Vstart 64 /* index of V channel at the globle histogram (out of 96 bins) */

#define BLOCKBINS 384 /* total bins for the three channels */
#define BLOCKSIZE 8 /*a single channel size YUVBINS/3 */
#define GRIDCOUNT 4 /* index of Y channel at the globle histogram (out of 96 bins)*/
#define blockchannelsize 128 /* index of U channel at the globle histogram (out of 96 bins) */


#define YUVBINS             96 /* total bins for the three channels */
#define YUVsinglechannel    32 /*a single channel size YUVBINS/3 */
#define Ystart              0 /* index of Y channel at the globle histogram (out of 96 bins)*/
#define Ustart              32 /* index of U channel at the globle histogram (out of 96 bins) */
#define Vstart              64 /* index of V channel at the globle histogram (out of 96 bins) */

#define BLOCKSBINS          384 /* total bins for the three channels */
#define SingleBlockBins     8 /*a single channel size YUVBINS/3 */
#define BlocksCount         4 /* size of each division */
#define blockchannelsize    128 /* index of U channel at the globle histogram (out of 96 bins) */
//lag =5
#define L                   10
#define LR                  9

using namespace cv;
using namespace std;

extern ostringstream err;

void help();
int* readAnnotation();
void writeAnnotation(int annotaiton[], int set);

void processVideo(string filename);
void classifyAbrubt (VideoCapture vid);
void segment(VideoCapture);
void classifyGradual(VideoCapture vid);


Mat globalHistogram(Mat src);
Mat blockHistogram(Mat src);
void saveNew(Mat m, string filename, string annotaion);
void showframe(Mat& frame, int);
void open(string filename, string annotation, Mat& mat);

void calcYUVHistogram(Mat src);
void calcRGBHistogram2(Mat src);

#endif /* final_h */
