// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


#include<iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "Projection.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Read in 3D data
    cout << "Welcome to Djikstra Group Project!!!" << endl;
    cout << "Please enter directory for the 3D data: (e.g. ../Scans/fracture)" << endl;
    string data_dir;
    getline(cin, data_dir);
    if (data_dir.length() == 0)
    {
        data_dir = "Scans/fracture";
    }
    Projection proj(data_dir);

    // Specify thin slab
    int zmin = NULL;
    int zmax = NULL;
    cout << "You can specify the thin slab to perform projections." << endl;
    cout << "Enter 1 to specify the thin slab, enter 0 to continue; " << endl;
    int specify_z = -1;
    while ((specify_z != 0) && (specify_z != 1))
    {
        cin >> specify_z;
        switch (specify_z)
        {
        case 1:
            cout << "Please enter z min" << endl;
            cin >> zmin;
            cout << "Please enter z max" << endl;
            cin >> zmax;
            break;
        case 0:
            break;
        default:
            cout << "Please enter a either 1 or 0!" << endl;
        }
        break;
    }

    // Select projection
    cout << "You can perform the following projections." << endl;
    cout << "To perform a projection, enter the list number:" << endl;
    cout << "----------------------------" << endl;

    cout << "1. Maximum intensity projection" << endl;
    cout << "2. Minimum intensity projection" << endl;
    cout << "3. Average intensity projection" << endl;

    unsigned char* data_out;
    string str = "";
    int proj_choice = -1;
    while ((proj_choice != 1) && (proj_choice != 2) && (proj_choice != 3))
    {
        cin >> proj_choice;
        switch (proj_choice)
        {
        case 1:
            data_out = proj.max_ip(zmin, zmax);
            break;

        case 2:
            data_out = proj.min_ip(zmin, zmax);
            break;

        case 3:
            data_out = proj.avg_ip(zmin, zmax);
            break;
        default:
            cout << "Please enter a number (1~3)!" << endl;
        }
    }

    int success = stbi_write_png("../Output/projection/output_projection.png",
        proj.get_width(), proj.get_height(), 1, data_out, 0);
}