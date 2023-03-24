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

//#include "Image.h"
#include "Volume.h"
#include "Slice.h"

using namespace std;

void test_slice();
void test_slice(Volume& v, std::string slice_plane, int slice_pos);
void test_yz_slice(Volume& v);
void test_xz_slice(Volume& v);

int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            std::cout << "Please run the command like: ./main_3Dslicing ../Scans/confuciusornis y-z 10" << std::endl;
            exit(0);
        }

        std::string inputDir = argv[1];
        std::string slice_plane = argv[2];
        std::string tmp = argv[3];
        int slice_pos = stoi(tmp);

        //std::string foldername = "../Scans/Scans/fracture";
        Volume v(inputDir);
        test_slice(v, slice_plane, slice_pos);


    }
    catch (invalid_argument) {
        cerr << "oops! Invalid arguments.\n";
    }

    return 0;
}

void test_slice(Volume& v, std::string slice_plane, int slice_pos) {
    int w, h, c;
    Slice s1(slice_plane, slice_pos, v);
    s1.get_slice_pic(v);

    std::string filename = "../Output/slicing/" + slice_plane + "_" + std::to_string(slice_pos) + ".png";

    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &c, 0);

    int new_h = v.get_height();
    int new_w = v.get_depth();
    int new_c = v.get_channel();

    assert(w == new_w && h == new_h && c == new_c);
}

void test_yz_slice(Volume& v) {
    int w, h, c;
    Slice s1("y-z", 10, v);
    s1.get_slice_pic(v);

    unsigned char* data = stbi_load("./y-z_10.png", &w, &h, &c, 0);

    int new_h = v.get_height();
    int new_w = v.get_depth();
    int new_c = v.get_channel();

    assert(w == new_w && h == new_h && c == new_c);
}

void test_xz_slice(Volume& v, std::string slice_plane, int slice_pos) {
    int w, h, c;
    Slice s2("x-z", 20, v);
    s2.get_slice_pic(v);

    unsigned char* data = stbi_load("./x-z_20.png", &w, &h, &c, 0);

    int new_h = v.get_depth();
    int new_w = v.get_width();
    int new_c = v.get_channel();

    assert(w == new_w && h == new_h && c == new_c);
}



//int main_4() {
//
//    std::string foldername = "/home/mm/acse_projects/advanced-programming-group-dijkstra/Scans/Scans/fracture";
//
//    Volume v(foldername);
//
//    std::string slice_plane = "x-z";
//    Slice s(slice_plane, 100);
//    s.get_slice_pic(v);
//
//
//
//    return 0;
//}


