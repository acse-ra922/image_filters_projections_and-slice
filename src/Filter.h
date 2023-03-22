//
// Created by Wang, Yuyang on 19/03/2023.
//

#include "Image.h"

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H


class Filter {
public:

    // color correction
    void grayscale(Image img);
    void auto_color_bal(Image img);
    void brightness(Image img, double brightness=50.0);
    void hist_equal(Image img);

    // image blur
    void median_blur(Image img, int kernel=3);
    void box_blur(Image img, int kernel=3);
    void gaussian_blur(Image img, int kernel_size, double sigma);
    void FilterCreation(double** GKernel, int kernel_size, double sigma);

    // edge detection
    void conv_3_3_kernel(Image img, double* kx, double* ky, unsigned char* output);
    void conv_any_kernel(Image img, double* kernel);
    void Sobel(Image img);
    void Prewitt(Image img);
    void Scharr(Image img);
    void Roberts(Image img);

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
