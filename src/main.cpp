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

using namespace std;

int main() {

    int w, h, c;
    unsigned char *data;

    // Read in image file
    data = stbi_load("../Images/gracehopper.png", &w, &h, &c, 0);

    // Create Image Object
    Image img(w, h, c, data);
    for(int i = 0; i < w*h*c; ++i){cout << char2int(data[i]) <<" ";}


    cout << "hello" << endl;
    // Print image size to screen
    cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << endl;

    // Save image to new filename
    int success = stbi_write_png("../Output/output.png", w, h, c, data, 0);
    if (success) { cout << "Succeed!" << endl; }
    else { cout << "Error!" << endl; }

    // Deallocate memory
    stbi_image_free(data);

    return 0;
}