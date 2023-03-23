// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cmath>
#include "stb_image.h"
#include "stb_image_write.h"
#include "Volume.h"
#include "utils.h"
namespace fs = std::filesystem;

Volume::Volume() {}

// Constructor
Volume::Volume(std::string data_dir) {

    // read filenames from a user-defined folder
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(data_dir)) {
        if (entry.is_regular_file() && stbi_is_hdr(entry.path().u8string().c_str()) == 0) {
            files.push_back(entry.path().u8string());
        }
    }

    if (files.empty()) {
        std::cerr << "No image files found in directory " << data_dir << std::endl;
        return;
    }

    quickSort(files, 0, files.size()-1);

    // calculate the total size of the data
    int w, h, c;
    unsigned char* buf;

    if (stbi_load(files[0].c_str(), &w, &h, &c, 0) == NULL) {
        std::cerr << "Failed to load image " << files[0] << std::endl;
        return;
    }

    this->img_size = w * h * c;
    //std::cout << img_size << std::endl;
    this->total_size = this->img_size * files.size();
    //std::cout << total_size << std::endl;


    // allocate a new unique_ptr to hold the data
    unsigned char* data = new unsigned char[this->total_size];

    // concatenate the images
    unsigned long long offset = 0;

    for (const auto& file : files) {
        buf = stbi_load(file.c_str(), &w, &h, &c, 0);
        if (buf == NULL) {
            std::cerr << "Failed to load image " << file << std::endl;
            delete[] data;
            return;
        }
        std::memcpy(data + offset, buf, this->img_size);
        stbi_image_free(buf);
        buf = nullptr;

        offset += this->img_size;
        //std::cout << offset << " " << std::endl;

    }
    //std::cout << double(data[301372499]) << std::endl;

    // set the volume member
    this->width = w;
    this->height = h;
    this->channel = c;
    this->depth = files.size();
    this->data = data;
    this->outdir = files;

    //delete [] data;

}

// Destructor
Volume::~Volume() {}

int Volume::get_width() { return this->width; }

int Volume::get_height() { return this->height; }

int Volume::get_channel() { return this->channel; }

int Volume::get_depth() { return this->depth; }

unsigned char* Volume::get_data() { return this->data; }

std::vector<std::string> Volume::get_outdir() {return this->outdir;}

int Volume::get_img_size() {return this->img_size;}

int Volume::get_total_size() {return this->total_size;}

void Volume::set_width(int w) { this->width = w; }

void Volume::set_height(int h) { this->height = h; }

void Volume::set_depth(int d) { this->depth = d; }

void Volume::writeImages(std::vector<double> processedVolume, std::string outdir, const std::string &filterType) {

    int width = this->width;
    int height = this->height;

    // write image
    std::cout << "Start Writing..." << std::endl;
    for (int i=0; i<this->outdir.size(); ++i) {
        std::string entry = this->outdir[i];
        int pos =entry.rfind("/");
        std::string fn = entry.substr(pos+1, entry.length()-pos-1);

        std::string outputPath = outdir + "/" + filterType + "/" + "output_" + fn;
        std::vector<unsigned char> data(width * height);
        std::cout << outputPath << std::endl;

        // for each save dir, write the image
        for (int j = 0; j < width * height; ++j)
        {
            data[j] = static_cast<unsigned char>(processedVolume[j + (width * height * i)]);
        }
        stbi_write_png(outputPath.c_str(), width, height, 1, data.data(), width);
    }
    std::cout << "Finished!" << std::endl;

}

std::vector<double> Volume::apply3DGaussianFilter(Volume v, int filterSize, double sigma) {
    unsigned char* volume = v.get_data();
    int width = v.get_width();
    int height = v.get_height();
    int depth = v.get_depth();

    int halfFilterSize = filterSize / 2;
    std::vector<double> result(width*height*depth);

    double sum = 0.0;
    std::vector<double> kernel(filterSize * filterSize * filterSize);
    for (int z = -halfFilterSize; z <= halfFilterSize; ++z)
    {
        for (int y = -halfFilterSize; y <= halfFilterSize; ++y)
        {
            for (int x = -halfFilterSize; x <= halfFilterSize; ++x)
            {
                double value = std::exp(-(x * x + y * y + z * z) / (2.0f * sigma * sigma)) / (std::sqrt(2.0f * M_PI) * sigma);
                kernel[(z + halfFilterSize) * filterSize * filterSize + (y + halfFilterSize) * filterSize + (x + halfFilterSize)] = value;
                sum += value;
            }
        }
    }

    // Normalize the kernel
    for (double& value : kernel)
    {
        value /= sum;
    }

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                double sum = 0.0;
                for (int kz = -halfFilterSize; kz <= halfFilterSize; ++kz)
                {
                    for (int ky = -halfFilterSize; ky <= halfFilterSize; ++ky)
                    {
                        for (int kx = -halfFilterSize; kx <= halfFilterSize; ++kx)
                        {
                            int zz = std::min(std::max(z + kz, 0), depth - 1);
                            int yy = std::min(std::max(y + ky, 0), height - 1);
                            int xx = std::min(std::max(x + kx, 0), width - 1);

                            double value = volume[zz * width * height + yy * width + xx];
                            double weight = kernel[(kz + halfFilterSize) * filterSize * filterSize + (ky + halfFilterSize) * filterSize + (kx + halfFilterSize)];

                            sum += value * weight;
                        }
                    }
                }
                result[z * width * height + y * width + x] = sum;
            }
        }
    }

    return result;
}

std::vector<double> Volume::apply3DMedianFilter(Volume v, int filterSize) {
    unsigned char* volume = v.get_data();
    int width = v.get_width();
    int height = v.get_height();
    int depth = v.get_depth();

    int halfFilterSize = filterSize / 2;
    std::vector<double> result(width*height*depth);

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                std::vector<double> neighbors;
                for (int kz = -halfFilterSize; kz <= halfFilterSize; ++kz)
                {
                    for (int ky = -halfFilterSize; ky <= halfFilterSize; ++ky)
                    {
                        for (int kx = -halfFilterSize; kx <= halfFilterSize; ++kx)
                        {
                            int zz = std::min(std::max(z + kz, 0), depth - 1);
                            int yy = std::min(std::max(y + ky, 0), height - 1);
                            int xx = std::min(std::max(x + kx, 0), width - 1);

                            neighbors.push_back(volume[zz * width * height + yy * width + xx]);
                        }
                    }
                }
                std::nth_element(neighbors.begin(), neighbors.begin() + neighbors.size() / 2, neighbors.end());
                result[z * width * height + y * width + x] = neighbors[neighbors.size() / 2];
            }
        }
    }

    return result;
}

void Volume::Median3D(Volume v, std::string outdir, int filterSize) {
    std::cout << "Applying 3D Median filter..." << std::endl;
    std::vector<double> processedVolume = apply3DMedianFilter(v, filterSize);
    this->writeImages(processedVolume, outdir, "3D_Median");
}

void Volume::Gaussian3D(Volume v, std::string outdir, int filterSize, double sigma) {
    std::cout << "Applying 3D Gaussian filter..." << std::endl;
    std::vector<double> processedVolume = apply3DGaussianFilter(v, filterSize, sigma);
    this->writeImages(processedVolume, outdir, "3D_Gaussian");
}