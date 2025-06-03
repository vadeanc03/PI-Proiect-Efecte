#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "efecte.h"

using namespace std;
using namespace cv;


Mat efect_invert(const Mat& img) {
     // Inverseaza culorile fiecarui pixel: 255 - valoarea actuala

    //Mat rezultat = img;
    //optimizat cu img.clone
    Mat rezultat = img.clone();

    for (int i = 0; i < rezultat.rows; i++) {
        for (int j = 0; j < rezultat.cols; j++) {
            Vec3b& pixel = rezultat.at<Vec3b>(i, j);
            pixel[0] = 255 - pixel[0]; // B
            pixel[1] = 255 - pixel[1]; // G
            pixel[2] = 255 - pixel[2]; // R
        }
    }

    return rezultat;
}


Mat efect_monocrom(const Mat& img) {
     // Conversie la alb-negru binar pe baza mediei RGB

    //Mat rezultat = img;
    Mat rezultat = img.clone();

    for (int i = 0; i < rezultat.rows; i++) {
        for (int j = 0; j < rezultat.cols; j++) {
            Vec3b& pixel = rezultat.at<Vec3b>(i, j);
            int medie = (pixel[0] + pixel[1] + pixel[2]) / 3;
            uchar valoare = (medie > 127) ? 255 : 0;
            pixel[0] = valoare;
            pixel[1] = valoare;
            pixel[2] = valoare;
        }
    }

    return rezultat;
}


Mat efect_sepia(const Mat& img) {
     // Aplica efectul sepia folosind formule fixe

    //Mat rezultat = img;
    Mat rezultat = img.clone();

    for (int i = 0; i < rezultat.rows; i++) {
        for (int j = 0; j < rezultat.cols; j++) {
            Vec3b pixel = rezultat.at<Vec3b>(i, j);
            int B = pixel[0], G = pixel[1], R = pixel[2];

            int nouR = 0.4 * R + 0.75 * G + 0.2 * B;
            int nouG = 0.35 * R + 0.7 * G + 0.15 * B;
            int nouB = 0.25 * R + 0.5 * G + 0.15 * B;

            if (nouR > 255) nouR = 255;
            if (nouG > 255) nouG = 255;
            if (nouB > 255) nouB = 255;

            rezultat.at<Vec3b>(i, j)[2] = (uchar)nouR;
            rezultat.at<Vec3b>(i, j)[1] = (uchar)nouG;
            rezultat.at<Vec3b>(i, j)[0] = (uchar)nouB;
        }
    }

    return rezultat;
}


// Mat efect_blur(Mat img) {
//      // Aplica blur
//
//     Mat rezultat = img;
//
//     for (int i = 1; i < img.rows - 1; i++) {
//         for (int j = 1; j < img.cols - 1; j++) {
//
//             int sumaB = 0, sumaG = 0, sumaR = 0;
//
//             for (int m = -1; m <= 1; m++) {
//                 for (int n = -1; n <= 1; n++) {
//                     Vec3b pixel = img.at<Vec3b>(i + m, j + n);
//                     sumaB += pixel[0];
//                     sumaG += pixel[1];
//                     sumaR += pixel[2];
//                 }
//             }
//
//             rezultat.at<Vec3b>(i, j)[0] = sumaB / 9;
//             rezultat.at<Vec3b>(i, j)[1] = sumaG / 9;
//             rezultat.at<Vec3b>(i, j)[2] = sumaR / 9;
//         }
//     }
//
//     return rezultat;
// }

