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

int main() {

//    // 3D Median/Gaussian
//    int filterSize = 3;
//    double sigma = 1.5;
//    std::string inputDir = "../Scans/confuciusornis";
//    std::string outputDir = "../Output/confuciusornis";
//
//    Volume vo(inputDir);
//
//    vo.Median3D(vo,outputDir, filterSize);
//    vo.Gaussian3D(vo, outputDir,filterSize,sigma);



    // Slicing
    try {
        std::string foldername = "../Scans/confuciusornis";
        Volume v(foldername);

        int w, h, c;
        Slice s1("y-z", 10, v);
        s1.get_slice_pic(v);

        unsigned char* data = stbi_load("../Output/slicing/y-z_10.png", &w, &h, &c, 0);

        int new_h = v.get_height();
        int new_w = v.get_depth();
        int new_c = v.get_channel();

        assert(w == new_w && h == new_h && c == new_c);
        stbi_image_free(data);


        Slice s2("x-z", 20, v);
        s2.get_slice_pic(v);

        data = stbi_load("../Output/slicing/x-z_20.png", &w, &h, &c, 0);

        new_h = v.get_depth();
        new_w = v.get_width();
        new_c = v.get_channel();

        assert(w == new_w && h == new_h && c == new_c);
    }
    catch (invalid_argument) {
        cerr << "oops! Invalid arguments.\n";
    }


    return 0;
}