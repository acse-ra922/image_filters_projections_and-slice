//
// Created by Wang, Yuyang on 19/03/2023.
//

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H


class Image {
private:
    int width;
    int height;
    int channel;
    unsigned char* data;  // char data, 1D array
    double *out;

public:
    // constructor
    Image(int w, int h, int c, unsigned char* dat);

    // Destructor
    ~Image();

    // get function
    int get_width();
    int get_height();
    int get_channel();
    unsigned char* get_data();
    double * get_out();

    // set function
    void set_width(int w);
    void set_height(int h);
    void set_channel(int c);
    void set_data(unsigned char* dat);
    void set_out(double* dat);

    double* change2doubledata(unsigned char* dat);  // char to double, 1D array to 2D array
    unsigned char* change2data(double* d_data);  // double to char, 1D array to 1D array

    double* conv(double *pad_img_grid, double *kernel);

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H
