// TestSuite.cpp
// Driver automatizat pentru testarea efectelor și măsurarea performanței

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <filesystem>
#include "C:\Users\Cata\Desktop\An3_Semestrul2\PI\Proiect_PI_Special_Effects\src\efecte.h"
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;
using namespace std;
using namespace cv;
using Clock = chrono::high_resolution_clock;

struct Result {
    string effect;
    string image;
    double time_ms;
    bool success;
};

int main() {
    // Colectam toate fisierele din tests/inputs
    vector<string> imgs;
    for (auto& entry : fs::directory_iterator("tests/inputs")) {
        if (entry.is_regular_file())
            imgs.push_back(entry.path().string());
    }

    vector<Result> results;

    // Pt fiecare imagine, aplicam toate efectele
    for (auto& path : imgs) {
        Mat img = imread(path, IMREAD_COLOR);
        if (img.empty()) {
            // eroare la incarcarea imaginii
            results.push_back({"LOAD_FAIL", fs::path(path).filename().string(), 0.0, false});
            continue;
        }

        auto runTest = [&](auto func, const string& name) {
            auto t0 = Clock::now();
            Mat out = func(img);
            auto t1 = Clock::now();
            double ms = chrono::duration<double, milli>(t1 - t0).count();
            bool ok = (out.size() == img.size());
            results.push_back({name, fs::path(path).filename().string(), ms, ok});
        };

        runTest(efect_invert,     "invert");
        runTest(efect_monocrom,   "monocrom");
        runTest(efect_sepia,      "sepia");
        runTest(efect_blur,       "blur");
        runTest(efect_desaturare, "desaturare");
        runTest([&](const Mat& m){ return efect_posterize(m, 6); },  "posterize");
        runTest([&](const Mat& m){ return efect_pixelate(m, 10); },  "pixelate");
    }

    // Scriem rezultatele într-un CSV
    ofstream csv("tests/results.csv");
    csv << "effect,image,time_ms,success\n";
    for (auto& r : results) {
        csv << r.effect << ","
            << r.image  << ","
            << r.time_ms<< ","
            << (r.success ? 1 : 0)
            << "\n";
    }

    cout << "Testele s-au terminat. Vezi tests/results.csv" << endl;
    return 0;
}
