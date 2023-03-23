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

    // Allocate memory
    unsigned char* grayData = new unsigned char[w * h];

    // Calculate grayscale values for each pixel
    for (int i = 0; i < w*h; i++) {
        double gray = 0.299 * data[i * c] + 0.587 * data[i * c + 1] + 0.114 * data[i * c + 2];
        grayData[i] = static_cast<unsigned char>(std::max(0.0, std::min(255.0, gray)));
    }

    // Set the number of channels to 1
    c = 1;

    // Save image to new filename
    int success = stbi_write_png("../Output/output_gray.png", w, h, c, grayData, w*c);
    if (success) { std::cout << "Grayscale Succeed!" << std::endl; }
    else { std::cout << "Grayscale Error!" << std::endl; }


    // Deallocate memory
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

    // copy the data
    for(int i=0; i<w*h*c; ++i){
        balData[i] = data[i];
    }

    // Calculate histogram
    double sumR = 0;
    double sumG = 0;
    double sumB = 0;

    for (int i = 0; i < w * h * c; i += c) {
        sumR += static_cast<double>(balData[i]);
        sumG += static_cast<double>(balData[i + 1]);
        sumB += static_cast<double>(balData[i + 2]);
    }

    // Compute CDF
    double ratioR = sumR/w/h/127;
    double ratioG = sumG/w/h/127;
    double ratioB = sumB/w/h/127;

    for (int i = 0; i < w * h * c; i += c) {
        double r = static_cast<double>(balData[i]);
        double g = static_cast<double>(balData[i + 1]);
        double b = static_cast<double>(balData[i + 2]);

        balData[i] = static_cast<unsigned char>(std::min(255.0, std::max(0.0,r * ratioR)));
        balData[i + 1] = static_cast<unsigned char>(std::min(255.0, std::max(0.0,g * ratioG)));
        balData[i + 2] = static_cast<unsigned char>(std::min(255.0, std::max(0.0,b * ratioB)));
    }

    // Save image to new filename
    int success = stbi_write_png("../Output/output_bal.png", w, h, c, balData, w*c);
    if (success) { std::cout << "Auto Color Balance Succeed!" << std::endl; }
    else { std::cout << "Auto Color Balance Error!" << std::endl; }

    // Deallocate memory
    delete[] balData;
}

void Filter::brightness(Image img, double brightness) {

    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();

    // Allocate memory
    unsigned char* brightData = new unsigned char[w * h * c];

    // Calculate average pixel value
    double total = 0.0;
    for (int i = 0; i < w * h * c; i++) {
        total += static_cast<double>(data[i]);
    }
    double avg = total / (w * h * c);

    // Calculate brightness adjusted values for each pixel
    for (int i = 0; i < w * h * c; i++) {
        double val = static_cast<double>(data[i]) + brightness;
        if (brightness == 0.0) {
            // Automatic brightness adjustment
            if (data[i] < 128) {
                val = data[i] * (128 / avg);
            }
            else {
                val = data[i] + (255 - data[i]) * (128 / (255 - avg));
            }
        }
        brightData[i] = static_cast<unsigned char>(std::max(0.0, std::min(255.0, val)));
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

    // Allocate memory
    unsigned char* histData = new unsigned char[w * h * c];

    // copy the data
    for(int i=0; i<w*h*c; ++i){
        histData[i] = data[i];
    }

    // Calculate histogram
    int hist[256] = { 0 };
    for (int i = 0; i < w * h * c; i += c) {
        int r = static_cast<int>(data[i]);
        int g = static_cast<int>(data[i + 1]);
        int b = static_cast<int>(data[i + 2]);
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
    double factor = 255.0 / (w * h * c);
    for (int i = 0; i < w * h * c; i += c) {
        int r = static_cast<int>(histData[i]);
        int g = static_cast<int>(histData[i + 1]);
        int b = static_cast<int>(histData[i + 2]);
        histData[i] = static_cast<unsigned char>(std::min(255.0, (cdf[r] * factor)));
        histData[i + 1] = static_cast<unsigned char>(std::min(255.0, (cdf[g] * factor)));
        histData[i + 2] = static_cast<unsigned char>(std::min(255.0, (cdf[b] * factor)));
    }

    // Save image to new filename
    int success = stbi_write_png("../Output/output_hist.png", w, h, c, histData, w*c);
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


    //double ke[25] = {0.04, 0.04, 0.04,0.04, 0.04, 0.04, 0.04,0.04, 0.04, 0.04,0.04, 0.04, 0.04, 0.04,0.04, 0.04, 0.04,0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04};

    //this->conv_any_kernel(img, ke, 5, output_data);

    // Write output image file
    int success = stbi_write_png("../Output/output_medianblur.png", w, h, c, output_data, w * c);
    if (success) { std::cout << "Median Blur Succeed!" << std::endl; }
    else { std::cout << "Median Blur Error!" << std::endl; }

    // Free memory
    delete[] output_data;
}

void Filter::box_blur(Image img, int kernel) {

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
                int sum = 0;
                for (int ii = std::max(0, i - k); ii <= std::min(h - 1, i + k); ii++) {
                    for (int jj = std::max(0, j - k); jj <= std::min(w - 1, j + k); jj++) {
                        int idx = (ii * w + jj) * c + ch;
                        sum += data[idx];
                    }
                }
                int idx = (i * w + j) * c + ch;
                output_data[idx] = sum / ((2 * k + 1) * (2 * k + 1));
            }
        }
    }

    // Write output image file
    int success = stbi_write_png("../Output/output_boxblur.png", w, h, c, output_data, w * c);
    if (success) { std::cout << "Box Blur Succeed!" << std::endl; }
    else { std::cout << "Box Blur Error!" << std::endl; }

    // Free memory
    delete[] output_data;
}

