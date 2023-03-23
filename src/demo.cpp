// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


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
#include "Slice.h"
#include "utils.h"

using namespace std;

int main() {

    int w, h, c;
    unsigned char *data;

// Test Filter, Image Class

//    // Read in image file
//    data = stbi_load("../Images/vh_ct.png", &w, &h, &c, 0);
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
//
//
//    // Read Pre-processed image
//    data = stbi_load("../Output/output_gray.png", &w, &h, &c, 0);
//    Image img2(w, h, c, data);
//
//    f.gaussian_blur(img2, 3, 1.5);
//    stbi_image_free(data);
//
//

//    data = stbi_load("../Output/output_gauss.png", &w, &h, &c, 0);
//    Image img3(w, h, c, data);
//
//    // Edge detection
//    cout << "Edge Detection:" << endl;
//    f.Sobel(img3);
//    f.Prewitt(img3);
//    f.Scharr(img3);
//    f.Roberts(img3);
//    cout << endl;
//
//    stbi_image_free(data);


// Test Volume Class

    int filterSize = 3;
    double sigma = 1.5;
    std::string inputDir = "../Scans/confuciusornis";
    std::string outputDir = "../Output/confuciusornis";

    Volume vo(inputDir);

    vo.Median3D(vo,outputDir, filterSize);
    vo.Gaussian3D(vo, outputDir,filterSize,sigma);



// Test Slice Class

//    try {
//        std::string foldername = "../Scans/confuciusornis";
//        Volume v(foldername);
//
//        int w, h, c;
//        Slice s1("y-z", 10, v);
//        s1.get_slice_pic(v);
//
//        unsigned char* data = stbi_load("./y-z_10.png", &w, &h, &c, 0);
//
//        int new_h = v.get_height();
//        int new_w = v.get_depth();
//        int new_c = v.get_channel();
//
//        assert(w == new_w && h == new_h && c == new_c);
//        stbi_image_free(data);
//
//
//        Slice s2("x-z", 20, v);
//        s2.get_slice_pic(v);
//
//        data = stbi_load("./x-z_20.png", &w, &h, &c, 0);
//
//        new_h = v.get_depth();
//        new_w = v.get_width();
//        new_c = v.get_channel();
//
//        assert(w == new_w && h == new_h && c == new_c);
//    }
//    catch (invalid_argument) {
//        cerr << "oops! Invalid arguments.\n";
//    }


    return 0;
}