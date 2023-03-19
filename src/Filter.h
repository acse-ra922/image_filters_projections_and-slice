//
// Created by Wang, Yuyang on 19/03/2023.
//

#include "Image.h"

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H


class Filter {
public:
    // Color Correction
    Image grayscale(const Image& img);
    Image auto_color_bal(const Image& img);
    Image brightness(const Image& img);
    Image hist_equal(const Image& img);

    // Image Blur
    Image median_blur(const Image& img);
    Image box_blur(const Image& img);
    Image gaussian_blur(const Image& img);

    // Edge Detection

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_FILTER_H
