//
// Created by Wang, Yuyang on 19/03/2023.
//

#include "Image.h"

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H


class Filter {
private:
    double * Gx;
    double * Gy;
    double * G;

public:
    // get methods
    double* get_gx();
    double* get_gy();
    double* get_g();

    // set methods
    void set_gx(double* gx);
    void set_gy(double* gy);
    void set_g(double* g);

    // Color Correction
    void grayscale(Image img);
    void auto_color_bal(Image img, double red_gain, double green_gain, double blue_gain);
    void brightness(Image img, double brightness);
    void hist_equal(Image img);

    // Image Blur
    void median_blur(Image img, int kernel=3);
    void box_blur(Image img, int kernel=3);
    void gaussian_blur(Image img, int kernel_size, double sigma);
    void FilterCreation(double** GKernel, int kernel_size, double sigma);

    // Edge Detection
    void conv_3_3_kernel(Image img, double* kx, double* ky, unsigned char* output);
    void Sobel(Image img);
    void Prewitt(Image img);
    void Scharr(Image img);

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
