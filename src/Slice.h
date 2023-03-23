#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_SLICE_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_SLICE_H
#include <string>
#include <memory>
#include "Volume.h"

class Slice : public Volume {
public:
    // constructor
    Slice();
    Slice(std::string slice_plane, int slice_pos, Volume &v);

    // Destructor
    ~Slice();

    //set function
    void set_slice_plane(std::string& slice_plane);
    void set_slice_pos(int slice_pos, Volume& v);

    // get function
    std::string get_slice_plane() const;
    int get_slice_pos() const;
    void get_slice_pic(Volume& v);


private:
    std::string slice_plane;
    int slice_pos;
    std::unique_ptr<unsigned char[]> slice_pic;

    // store the slice image
    void store_pic(Volume& v);
};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_SLICE_H