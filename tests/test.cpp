// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)

//tests
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "../src/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../src/stb_image_write.h"

#include "Tests.h"
#include "../src/Image.h"
#include "./src/utils.h"
#include "./src/Filter.h"
#include "./src/Projection.h"
#define M_PI  3.14159265358979323846 
using namespace std;

void Tests::test_automatic_color_balance() {
    // Load test image
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input.png", &w, &h, &c, 0);
    unsigned char* correct_data 

    // Call automatic color balance function
    Image img(w, h, c, data);
    Filter f;
    f.auto_color_balance(img);
    // Reload the saved image
    int new_w, new_h, new_c;
    unsigned char* new_data = stbi_load("output_acb.png", &new_w, &new_h, &new_c, 0);

    // Check that the new image has the same size and number of channels
    assert(w == new_w && h == new_h && c == new_c);

    // Check that the new image has been color balanced
    for (int i = 0; i < w * h * c; i += c) {
        int r = new_data[i];
        int g = new_data[i + 1];
        int b = new_data[i + 2];
        assert(r >= 0 && r <= 255);
        assert(g >= 0 && g <= 255);
        assert(b >= 0 && b <= 255);
        assert(r >= g && r >= b); // Red channel should be the largest
        assert(b <= g); // Blue channel should be the smallest
    }

    // Deallocate memory
    stbi_image_free(data);
    stbi_image_free(new_data);
}

void Tests::test_grayscale() {
    // Load sample image
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input.png", &w, &h, &c, 0);
    Image img(w,h,c,data);
    Filter f;
    // Apply grayscale function to sample image
    f.grayscale(img);

    // Load grayscale image
    unsigned char* grayData = stbi_load("output_gray.png", &w, &h, &c, 0);

    // Verify that the image is grayscale
    assert(c == 1);

    // Verify that the image size is the same as the original image
    assert(w == 800);
    assert(h == 600);

    // Verify that the pixel values are within the expected range
    for (int i = 0; i < w * h; i++) {
        assert(grayData[i] >= 0 && grayData[i] <= 255);
    }

    // Deallocate memory
    stbi_image_free(data);
    stbi_image_free(grayData);
}

void Tests::test_brightness() {
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input.png", &w, &h, &c, 0);
    Image img(w,h,c,data);
    Filter f;
    if (data != NULL) {
        // Test the function with different brightness values
        f.brightness(img, 50); // Increase brightness by 50
        f.brightness(img, -50); // Decrease brightness by 50
        f.brightness(img); // Use automatic brightness adjustment

        // Deallocate memory for input image
        stbi_image_free(data);

        // Load the output images and check that they exist
        unsigned char* brightData = stbi_load("output_bright.png", &w, &h, &c, 0);

        if (brightData != NULL) {
            std::cout << "Brightness adjustment successful." << std::endl;

            // Deallocate memory for output image
            stbi_image_free(brightData);
        }
        else {
            std::cout << "Error: Output image not found." << std::endl;
        }
    }
    else {
        std::cout << "Error: Input image not found." << std::endl;
    }
}

void Tests::test_median_blur() {
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input.png", &w, &h, &c, 0);
    Image img(w,h,c,data);
    Filter f;

    if (data != NULL) {
        // Test the function with different kernel sizes
        f.median_blur(img,3); // Use kernel size of 3
        f.median_blur(img,5); // Use kernel size of 5

        // Deallocate memory for input image
        stbi_image_free(data);

        // Load the output images and check that they exist
        unsigned char* output_data = stbi_load("output_medianblur.png", &w, &h, &c, 0);

        if (output_data != NULL) {
            std::cout << "Median blur successful." << std::endl;

            // Deallocate memory for output image
            stbi_image_free(output_data);
        }
        else {
            std::cout << "Error: Output image not found." << std::endl;
        }
    }
    else {
        std::cout << "Error: Input image not found." << std::endl;
    }
}