//int medianBlur(const char* filename, int w, int h, int c, const unsigned char* data, int kernel_size);
//int gaussianBlur(const char* filename, int w, int h, int c, const unsigned char* data, int kernel_size, double sigma);
////void gaussianBlur(int w, int h, int c, const unsigned char* data, int kernel_size, double sigma);
//
//void FilterCreation(double** GKernel, int kernel_size, double sigma);
//
//
//int main_1() {
//
//    int w, h, c;
//    unsigned char* data;
//
//    // Read in image file
//    data = stbi_load("/home/mm/acse_projects/advanced-programming-group-dijkstra/Images/dimorphos.png", &w, &h, &c, 0);
//
//    //std::cout << *data;
//
//    // Print image size to screen
//    std::cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl;
//
//    
//
//    // Save image to new filename
//    int kernel_size = 7;
//    int success = medianBlur("median_blur.png", w, h, c, data, kernel_size);
//    //stbi_write_png("output.png", w, h, c, data, 0);
//
//    // Deallocate memory
//    stbi_image_free(data);
//
//    return 0;
//}
//
//
//int medianBlur(const char* filename, int w, int h, int c, const unsigned char* data, int kernel_size) {
//    unsigned char* output = new unsigned char[w * h * c];
//    int k = kernel_size / 2;
//
//
//    for (int i = 0; i < h; i++) {
//        for (int j = 0; j < w; j++) {
//            for (int ch = 0; ch < c; ch++) {
//                vector<int> values;// outside
//
//
//                for (int ii = max(0, i - k); ii <= min(h - 1, i + k); ii++) {
//                    for (int jj = max(0, j - k); jj <= min(w - 1, j + k); jj++) {
//                        int idx = (ii * w + jj) * c + ch;
//                        values.push_back(data[idx]);// assign size // multiset sort
//                    }
//                }
//
//                sort(values.begin(), values.end());
//                int idx = (i * w + j) * c + ch;
//                output[idx] = values[values.size() / 2];
//            }
//        }
//    }
//
//    // Save image to new filename
//    int success = stbi_write_png(filename, w, h, c, output, w*c);
//    stbi_image_free(output);
//
//    return success;
//}
//
//
//int main_2() {
//
//    int w, h, c;
//    unsigned char* data;
//
//    // Read in image file
//    data = stbi_load("/home/mm/acse_projects/advanced-programming-group-dijkstra/Images/stinkbug.png", &w, &h, &c, 0);
//
//    //std::cout << *data;
//
//    // Print image size to screen
//    std::cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl;
//
//    // Save image to new filename
//    int kernel_size = 7;
//    double sigma = 3.0;
//
//    int success = gaussianBlur("gaussian_blur.png", w, h, c, data, kernel_size, sigma);
//    //gaussianBlur(w, h, c, data, 7, 3.0);
//
//
//    // Deallocate memory
//    stbi_image_free(data);
//
//    return 0;
//}
//
//
//
//int gaussianBlur(const char* filename, int w, int h, int c, const unsigned char* data, int kernel_size, double sigma)
//{
//    // Allocate memory for the output image
//    unsigned char* output = new unsigned char[w * h * c];
//
//    // Allocate memory for the Gaussian kernel
//    double** kernel = new double* [kernel_size];
//    for (int i = 0; i < kernel_size; i++) {
//        kernel[i] = new double[kernel_size];
//    }
//
//    // Compute the Gaussian kernel
//    FilterCreation(kernel, kernel_size, sigma);
//
//    int k = kernel_size / 2;
//
//
//    // Iterate over each pixel in the image
//    for (int i = 0; i < h; i++) {
//        for (int j = 0; j < w; j++) {
//            for (int ch = 0; ch < c; ch++) {
//                double sum = 0.0;
//                double weightSum = 0.0;
//
//                for (int ii = max(0, i - k); ii <= min(h - 1, i + k); ii++) {
//                    for (int jj = max(0, j - k); jj <= min(w - 1, j + k); jj++) {
//                        // kernel_value
//                        int m = ii - i + k;
//                        int l = jj - j + k;
//                        double weight = kernel[m][l];
//
//                        int idx = (ii * w + jj) * c + ch;
//                        sum += data[idx] * weight;
//                        //weightSum += weight;
//
//                    }
//                }
//
//                // Normalize the sum of pixel values by the sum of weights
//                int idx = (i * w + j) * c + ch;
//                output[idx] = static_cast<unsigned char>(sum);
//                //output[idx] = static_cast<unsigned char>(sum / weightSum);
//            }
//        }
//    }
//
//    // Write the output image to file
//    int success = stbi_write_png(filename, w, h, c, output, w * c);//filename
//
//    // Deallocate memory
//    stbi_image_free(output);
//    for (int i = 0; i < kernel_size; i++) {
//        delete[] kernel[i];
//    }
//    delete[] kernel;
//
//    return success;
//}
//
//
//// Function to create Gaussian filter
//void FilterCreation(double** GKernel, int kernel_size, double sigma)
//{
//    // initialising s
//    double r, s = 2.0 * sigma * sigma;
//
//    // sum is for normalization
//    double sum = 0.0;
//    int half_k = kernel_size / 2;
//
//    // generating kernel
//    for (int x = -half_k; x <= half_k; x++) {
//        for (int y = -half_k; y <= half_k; y++) {
//            r = x * x + y * y;
//            GKernel[x + half_k][y + half_k] = (exp(- r / s)) / (M_PI * s);
//            sum += GKernel[x + half_k][y + half_k];
//        }
//    }
//
//    // normalising the Kernel
//    for (int i = 0; i < kernel_size; ++i)
//        for (int j = 0; j < kernel_size; ++j)
//            GKernel[i][j] /= sum;
//}

