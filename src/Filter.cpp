//
// Created by Wang, Yuyang on 19/03/2023.
//

#include <iostream>
#include "Filter.h"
#include "utils.h"
#include <algorithm> // std::max, std::min
#include "stb_image.h"
#include "stb_image_write.h"

// Color Correction
void Filter::grayscale(Image img) {

    // initialization
    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();
    unsigned char* grayData = new unsigned char[w * h];

    // Calculate grayscale values for each pixel
    for (int i = 0; i < w*h; i++) {
        int gray = 0.299 * data[i * c] + 0.587 * data[i * c + 1] + 0.114 * data[i * c + 2];
        grayData[i] = std::max(0, std::min(255, gray));
    }

    // Set the number of channels to 1
    c = 1;

    // Save image to new filename
    int success = stbi_write_png("../Output/output_gray.png", w, h, c, grayData, w);
    if (success) { std::cout << "Grayscale Succeed!" << std::endl; }
    else { std::cout << "Grayscale Error!" << std::endl; }


    // Deallocate memory
    //stbi_image_free(grayData);
    delete[] grayData;
}

void Filter::auto_color_bal(Image img) {

    // initialization
    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();

    // Allocate memory
    unsigned char* balData = new unsigned char[w * h * c];

    for(int i=0; i<w*h*c; ++i){
        balData[i] = data[i];
    }

    const float red_gain = 1.2f;   // Adjust red channel by 20%
    const float green_gain = 1.0f; // No adjustment to green channel
    const float blue_gain = 0.8f;  // Adjust blue channel by 20%
    for (int i = 0; i < w * h * c; i += c) {
        int r = balData[i];
        int g = balData[i + 1];
        int b = balData[i + 2];
        balData[i] = std::min(255, (int)(r * red_gain));
        balData[i + 1] = std::min(255, (int)(g * green_gain));
        balData[i + 2] = std::min(255, (int)(b * blue_gain));
    }
    std::cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl;

    // Save image to new filename
    int success = stbi_write_png("../Output/output_bal.png", w, h, c, balData, 0);
    if (success) { std::cout << "Auto Color Balance Succeed!" << std::endl; }
    else { std::cout << "Auto Color Balance Error!" << std::endl; }

    // Deallocate memory
    delete[] balData;
}

void Filter::brightness(Image img, int brightness) {

    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();

    // Allocate memory
    unsigned char* brightData = new unsigned char[w * h * c];

    // Calculate average pixel value
    int total = 0;
    for (int i = 0; i < w * h * c; i++) {
        total += data[i];
    }
    int avg = total / (w * h * c);

    // Calculate brightness adjusted values for each pixel
    for (int i = 0; i < w * h * c; i++) {
        int val = data[i] + brightness;
        if (brightness == 0) {
            // Automatic brightness adjustment
            if (data[i] < 128) {
                val = data[i] * (128 / avg);
            }
            else {
                val = data[i] + (255 - data[i]) * (128 / (255 - avg));
            }
        }
        brightData[i] = std::max(0, std::min(255, val));
    }


    // Save image to new filename
    int success = stbi_write_png("../Output/output_bright.png", w, h, c, brightData, w*c);
    if (success) { std::cout << "Brightness Succeed!" << std::endl; }
    else { std::cout << "Brightness Error!" << std::endl; }

    // Deallocate memory
    delete[] brightData;
}

void Filter::hist_equal(Image img) {

    // initialization
    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();

    unsigned char* histData = new unsigned char[w * h * c];

    for(int i=0; i<w*h*c; ++i){
        histData[i] = data[i];
    }

    // Calculate histogram
    int hist[256] = { 0 };
    for (int i = 0; i < w * h * c; i += c) {
        int r = histData[i];
        int g = histData[i + 1];
        int b = histData[i + 2];
        hist[r]++;
        hist[g]++;
        hist[b]++;
    }

    // Compute CDF
    int cdf[256] = { 0 };
    int sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += hist[i];
        cdf[i] = sum;
    }

    // Normalize intensities
    float factor = 255.0f / (w * h * c);
    for (int i = 0; i < w * h * c; i += c) {
        int r = histData[i];
        int g = histData[i + 1];
        int b = histData[i + 2];
        histData[i] = std::min(255, (int)(cdf[r] * factor));
        histData[i + 1] = std::min(255, (int)(cdf[g] * factor));
        histData[i + 2] = std::min(255, (int)(cdf[b] * factor));
    }

    // Save image to new filename
    int success = stbi_write_png("../Output/output_hist.png", w, h, c, histData, 0);
    if (success) { std::cout << "Hist Equal Succeed!" << std::endl; }
    else { std::cout << "Hist Equal Error!" << std::endl; }

    // Deallocate memory
    delete[] histData;
}


// Edge Detection
Image Filter::Sobel(Image img) {
    double kernel_x[3*3] = {-1, 0, -1, -2, 0, 2, -1, 0, 1};
    double kernel_y[3*3] = {-1, -2, -1,0, 0, 0,1, 2, 1};

    double* d_data = img.change2doubledata(img.get_data()); // double data, 2D array

    double* gx = img.conv(d_data,kernel_x);
    double* gy = img.conv(d_data,kernel_y);

    this->Gx = gx;
    this->Gy = gy;

    return img;
}