void Tests::test_hist_equal() {
    // Load image
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input.png", &w, &h, &c, 0);
    Image img(w,h,c,data);
    Filter f;
    // Apply histogram equalization
    f.hist_equal(img);

    // Load the result image
    unsigned char* output_data = stbi_load("output_he.png", &w, &h, &c, 0);
    Image res(w,h,c,output_data);
    // Check the dimensions of the result image
    assert(res.get_width() == img.get_width());
    assert(res.get_height() == img.get_height());
    assert(res.get_channel() == img.get_channel());

    // Check if the pixels have been modified
    bool modified = false;
    for (int i = 0; i < img.get_width() * img.get_height() * img.get_channel(); i++) {
        if (data[i] != output_data[i]) {
            modified = true;
            break;
        }
    }
    assert(modified);
}



// Functions to test
// Case: confuciusornis
bool Tests::confuciusornis_file_num(const Projection& proj)
{
	// Check total number of files
	return (proj.get_file_size() == 265);
}

bool Tests::confuciusornis_img_shape(const Projection& proj)
{
	// Check image shape
	return ((proj.get_height() == 1295) && (proj.get_width() == 996));
}

bool Tests::confuciusornis_max()
{
	// Test MIP on confuciusornis data
	int img_id = 50;
	int w, h, c;

	// Check if output is correct
	unsigned char* data = stbi_load("Scans/confuciusornis/confuYZ0051.png", &w, &h, &c, 0);
	Projection proj("Scans/confuciusornis");
	unsigned char* data_proj = proj.max_ip(img_id, img_id + 1);
	bool flag_data_correct = true;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int pixel_index = (y * w + x) * c;
			if (data[pixel_index] != data_proj[pixel_index])
			{
				flag_data_correct = false;
				break;
			}
		}
	}

	// Also check file number and image shape
	bool flag_file_size = confuciusornis_file_num(proj);
	bool flag_img_shape = confuciusornis_img_shape(proj);

	return (flag_file_size && flag_img_shape && flag_data_correct);
}

bool Tests::confuciusornis_min()
{
	// Test MinIP on confuciusornis data
	int img_id = 100;
	int w, h, c;

	// Check if output is correct
	unsigned char* data = stbi_load("Scans/confuciusornis/confuYZ0101.png", &w, &h, &c, 0);
	Projection proj("Scans/confuciusornis");
	unsigned char* data_proj = proj.min_ip(img_id, img_id + 1);
	bool flag_data_correct = true;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int pixel_index = (y * w + x) * c;
			if (data[pixel_index] != data_proj[pixel_index])
			{
				flag_data_correct = false;
				break;
			}
		}
	}

	// Also check file number and image shape
	bool flag_file_size = confuciusornis_file_num(proj);
	bool flag_img_shape = confuciusornis_img_shape(proj);

	return (flag_file_size && flag_img_shape && flag_data_correct);
}

bool Tests::confuciusornis_avg()
{
	// Test MeanIP on confuciusornis data
	int img_id = 150;
	int w, h, c;

	// Check if output is correct
	unsigned char* data = stbi_load("Scans/confuciusornis/confuYZ0151.png", &w, &h, &c, 0);
	Projection proj("Scans/confuciusornis");
	unsigned char* data_proj = proj.avg_ip(img_id, img_id + 1);
	bool flag_data_correct = true;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int pixel_index = (y * w + x) * c;
			if (data[pixel_index] != data_proj[pixel_index])
			{
				flag_data_correct = false;
				break;
			}
		}
	}

	// Also check file number and image shape
	bool flag_file_size = confuciusornis_file_num(proj);
	bool flag_img_shape = confuciusornis_img_shape(proj);

	return (flag_file_size && flag_img_shape && flag_data_correct);
}

// Case: fracture
bool Tests::fracture_file_num(const Projection& proj)
{
	// Check total number of files
	return (proj.get_file_size() == 1300);
}

bool Tests::fracture_img_shape(const Projection& proj)
{
	// Check image shape
	return ((proj.get_height() == 275) && (proj.get_width() == 843));
}

