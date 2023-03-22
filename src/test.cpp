// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.h"
#include "utils.h"
#include "Filter.h"

using namespace std;

int main() {

    int w, h, c;
    unsigned char *data;

    // Read in image file
    cout << "Welcome to Djikstra Group Project: " << endl;
    cout << "Please enter a path for the image"<< endl;
    string path;
    getline(cin, path);
    if(path.length()==0)
    {
        data = stbi_load("../Images/gracehopper.png",&w,&h,&c,0);
    }
    else{
        data = stbi_load(path.c_str(), &w, &h, &c, 0);
    }

    // Create Image object
    Image img(w, h, c, data);
    Filter f;

    cout<< "Color Correction"<<endl;
    cout<< "The following functions are being performed on the image right now"<<endl;
    cout<< "1. Automatic Color Balance"<<endl;
    f.auto_color_bal(img);
    cout <<"2. Histogram Equalisation" <<endl;
    f.hist_equal(img);
    cout<< "3. Grayscale"<<endl;
    f.grayscale(img);
    cout<<"4. Brightness"<<endl;
    int brightness;
    cout<<"Please enter an integer/float value for brightness"<<endl;
    cin>>brightness;
    f.brightness(img, brightness);
    cout << endl;


    // Blur
    cout << "Blur " << endl;
    cout << "1. Median Blur" <<endl;
    cout<< "Please specify kernel size" <<endl;
    int k;
    cin>>k;
    f.median_blur(img,k);
    cout<< "2. Box Blur"<<endl;
    cout<<"Please specify kernel size" <<endl;
    int ker;
    cin>>ker;
    f.box_blur(img, ker);
    cout<<"3. Gaussian Blur"<<endl;
    cout<<"Please specify kernel size" <<endl;
    int kern;
    cin>>kern;
    f.gaussian_blur(img, kern, 3.0);


    //Image img2 = f.Sobel(img);
//    double* out = img.change2doubledata(data);
//    for(int i = 0; i < h; ++i){
//        for(int j=0; j<w; ++j){
//            cout << (out+i)[j] <<" ";
//        }
//        cout << endl;
//    }

    //cout << "hello" << endl;
    // Print image size to screen
    //cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << endl;

    // Save image to new filename and print log
//    int success = stbi_write_png("../Output/output.png", w, h, c, img.get_data(), 0);
//    if (success) { cout << "Succeed!" << endl; }
//    else { cout << "Error!" << endl; }

    // Deallocate memory
    stbi_image_free(data);

    // Read Pre-processed image
    data = stbi_load("../Images/output_gray.png", &w, &h, &c, 0);
    Image img2(w, h, c, data);

    // Edge detection
    cout << "Edge Detection:" << endl;
    cout<<"1. Sobel"<<endl;
    f.Sobel(img2);
    cout<<"2. Prewitt"<< endl;
    f.Prewitt(img2);
    cout <<"3. Scharr" <<endl;
    f.Scharr(img2);
    cout<<"4. Roberts" <<endl;
    f.Roberts(img2);
    cout << endl;

    return 0;
}