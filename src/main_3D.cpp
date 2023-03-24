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


#include "Volume.h"
#include "Slice.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc!=3){
        std::cout << "Please run the command like: ./3Dfilter ../Scans/confuciusornis ../Output/confuciusornis" << std::endl;
    }

    // 3D Median/Gaussian
    int median_filterSize = 5;
    int gaussian_filterSize = 3;
    double sigma = 2.0;
    std::string inputDir = argv[1];
    std::string outputDir = argv[2];

    Volume vo(inputDir);

    std::cout << "Gaussian 3D (3*3*3), sigma=2.0" << std::endl;
    vo.Gaussian3D(vo, outputDir,gaussian_filterSize, sigma);

    std::cout << "Median 3D (5*5*5)" << std::endl;
    vo.Median3D(vo,outputDir, median_filterSize);



//    // Slicing
//    try {
//        std::string foldername = "../Scans/confuciusornis";
//        Volume v(foldername);
//
//        int w, h, c;
//        Slice s1("y-z", 10, v);
//        s1.get_slice_pic(v);
//
//        unsigned char* data = stbi_load("../Output/slicing/y-z_10.png", &w, &h, &c, 0);
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
//        data = stbi_load("../Output/slicing/x-z_20.png", &w, &h, &c, 0);
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