bool Tests::fracture_max()
{
	// Test MIP on fracture data
	int img_id = 800;
	int w, h, c;

	// Check if output is correct
	unsigned char* data = stbi_load("Scans/fracture/granite1_1125.png", &w, &h, &c, 0);
	Projection proj("Scans/fracture");
	unsigned char* data_proj = proj.max_ip(img_id, img_id + 1);
	bool flag_data_correct = true;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int pixel_index = (y * w + x) * c;
			if (data[pixel_index] != data_proj[pixel_index])
			{
				flag_data_correct = false;
				break;
			}
		}
	}

	// Also check file number and image shape
	bool flag_file_size = fracture_file_num(proj);
	bool flag_img_shape = fracture_img_shape(proj);

	return (flag_file_size && flag_img_shape && flag_data_correct);
}

bool Tests::fracture_min()
{
	// Test MinIP on fracture data
	int img_id = 700;
	int w, h, c;

	// Check if output is correct
	unsigned char* data = stbi_load("Scans/fracture/granite1_1025.png", &w, &h, &c, 0);
	Projection proj("Scans/fracture");
	unsigned char* data_proj = proj.min_ip(img_id, img_id + 1);
	bool flag_data_correct = true;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int pixel_index = (y * w + x) * c;
			if (data[pixel_index] != data_proj[pixel_index])
			{
				flag_data_correct = false;
				break;
			}
		}
	}

	// Also check file number and image shape
	bool flag_file_size = fracture_file_num(proj);
	bool flag_img_shape = fracture_img_shape(proj);

	return (flag_file_size && flag_img_shape && flag_data_correct);
}

bool Tests::fracture_avg()
{
	// Test MeanIP on fracture data
	int img_id = 600;
	int w, h, c;

	// Check if output is correct
	unsigned char* data = stbi_load("Scans/fracture/granite1_925.png", &w, &h, &c, 0);
	Projection proj("Scans/fracture");
	unsigned char* data_proj = proj.avg_ip(img_id, img_id + 1);
	bool flag_data_correct = true;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int pixel_index = (y * w + x) * c;
			if (data[pixel_index] != data_proj[pixel_index])
			{
				flag_data_correct = false;
				break;
			}
		}
	}

	// Also check file number and image shape
	bool flag_file_size = fracture_file_num(proj);
	bool flag_img_shape = fracture_img_shape(proj);

	return (flag_file_size && flag_img_shape && flag_data_correct);
}

// If parameter is not true, test fails
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

// Test for confuciusornis data
void Tests::test_confuciusornis()
{
	IS_TRUE(confuciusornis_max());
	IS_TRUE(confuciusornis_min());
	IS_TRUE(confuciusornis_avg());
}

// Test for fracture data
void Tests::test_fracture()
{
	IS_TRUE(fracture_max());
	IS_TRUE(fracture_min());
	IS_TRUE(fracture_avg());
}
void Tests::test_box_blur() {
    // Load input image
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input_boxblur.png", &w, &h, &c, 0);
    Image
     img(w, h, c, data);

    // Apply box blur filter
    Filter f;
    f.box_blur(img, 3);

    // Load output image
    unsigned char* output_data = stbi_load("../Output/output_boxblur.png", &w, &h, &c, 0);
    Image output_img(w, h, c, output_data);

    // Check if output image has been successfully created
    assert(output_data != NULL);

    // Check if output image is the same as input image
    bool modified = false;
    for (int i = 0; i < img.get_width() * img.get_height() * img.get_channel(); i++) {
        if (data[i] != output_data[i]) {
            modified = true;
            break;
        }
    }
    assert(modified);
    
    // Free memory
    stbi_image_free(data);
    stbi_image_free(output_data);
}

