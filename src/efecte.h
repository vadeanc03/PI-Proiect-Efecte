#ifndef EFECTE_H
#define EFECTE_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Efecte simple
Mat efect_invert(const Mat& img);
Mat efect_monocrom(const Mat& img);
Mat efect_sepia(const Mat& img);
Mat efect_blur(const Mat& img);
Mat efect_desaturare(const Mat& img);

// Efecte complexe
Mat efect_posterize(const Mat& img, int niveluri);   // niveluri = câte valori să rămână pe canal

Mat efect_pixelate(const Mat& img, int blockSize);


#endif // EFECTE_H
