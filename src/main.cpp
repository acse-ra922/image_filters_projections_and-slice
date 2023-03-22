// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.h"
#include "utils.h"
#include "Filter.h"

using namespace std;

int main() {

    int w, h, c;
    unsigned char *data;

    // Read in image file
    data = stbi_load("../Images/gracehopper.png", &w, &h, &c, 0);

    // Create Image object
    Image img(w, h, c, data);

    Filter f;

    // Color correction
    cout << "Color Correction: " << endl;
    f.auto_color_bal(img, 1.2, 1.0, 0.8);  // Increase red channel by 20%, decrease blue channel by 20%
    f.hist_equal(img);
    f.grayscale(img);
    f.brightness(img, 100.0);
    cout << endl;


    // Blur
    cout << "Blur: " << endl;
    //f.median_blur(img);
    f.box_blur(img, 5);
    f.gaussian_blur(img, 7, 3.0);
    cout << endl;

    //Image img2 = f.Sobel(img);
//    double* out = img.change2doubledata(data);
//    for(int i = 0; i < h; ++i){
//        for(int j=0; j<w; ++j){
//            cout << (out+i)[j] <<" ";
//        }
//        cout << endl;
//    }

    //cout << "hello" << endl;
    // Print image size to screen
    //cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << endl;

    // Save image to new filename and print log
//    int success = stbi_write_png("../Output/output.png", w, h, c, img.get_data(), 0);
//    if (success) { cout << "Succeed!" << endl; }
//    else { cout << "Error!" << endl; }

    // Deallocate memory
    stbi_image_free(data);

    // Read Pre-processed image
    data = stbi_load("../Images/output_gray.png", &w, &h, &c, 0);
    Image img2(w, h, c, data);

    // Edge detection
    cout << "Edge Detection:" << endl;
    f.Sobel(img2);
    f.Prewitt(img2);
    f.Scharr(img2);
    cout << endl;

    return 0;
}