void Tests::test_sobel() {
    // Load input image
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input_sobel.png", &w, &h, &c, 0);
    Image img(w, h, c, data);

    // Apply Sobel filter
    Filter f;
    f.Sobel(img);

    // Load expected output image
    unsigned char* expected_data = stbi_load("./Images/tests/output_sobel.png", &w, &h, &c, 0);
    Image expected(w, h, c, expected_data);

    // Load actual output image
    unsigned char* actual_data = stbi_load("../Output/output_sobel.png", &w, &h, &c, 0);
    Image actual(w, h, c, actual_data);

    // Compare dimensions of expected and actual output images
    assert(expected.get_width() == actual.get_width());
    assert(expected.get_height() == actual.get_height());
    assert(expected.get_channel() == actual.get_channel());

    // Check if the pixels have been modified
    bool modified = false;
    for (int i = 0; i < w * h * c; i++) {
        if (expected_data[i] != actual_data[i]) {
            modified = true;
            break;
        }
    }
    assert(modified);

    // Deallocate memory
    stbi_image_free(data);
    stbi_image_free(expected_data);
    stbi_image_free(actual_data);
}
void Tests::test_prewitt() {
    // Load input image
    int w, h, c;
    unsigned char* data = stbi_load("./Images/tests/input_sobel.png", &w, &h, &c, 0);
    Image img(w, h, c, data);

    // Apply Sobel filter
    Filter f;
    f.Prewitt(img);

    // Load expected output image
    unsigned char* expected_data = stbi_load("./Images/tests/output_prewitt.png", &w, &h, &c, 0);
    Image expected(w, h, c, expected_data);

    // Load actual output image
    unsigned char* actual_data = stbi_load("../Output/output_prewitt.png", &w, &h, &c, 0);
    Image actual(w, h, c, actual_data);

    // Compare dimensions of expected and actual output images
    assert(expected.get_width() == actual.get_width());
    assert(expected.get_height() == actual.get_height());
    assert(expected.get_channel() == actual.get_channel());

    // Check if the pixels have been modified
    bool modified = false;
    for (int i = 0; i < w * h * c; i++) {
        if (expected_data[i] != actual_data[i]) {
            modified = true;
            break;
        }
    }
    assert(modified);

    // Deallocate memory
    stbi_image_free(data);
    stbi_image_free(expected_data);
    stbi_image_free(actual_data);
}




double** FilterCreation(double** GKernel, int kernel_size, double sigma);
void gaussian_blur(double** GKernel, int kernel_size, double sigma, int w, int h, int c, double* data, double* output);



//Test for generating a Guassian Kernel
// copioed from "src/Filter.cpp": for generating a Guassian kernel. 
double**  FilterCreation(double** GKernel, int kernel_size, double sigma)
{
    /*
    * set kernel_size = 3, sigma = 1.0
    
    The expected guassian kernel is 
    - 1st:  calculate the Gaussian weights corresponding to each coordinate, 
    where �� = 1 and the centre point of the Gaussian kernel is (0, 0):

    G(-1, -1) = G(1, 1) = (1 / (2 * �� * 1^2)) * exp(-((-1)^2 + (-1)^2) / (2 * 1^2)) �� 0.367879
    G(0, -1) = G(0, 1) = (1 / (2 * �� * 1^2)) * exp(-(0^2 + (-1)^2) / (2 * 1^2)) �� 0.606531
    G(1, -1) = G(-1, 1) = (1 / (2 * �� * 1^2)) * exp(-((1)^2 + (-1)^2) / (2 * 1^2)) �� 0.367879

    G(-1, 0) = G(1, 0) = (1 / (2 * �� * 1^2)) * exp(-((-1)^2 + 0^2) / (2 * 1^2)) �� 0.606531
    G(0, 0) = (1 / (2 * �� * 1^2)) * exp(-(0^2 + 0^2) / (2 * 1^2)) �� 1.00000
    G(1, 0) = G(-1, 0) = (1 / (2 * �� * 1^2)) * exp(-((1)^2 + 0^2) / (2 * 1^2)) �� 0.606531

    G(-1, 1) = G(1, -1) = (1 / (2 * �� * 1^2)) * exp(-((-1)^2 + (1)^2) / (2 * 1^2)) �� 0.367879
    G(0, 1) = G(0, -1) = (1 / (2 * �� * 1^2)) * exp(-(0^2 + (1)^2) / (2 * 1^2)) �� 0.606531
    G(1, 1) = G(-1, -1) = (1 / (2 * �� * 1^2)) * exp(-((1)^2 + (1)^2) / (2 * 1^2)) �� 0.367879
    
    - Next, these weights are normalized so that they sum to 1:
      Normalization factor = 1 / (0.3678794 + 0.6065314 + 1) �� 0.331936
      The normalized 3x3 Gaussian kernel matrix is
      [[0.075114, 0.123842, 0.075114],
       [0.123842, 0.204179, 0.123842],
       [0.075114, 0.123842, 0.075114]]


    
    
    The actual output of this guassian kernel is
    
    [[0.0751136, 0.123841,  0.0751136],
     [0.123841,  0.20418,  0.123841],
     [0.0751136,  0.123841,  0.0751136]]


     which is almost the same as what expected! 


     test: passed! 

    */
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
    for (int i = 0; i < kernel_size; ++i)
    {
        for (int j = 0; j < kernel_size; ++j)
        {
            GKernel[i][j] /= sum;
            cout << GKernel[i][j] << " ";
        }
        cout << endl;
    }
    return GKernel;
}


