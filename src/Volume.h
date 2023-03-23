// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


#ifndef ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_VOLUME_H
#define ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_VOLUME_H
#include <string>
#include <vector>


class Volume {
protected:
//private:
    int width;
    int height;
    int depth;
    int channel;
    int img_size;
    int total_size;
    std::vector<std::string> outdir;

    unsigned char* data;

public:
    // empty constructor
    Volume();

    // constructor
    Volume(std::string data_dir);

    // Destructor
    ~Volume();

    // get function
    int get_width();
    int get_height();
    int get_channel();
    int get_depth();
    int get_img_size();
    int get_total_size();
    std::vector<std::string> get_outdir();
    unsigned char* get_data();

    // set function
    void set_width(int w);
    void set_height(int h);
    void set_depth(int d);

    //void store_pic();
    void writeImages(std::vector<double> processedVolume, std::string outdir, const std::string &filterType);
    std::vector<double> apply3DMedianFilter(Volume v, int filterSize);
    std::vector<double> apply3DGaussianFilter(Volume v, int filterSize, double sigma);
    void Median3D(Volume v, std::string outdir, int filterSize);
    void Gaussian3D(Volume v, std::string outdir, int filterSize, double sigma);

    //void quickSort(std::vector<std::string>& arr, int left, int right);

};


#endif //ADVANCED_PROGRAMMING_GROUP_DIJKSTRA_VOLUME_H