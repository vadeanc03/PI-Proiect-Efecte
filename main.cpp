#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/efecte.h"

using namespace std;
using namespace cv;

int main() {
    // Încărcăm imaginea de test (ca imagine color)
    Mat imagine = imread("C:\\Users\\Cata\\Desktop\\An3_Semestrul2\\PI\\Proiect_PI_Special_Effects\\images\\tree.bmp", IMREAD_COLOR);
    if (imagine.empty()) {
        cout << "Eroare: imaginea nu a fost găsită sau este invalidă." << endl;
        return -1;
    }
    
    imshow("Imagine originală", imagine);
    waitKey(0);

    // inverted
    Mat img_invert = efect_invert(imagine.clone());
    imshow("Invert", img_invert);
    imwrite("output/invert.bmp", img_invert);
    waitKey(0);

    // monochrome
    Mat img_monocrom = efect_monocrom(imagine.clone());
    imshow("Monocrom", img_monocrom);
    imwrite("output/monocrom.bmp", img_monocrom);
    waitKey(0);

    // sepia
    Mat img_sepia = efect_sepia(imagine.clone());
    imshow("Sepia", img_sepia);
    imwrite("output/sepia.bmp", img_sepia);
    waitKey(0);

    // blur
    Mat img_blur = efect_blur(imagine.clone());
    imshow("Blur", img_blur);
    imwrite("output/blur.bmp", img_blur);
    waitKey(0);

    // desaturare
    Mat img_desat = efect_desaturare(imagine.clone());
    imshow("Desaturare", img_desat);
    imwrite("output/desaturare.bmp", img_desat);
    waitKey(0);

    //posterize
    Mat img_poster = efect_posterize(imagine.clone(), 6);  // 6 culori
    imshow("Posterize", img_poster);
    imwrite("output/posterize.bmp", img_poster);
    waitKey(0);

    //pixelate
    Mat img_pixel = efect_pixelate(imagine.clone(), 10);  // blocuri de 10x10
    imshow("Pixelate", img_pixel);
    imwrite("output/pixelate.bmp", img_pixel);
    waitKey(0);


    return 0;
}