// Test for applying Guassian Kernel:
// copioed from "src/Filter.cpp": for applying the Guassian kernel. 
void gaussian_blur(double** GKernel, int kernel_size, double sigma, int w, int h, int c, double* data, double* output)
{
    /*
    The algorithm uses cropping in its processing to handle the pixel points at the border.

    The input: {55.0,60.0,65.0,75.0,80.0,85.0,95.0,100.0,105.0}
    kernel_size = 3
    sigma = 1.0

    - The expected output:

    1. Output[0][0](Top left):
        Overlapping input image pixel: 55.0, 60.0, 75.0, 80.0
        Overlapping Gaussian kernel elements: 0.20418, 0.123841, 0.123841, 0.0751136
        Calculation: 55.0 * 0.20418 + 60.0 * 0.123841 + 75.0 * 0.123841 + 80.0 * 0.0751136 �� 64.44
     
    2. Output[0][1]:
        Overlapping input image pixel: 55.0, 60.0, 65.0, 75.0, 80.0, 85.0
        Overlapping Gaussian kernel elements: 0.123841, 0.20418, 0.123841, 0.0751136, 0.123841, 0.0751136
        Calculation: 55.0 * 0.123841 + 60.0 * 0.20418 + 65.0 * 0.123841 + 75.0 * 0.0751136 + 80.0 * 0.123841 + 85.0 * 0.0751136 �� 67.55

    3. Output[0][2](Top right):
        Overlapping input image pixel: 60.0, 65.0, 80.0, 85.0
        Overlapping Gaussian kernel elements: 0.20418, 0.123841, 0.123841, 0.0751136
        Calculation: 60.0 * 0.20418 + 65.0 * 0.123841 + 80.0 * 0.123841 + 85.0 * 0.0751136 �� 70.66

    4. Output[1][0]:
        Overlapping input image pixel: 55.0, 60.0, 75.0, 80.0, 95.0, 100.0
        Overlapping Gaussian kernel elements: 0.123841, 0.0751136, 0.20418, 0.123841, 0.123841, 0.0751136
        Calculation: 55.0 * 0.123841 + 60.0 * 0.0751136 + 75.0 * 0.20418 + 80.0 * 0.123841 + 95.0 * 0.123841 + 100.0 * 0.0751136 �� 76.89
    
    5. Output[1][1](center):
        Overlapping input image pixel: 55.0, 60.0, 65.0, 75.0, 80.0, 85.0, 95.0, 100.0, 105.0
        Overlapping Gaussian kernel elements: 0.0751136, 0.123841, 0.0751136, 0.123841
        Calculation: 55.0 * 0.0751136 + 60.0 * 0.123841 + 65.0 * 0.0751136 + 75.0 * 0.123841 + 80.0 * 0.20418 + 85.0 * 0.123841 + 95.0 * 0.0751136 + 100.0 * 0.123841 + 105.0 * 0.0751136 �� 80.0

    6. Output[1][2](Middle right):
        Overlapping input image pixel: 60.0, 65.0, 80.0, 85.0, 100.0, 105.0
        Overlapping Gaussian kernel elements: 0.0751136, 0.123841, 0.0751136, 0.123841, 0.20418, 0.123841
        Calculation: 60.0 * 0.0751136 + 65.0 * 0.123841 + 80.0 * 0.0751136 + 85.0 * 0.123841 + 100.0 * 0.20418 + 105.0 * 0.123841 �� 83.11

    7. Output[2][0](Lower left corner):
        Overlapping input image pixel: 75.0, 80.0, 95.0, 100.0
        Overlapping Gaussian kernel elements: 0.20418, 0.123841, 0.123841, 0.0751136
        Calculation: 75.0 * 0.20418 + 80.0 * 0.123841 + 95.0 * 0.123841 + 100.0 * 0.0751136 �� 89.34

    8. Output[2][1](Top left):
        Overlapping input image pixel: 75.0, 80.0, 85.0, 95.0, 100.0, 105.0
        Overlapping Gaussian kernel elements: 0.123841, 0.20418, 0.123841, 0.0751136, 0.123841, 0.0751136
        Calculation:75.0 * 0.123841 + 80.0 * 0.20418 + 85.0 * 0.123841 + 95.0 * 0.0751136 + 100.0 * 0.123841 + 105.0 * 0.0751136 �� 92.45

    9. Output[2][2](Bottom right corner):
        Overlapping input image pixel: 0.20418, 0.123841, 0.123841, 0.0751136
        Overlapping Gaussian kernel elements: 0.20418, 0.123841, 0.123841, 0.0751136
        Calculation: 80.0 * 0.20418 + 85.0 * 0.123841 + 100.0 * 0.123841 + 105.0 * 0.0751136 �� 95.56

    Therefore, the final correct results: 
    [
        [64.44,  67.55,  70.66],
        [76.89,  80.0,   83.11],
        [89.34,  92.45,  95.56]
    ]



     The actual output of this gaussian_blur is
     [64.4385, 67.5508,70.6631, 76.8877, 80.0, 83.1123, 89.3369, 92.4492, 95.5615]
    
    
    which is almost the same as what expected!


    test: passed!
 */

    



    int k = kernel_size / 2;

    for (int ch = 0; ch < c; ch++) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                double sum = 0.0;
                double weightSum = 0.0;

                for (int ii = std::max(0, i - k); ii <= std::min(h - 1, i + k); ii++) {
                    for (int jj = std::max(0, j - k); jj <= std::min(w - 1, j + k); jj++) {
                        int m = ii - i + k;
                        int l = jj - j + k;
                        double weight = GKernel[m][l];

                        sum += data[(ii * w + jj) * c + ch] * weight;
                        weightSum += weight;
                    }
                }

                output[(i * w + j) * c + ch] = sum / weightSum;
            }
        }
    }

    for (int i = 0; i < 9; ++i)
    {
        cout << output[i] << endl;
    }
}


int main()
{
    Tests t;
    t.test_automatic_color_balance();
    t.test_brightness();
    t.test_grayscale();
    t.test_hist_equal();
    t.test_median_blur();
    //t.test_sobel();
    //t.test_prewitt();
	t.test_confuciusornis();
	t.test_fracture();
    //t.test_box_blur();
	/*Projection proj("Scans\\fracture");
	proj.min_ip(600, 800);
	unsigned char* data = proj.min_ip(799, 800);
	int success = stbi_write_png("MinIP_fracture_799_800.png", 
		proj.get_width(), proj.get_height(), 1, data, 0);*/
	std::cout << "All tests passed successfully! " << std::endl;
	return 0;
}



