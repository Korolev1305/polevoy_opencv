//
//  main.cpp
//  testopencv
//
//  Created by Королев Максим Алексеевич on 21/02/2019.
//  Copyright © 2019 Королев Максим Алексеевич. All rights reserved.
//

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("img.jpg");
    
    int intensivityArray[256]= {0};

    for(int j=0;j<img.rows;j++)
    {
        for (int i=0;i<img.cols;i++)
        {
            int number = (int) img.at<uchar>(j,i);
            ++intensivityArray[number];
        }
    }

    int rows = 2500;
   
    int binSize = 15;
    
    int cols = 256* binSize;
    
    Mat3b dst = Mat3b(rows, cols, Vec3b(0,0,0));
    
    for (int i = 0; i < 256; ++i)
    {
        int h = rows - (int) intensivityArray[i]/10;
        
        rectangle(dst, Point(i*binSize, h), Point((i + 1)*binSize-1, rows), (i%2) ? Scalar(0, 100, 255) : Scalar(0, 0, 255),FILLED);
    }
    
    imshow("Histogram", dst);
    waitKey();
    return 0;

}
