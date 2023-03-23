// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include <iostream>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.h"
#include "Volume.h"
#include "Filter.h"

using namespace std;

int main() {

    int w, h, c;
    unsigned char *data;

//    // Read in image file
//    data = stbi_load("../Images/gracehopper.png", &w, &h, &c, 0);
//
//    // Create Image object
//    Image img(w, h, c, data);
//
//    Filter f;
//
//    // Color correction
//    cout << "Color Correction: " << endl;
//    f.auto_color_bal(img);
//    f.hist_equal(img);
//    f.grayscale(img);
//    f.brightness(img, 100.0);
//    cout << endl;
//
//
//    // Blur
//    cout << "Blur: " << endl;
//    f.median_blur(img);
//    f.box_blur(img, 5);
//    f.gaussian_blur(img, 7, 3.0);
//    cout << endl;
//
//    // Deallocate memory
//    stbi_image_free(data);
//
//    // Read Pre-processed image
//    data = stbi_load("../Images/output_gray.png", &w, &h, &c, 0);
//    Image img2(w, h, c, data);
//
//    // Edge detection
//    cout << "Edge Detection:" << endl;
//    f.Sobel(img2);
//    f.Prewitt(img2);
//    f.Scharr(img2);
//    f.Roberts(img2);
//    cout << endl;



    int filterSize = 3;
    double sigma = 1.5;
    std::string inputDir = "../Scans/ex";
    std::string outputDir = "../Output/fracture";

    Volume vo(inputDir);

//    for(int i=0; i<vo.get_outdir().size(); ++i)
//        std::cout << vo.get_outdir()[i] << std::endl;

    vo.Median3D(vo,outputDir,filterSize);

    return 0;
}