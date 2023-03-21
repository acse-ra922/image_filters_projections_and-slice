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
    void auto_color_bal(Image img);
    void brightness(Image img, int brightness);
    void hist_equal(Image img);

    // Image Blur
    Image median_blur(const Image& img);
    Image box_blur(const Image& img);
    Image gaussian_blur(const Image& img);

    // Edge Detection
    void Sobel(Image img);

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
