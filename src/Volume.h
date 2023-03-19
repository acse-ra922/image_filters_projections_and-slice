//
// Created by Wang, Yuyang on 19/03/2023.
//

#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_VOLUME_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_VOLUME_H


class Volume {
private:
    int width;
    int height;
    int depth;

public:
    // constructor
    Volume(int w, int h, int d);

    // Destructor
    ~Volume();

    // get function
    int get_width();
    int get_height();
    int get_depth();

    // set function
    void set_width(int w);
    void set_height(int h);
    void set_depth(int d);

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_VOLUME_H
