// Group-Dijkstra
// Xuefei Mi (xm421)
// Yuyang Wang (yw22)
// Chaofan Wu (cw522)
// Yi Yang (yy3222)
// Rubab Atwal (ra922)


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
    cout << "Welcome to Djikstra Group Project!!!" << endl;
    cout << "Please enter a path for the image: (e.g. ../Images/gracehopper.png)"<< endl;
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
    cout<<"You can perform the following filters."<<endl;

    string str = "";
    int listnum = -1;
    while(1){
        cout<<"To implement a filter, enter the list number:"<<endl;
        cout << "----------------------------" << endl;

        cout<< "1. Automatic Color Balance"<<endl;
        cout <<"2. Histogram Equalisation" <<endl;
        cout<< "3. Grayscale"<<endl;
        cout<<"4. Brightness"<<endl;
        cout <<"5. Median Blur" <<endl;
        cout<< "6. Box Blur"<<endl;
        cout<< "7. Gaussian Blur"<<endl;
        cout<<"8. Sobel"<<endl;
        cout<<"9. Prewitt"<< endl;
        cout <<"10. Scharr" <<endl;
        cout<<"11. Roberts" <<endl;
        cin>>listnum;
        switch (listnum){
            case 1:
                f.auto_color_bal(img);
                break;

            case 2:
                f.hist_equal(img);
                break;

            case 3:
                f.grayscale(img);
                break;

            case 4:
                int brightness;
                cout<<"Please enter an integer/float value for brightness: "<<endl;
                cin>>brightness;
                f.brightness(img, brightness);
                break;

            case 5:
                cout<< "Please specify kernel size: " <<endl;
                int k;
                cin>>k;
                f.median_blur(img,k);
                break;

            case 6:
                cout<<"Please specify kernel size: " <<endl;
                int ker;
                cin>>ker;
                f.box_blur(img, ker);
                break;

            case 7:
                cout<<"Please specify kernel size: " <<endl;
                int kern;
                cin>>kern;
                f.gaussian_blur(img, kern, 3.0);
                break;

            case 8:
                f.Sobel(img);
                break;

            case 9:
                f.Prewitt(img);
                break;

            case 10:
                f.Scharr(img);
                break;

            case 11:
                f.Roberts(img);
                break;

            default:
                cout << "Please enter a number (1~11)!" << endl;
        }

        // Ask for continue
        cout<<"Enter Y/y to continue or N/n to terminate the program"<<endl;
        cin>>str;
        if(str.compare("n")==0 && str.compare("N")){
            break;
        }
    }

    return 0;
}