// efectul blur optimizat
Mat efect_blur(const Mat& img) {
    int rows = img.rows;
    int cols = img.cols;

    Mat integralImg(rows + 1, cols + 1, CV_32SC3, Vec3i(0, 0, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b pix = img.at<Vec3b>(i, j);
            Vec3i valOrig(pix[0], pix[1], pix[2]);

            Vec3i sus    = integralImg.at<Vec3i>(i,   j + 1);
            Vec3i stanga = integralImg.at<Vec3i>(i + 1, j  );
            Vec3i diag   = integralImg.at<Vec3i>(i,   j  );

            Vec3i &dest = integralImg.at<Vec3i>(i + 1, j + 1);
            dest = valOrig + sus + stanga - diag;
        }
    }

    // Construim imaginea de output, inițial o clona a originalului
    //    Marginile le lăsăm neschimbate
    Mat rezultat = img.clone();

    // Pentru fiecare pixel interior, calculăm blur-ul pe 3×3 cu ajutorul imaginii integrale
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            Vec3i A = integralImg.at<Vec3i>(i - 1,     j - 1);
            Vec3i B = integralImg.at<Vec3i>(i - 1,     j + 2);
            Vec3i C = integralImg.at<Vec3i>(i + 2,     j - 1);
            Vec3i D = integralImg.at<Vec3i>(i + 2,     j + 2);

            // Suma celor 9 pixeli (B, G, R) din patch-ul 3×3
            Vec3i sum3x3 = D + A - B - C;

            // Calculăm media pe cele 3 canale, împărțind la 9 și convertind la uchar
            Vec3b medie;
            medie[0] = static_cast<uchar>(sum3x3[0] / 9);
            medie[1] = static_cast<uchar>(sum3x3[1] / 9);
            medie[2] = static_cast<uchar>(sum3x3[2] / 9);

            rezultat.at<Vec3b>(i, j) = medie;
        }
    }

    return rezultat;
}


Mat efect_desaturare(const Mat& img) {
     // Efect de desaturare; reduce saturația culorilor

    //Mat rezultat = img;
    Mat rezultat = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3b& pixel = rezultat.at<Vec3b>(i, j);
            int medie = (pixel[0] + pixel[1] + pixel[2])  / 3;

            // combina culoarea originala cu griul sau
            pixel[0] = (pixel[0] + medie) / 2;
            pixel[1] = (pixel[1] + medie) / 2;
            pixel[2] = (pixel[2] + medie) / 2;
        }
    }

    return rezultat;
}


Mat efect_posterize(const Mat& img, int niveluri) {
     // Posterize folosind algoritmul K-Means Clustering
     // niveluri = numarul de culori dorite (K)

    //Mat rezultat;
    Mat rezultat = img.clone();

    Mat samples(img.rows * img.cols, 3, CV_32F);

    // Pregatim vectorii de intrare pentru K-Means
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            for (int c = 0; c < 3; c++) {
                samples.at<float>(i * img.cols + j, c) = static_cast<float>(img.at<Vec3b>(i, j)[c]);
            }
        }
    }

    // vector pentru etichete si pentru centrele clusterelor
    Mat etichete;
    Mat centre; // culorile fiecarui cluster

    // aici aplicam KMeans
    kmeans(samples, niveluri, etichete,
           TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 5, 1.0),
           3, KMEANS_PP_CENTERS, centre);

    // Refacem imaginea folosind centrele clusterelor
    rezultat = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int et = etichete.at<int>(i * img.cols + j);
            Vec3b& pixel = rezultat.at<Vec3b>(i, j);
            for (int c = 0; c < 3; c++) {
                pixel[c] = static_cast<uchar>(centre.at<float>(et, c));
            }
        }
    }

    return rezultat;
}


Mat efect_pixelate(const Mat& img, int blockSize) {
     // Efect de pixelare: impartim imaginea in patrate egale
     // fiecare bloc este inlocuit cu culoarea medie a sa

    //Mat rezultat = img;
    Mat rezultat = img.clone();

    for (int i = 0; i < img.rows; i += blockSize) {
        for (int j = 0; j < img.cols; j += blockSize) {

            int sumaB = 0, sumaG = 0, sumaR = 0;
            int numarPixeli = 0;

            for (int x = i; x < i + blockSize && x < img.rows; x++) {
                for (int y = j; y < j + blockSize && y < img.cols; y++) {
                    Vec3b pixel = img.at<Vec3b>(x, y);
                    sumaB += pixel[0];
                    sumaG += pixel[1];
                    sumaR += pixel[2];
                    numarPixeli++;
                }
            }

            // Culoare medie
            int medieB = sumaB / numarPixeli;
            int medieG = sumaG / numarPixeli;
            int medieR = sumaR / numarPixeli;

            // aplicam culoarea medie pe tot blocul
            for (int x = i; x < i + blockSize && x < img.rows; x++) {
                for (int y = j; y < j + blockSize && y < img.cols; y++) {
                    rezultat.at<Vec3b>(x, y)[0] = (uchar)medieB;
                    rezultat.at<Vec3b>(x, y)[1] = (uchar)medieG;
                    rezultat.at<Vec3b>(x, y)[2] = (uchar)medieR;
                }
            }
        }
    }

    return rezultat;
}


