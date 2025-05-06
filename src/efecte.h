#ifndef EFECTE_H
#define EFECTE_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Efecte simple
Mat efect_invert(Mat img);
Mat efect_monocrom(Mat img);
Mat efect_sepia(Mat img);
Mat efect_blur(Mat img);
Mat efect_desaturare(Mat img);

// Efecte complexe
Mat efect_posterize(Mat img, int niveluri);   // niveluri = câte valori să rămână pe canal

Mat efect_pixelate(Mat img, int blockSize);


#endif // EFECTE_H
