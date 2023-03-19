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
    unsigned char* data;

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

    // set function
    void set_width(int w);
    void set_height(int h);
    void set_channel(int c);
    void set_data(unsigned char* dat);
};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H