void Filter::FilterCreation(double **GKernel, int kernel_size, double sigma) {
    double r, s = 2.0 * sigma * sigma;
    double sum = 0.0;
    int half_k = kernel_size / 2;
    for (int x = -half_k; x <= half_k; x++) {
        for (int y = -half_k; y <= half_k; y++) {
            r = x * x + y * y;
            GKernel[x + half_k][y + half_k] = (exp(-r / s)) / (M_PI * s);
            sum += GKernel[x + half_k][y + half_k];
        }
    }
    for (int i = 0; i < kernel_size; ++i) {
        for (int j = 0; j < kernel_size; ++j) {
            GKernel[i][j] /= sum;
        }
    }
}

void Filter::gaussian_blur(Image img, int kernel_size, double sigma) {

    // initialization
    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();

    // Allocate memory for the output image
    unsigned char* output = new unsigned char[w * h * c];

    // Allocate memory for the Gaussian kernel
    double** kernel = new double* [kernel_size];
    for (int i = 0; i < kernel_size; i++) {
        kernel[i] = new double[kernel_size];
    }

    // Compute the Gaussian kernel
    FilterCreation(kernel, kernel_size, sigma);

    int k = kernel_size / 2;

    // Iterate over each pixel in the image
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int ch = 0; ch < c; ch++) {
                double sum = 0.0;
                double weightSum = 0.0;

                for (int ii = std::max(0, i - k); ii <= std::min(h - 1, i + k); ii++) {
                    for (int jj = std::max(0, j - k); jj <= std::min(w - 1, j + k); jj++) {
                        // kernel_value
                        int m = ii - i + k;
                        int l = jj - j + k;
                        double weight = kernel[m][l];

                        sum += data[(ii * w + jj) * c + ch] * weight;
                        weightSum += weight;
                    }
                }

                // Normalize the sum of pixel values by the sum of weights
                output[(i * w + j) * c + ch] = static_cast<unsigned char>(sum / weightSum);
            }
        }
    }

    // Write the output image to file
    int success = stbi_write_png("../Output/output_gauss.png", w, h, c, output, w * c);
    if (success) { std::cout << "Gaussian Blur Succeed!" << std::endl; }
    else { std::cout << "Gaussian Blur Error!" << std::endl; }

    for (int i = 0; i < kernel_size; i++) {
        delete[] kernel[i];
    }
    delete[] kernel;

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
    int success = stbi_write_png("../Output/output_sobel.png", w, h, c, output, w*c);
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
    int success = stbi_write_png("../Output/output_prewitt.png", w, h, c, output, w*c);
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
    int success = stbi_write_png("../Output/output_scharr.png", w, h, c, output, w*c);
    if (success) { std::cout << "Scharr Succeed!" << std::endl; }
    else { std::cout << "Scharr Error!" << std::endl; }


    // Deallocate memory
    delete[] output;
}

void Filter::Roberts(Image img) {

    int w = img.get_width();
    int h = img.get_height();
    int c = img.get_channel();
    unsigned char* data = img.get_data();
    unsigned char* output = new unsigned char[w*h];

    // Apply Roberts cross filter
    for (int i = 0; i < w - 1; i++)
    {
        for (int j = 0; j < h - 1; j++)
        {
            double pixel_top_left = static_cast<double>(data[(j * w + i)]);
            double pixel_top_right = static_cast<double>(data[(j * w + i + 1)]);
            double pixel_bottom_left = static_cast<double>(data[((j + 1) * w + i)]);
            double pixel_bottom_right = static_cast<double>(data[((j + 1) * w + i + 1)]);

            double value = std::abs(pixel_top_left - pixel_bottom_right) +
                                 std::abs(pixel_top_right - pixel_bottom_left);

            // Set the pixel value after applying the filter
            output[(j * w + i)] = static_cast<unsigned char>(value);
        }
    }

    // Save image to new filename
    int success = stbi_write_png("../Output/output_roberts.png", w, h, c, output, w*c);
    if (success) { std::cout << "Roberts Succeed!" << std::endl; }
    else { std::cout << "Roberts Error!" << std::endl; }

    // Deallocate memory
    delete[] output;
}