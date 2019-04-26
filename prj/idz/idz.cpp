

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    int windowSize = 2;
    int imageNumber = -1;
    int sigma = -1;
    while(imageNumber > 2 or imageNumber < 0)
    {
    cout << "Введите номер изображения (1 – домик или 2 – овощи):" << endl;
    cin >> imageNumber;
    if (imageNumber > 2 or imageNumber < 0)
    {
        cout << "Введено неверное число" << endl;
    }
    }
    
    while(windowSize % 2 == 0)
    {
        cout << "Введите размер стороны (нечетное число):" << endl;
        cin >> windowSize;
        if (windowSize % 2 == 0)
        {
            cout << "Введено неверное число" << endl;
        }
    }
    
    while(sigma < 0 or sigma > 255)
    {
        cout << "Введите число Sigma (от 0 до 255):" << endl;
        cin >> sigma;
        if (sigma < 0 or sigma > 255)
        {
            cout << "Введено неверное число" << endl;
        }
    }
    
    Mat image1;
    if(imageNumber == 1){
        image1 = imread("Using-an-edge-indicator-based-weights-our-adaptive-TV-regularization-obtains-better-noise_Q320.jpg");
    }
    if(imageNumber == 2){
        image1 = imread("217021.fig.005a.jpg");
    }
    
    
    imshow("first image", image1);
    vector<Mat> rgb_image;
    split(image1, rgb_image);
    int midPixel;
    int anyPixel;
    int sum;
    int no;
    
    for(int y=0;y<image1.rows;y++)
    {
        for(int x=0;x<image1.cols*3;x++)
        {
            midPixel=(int)image1.at<uchar>(y,x);
            sum = 0;
            no = 0;
            for (int yy=-windowSize/2;yy<=windowSize/2;yy++)
            {
                int yyy=y+yy;
                //if(yyy<0 or yyy>=image1.cols) continue;
                for(int xx=-windowSize/2;xx<=windowSize/2;xx++)
                {
                    int xxx=xx+x;
                    //if(xxx<0 or xxx>=image1.rows) continue;
                    anyPixel = (int) image1.at<uchar>(yyy,xxx);
                    if(abs(midPixel-anyPixel)<sigma)
                    {
                        sum+=anyPixel;
                        no++;
                    }
                }
            }
            if(no>0) {
                int ti = sum/no;
                image1.at<uchar>(y,x) = ti;
            } else {
                image1.at<uchar>(y,x) = midPixel;
            }
        }
    }
    
    imshow("result", image1);
    waitKey();
    destroyAllWindows();
    return 0;
}
