//
// Created by Wang, Yuyang on 19/03/2023.
//

#include <iostream>
#include "Filter.h"
#include "utils.h"
#include <cmath> // std::max, std::min
#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>

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


// Blur
void Filter::median_blur(Image img, int kernel) {

    // initialization
    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();
    int k = kernel;

    unsigned char* output_data = new unsigned char[w * h * c];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int ch = 0; ch < c; ch++) {
                std::vector<int> values;
                for (int ii = std::max(0, i - k); ii <= std::min(h - 1, i + k); ii++) {
                    for (int jj = std::max(0, j - k); jj <= std::min(w - 1, j + k); jj++) {
                        int idx = (ii * w + jj) * c + ch;
                        values.push_back(data[idx]);
                    }
                }
                std::sort(values.begin(), values.end());
                int idx = (i * w + j) * c + ch;
                output_data[idx] = values[values.size() / 2];
            }
        }
    }

    // Write output image file
    int success = stbi_write_png("../Output/output_medianblur.png", w, h, c, output_data, w * c);
    if (success) { std::cout << "Median Blur Succeed!" << std::endl; }
    else { std::cout << "Median Blur Error!" << std::endl; }

    // Free memory
    delete[] output_data;
}


// Edge Detection

void Filter::conv_3_3_kernel(Image img, double* kx, double* ky, unsigned char* output) {

    // Initialization
    int w = img.get_width();
    int h = img.get_height();
    unsigned char* data = img.get_data();
    unsigned char* p_data = img.padding(data);

    for (int x = 1; x < h - 1; x++) {
        for (int y = 1; y < w - 1; y++) {

            // Compute Gx and Gy values using convolution
            double Gx = 0.0, Gy = 0.0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    double pixel = p_data[(x + i) * w + (y + j)];
                    Gx += kx[(i + 1)*3+(j + 1)] * pixel;
                    Gy += ky[(i + 1)*3+(j + 1)] * pixel;
                }
            }

            // Compute gradient magnitude and direction
            double magnitude = std::min(255.0, sqrt(Gx * Gx + Gy * Gy));
            output[x * w + y] = static_cast<unsigned char>(magnitude);
        }
    }



}

void Filter::Sobel(Image img) {

    // set kernel
    double kx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    double ky[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();

    unsigned char* output = new unsigned char[w*h];
    this->conv_3_3_kernel(img, kx, ky, output);

    // Save image to new filename
    int success = stbi_write_png("../Output/output_sobel.png", w, h, c, output, w);
    if (success) { std::cout << "Sobel Succeed!" << std::endl; }
    else { std::cout << "Sobel Error!" << std::endl; }


    // Deallocate memory
    delete[] output;

}

void Filter::Prewitt(Image img) {

    // set kernel
    double kx[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    double ky[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();

    unsigned char* output = new unsigned char[w*h];
    this->conv_3_3_kernel(img, kx, ky, output);

    // Save image to new filename
    int success = stbi_write_png("../Output/output_prewitt.png", w, h, c, output, w);
    if (success) { std::cout << "Prewitt Succeed!" << std::endl; }
    else { std::cout << "Prewitt Error!" << std::endl; }


    // Deallocate memory
    delete[] output;

}

void Filter::Scharr(Image img) {

    // set kernel
    double kx[9] = {-3, 0, 3, -10, 0, 10, -3, 0, 3};
    double ky[9] = {-3, -10, -3, 0, 0, 0, 3, 10, 3};

    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();

    unsigned char* output = new unsigned char[w*h];
    this->conv_3_3_kernel(img, kx, ky, output);

    // Save image to new filename
    int success = stbi_write_png("../Output/output_scharr.png", w, h, c, output, w);
    if (success) { std::cout << "Scharr Succeed!" << std::endl; }
    else { std::cout << "Scharr Error!" << std::endl; }


    // Deallocate memory
    delete[] output;
}
