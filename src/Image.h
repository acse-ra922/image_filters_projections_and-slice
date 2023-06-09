// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H


class Image {
private:
    int width;
    int height;
    int channel;
    unsigned char* data;  // char data, 1D array

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

    unsigned char* padding(unsigned char* dat);  // padding 0, 1D array

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_IMAGE_H
