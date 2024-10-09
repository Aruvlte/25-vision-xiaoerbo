// OpenCVtest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "stdio.h"
#include<iostream> 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;



Point2f getCenter(const Rect& rect){
    return Point2f(rect.x+rect.width/2.0,rect.y+rect.height/2.0);
}


bool Parallel(const Rect& rect1,const Rect&rect2,float angleThreshold){
    float angle1=atan2(rect1.height,rect1.width);
    float angle2=atan2(rect2.height,rect2.width);
    return abs(angle1-angle2)<angleThreshold;

}
//灯条平行


bool Similar(const Rect& rect1,const Rect&rect2,float heighThreshold){
    float heightDiff =abs(rect1.height-rect2.height);
    return heightDiff<heighThreshold;
}

//灯条高度相似


bool CenterClose(const Rect& rect1,const Rect&rect2,float distanceThreshold){
    Point2f center1=getCenter(rect1);
    Point2f center2=getCenter(rect2);
    return norm(center1-center2)<distanceThreshold;
}

//灯条中心距离不会太远



const Size kGaussianSize = Size(5, 5);
int main()
{
    string path ="/home/aruvle/Downloads/zimiao_test.mp4";
    VideoCapture video(path);

    //导入视频


    Mat frame,frame_hsv,channels[3],binary,GaussianBlue,GaussianRed;
    vector<vector<Point>> contoursRed,contoursBlue;
    vector<Vec4i> hierarchyBlue,hierarchyRed;
    Rect boundRectRed,boundRectBlue;
    RotatedRect box;
    vector<Point2f> boxPts(4);
    //定义变量

    // Scalar lowerOrange =Scalar(5,150,150);
    // Scalar upperOrange =Scalar(15,255,255);
    //橙色HSV

    // Scalar lowerBlue =Scalar(100,150,0);
    // Scalar upperBlue =Scalar(140,255,255);
    //蓝色HSV
    Mat maskRed,maskBlue;



    while (true)  {
        Rect point_arrayBlue[20],point_arrayRed[20];
        video >> frame;  //逐帧处理
        if (frame.empty()) {
            break;
        }      //判断读取是否出错
        split(frame,channels);
        //threshold(channels[0],maskBlue,220,250,0);
        threshold(channels[2],maskRed,220,250,0);


        GaussianBlur(maskRed, GaussianRed, kGaussianSize, 0);
        //GaussianBlur(maskBlue, GaussianBlue, kGaussianSize, 0);
        
        //高斯模糊
        
        findContours(GaussianRed, contoursRed, hierarchyRed, RETR_TREE, CHAIN_APPROX_NONE);
        //findContours(GaussianBlue, contoursBlue, hierarchyBlue, RETR_TREE, CHAIN_APPROX_NONE);
        
        
        //二值化以及寻找轮廓
        //hierarchyRed里面保存的是轮廓的层级关系/嵌套关系


        if(contoursRed.size()<2){
            cout<<"not enough rectangles to compare"<<endl;
            continue;
        }
        
        //防止存储区域段错误，区域段错误的原因一般是数组访问越界

        int index = 0;
        for (int i = 0; i < contoursRed.size(); i++) {
            boundRectRed = boundingRect(Mat(contoursRed[i]));//外接最小矩形
            if(double ((boundRectRed.height/boundRectRed.width)>=1.3&&boundRectRed.height>36&&boundRectRed.width>20)){
            point_arrayRed[index]=boundRectRed;
            index++;}
            
        }   

        //初步筛选灯条，减小误差，防止boundRect访问越界

        // index=0;
        // for (int i = 0; i < contoursBlue.size(); i++) {
        //     boundRectBlue = boundingRect(Mat(contoursBlue[i]));
        //     point_arrayBlue[index]=boundRectBlue;
        //     index++;
        // }    
        // if(index<2){
        //     cout<<"not enough rectangles to compare"<<endl;
        //     continue;
        // }




        int point_near[2];
        float bestscore=numeric_limits<float>::max();
        for (int i = 0; i < index-1; i++)
        {
            for (int j = i + 1; j < index; j++) {
                if (Parallel(point_arrayRed[i],point_arrayRed[j],CV_PI/10)
                    //&&Similar(point_arrayRed[i],point_arrayRed[j],10)
                    //CenterClose(point_arrayRed[i],point_arrayRed[j],30)
                    )
                {   float score =abs(point_arrayRed[i].area()-point_arrayRed[j].area());
                    if(score <bestscore){ 
                    bestscore=score;
                    point_near[0] = i;
                    point_near[1] = j;
                    }
                }
            }
        }   

        //利用平行，高度差，距离筛选灯条
        //选出大小最相似的灯条作为输出



        // for (int i = 0; i < contoursBlue.size(); i++)
        // {
        //     for (int j = i + 1; j < contoursBlue.size()+1; j++) {
        //         int value = abs(point_arrayBlue[i].area() - point_arrayRed[j].area());
        //         if (value < min)
        //         {
        //             min = value;
        //             point_near[0] = i;
        //             point_near[1] = j;
        //         }
        //     }
        // }   


        try
        {
            Rect rectangle_1 = point_arrayRed[point_near[0]];
            Rect rectangle_2 = point_arrayRed[point_near[1]];


            Point point1 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y);
            Point point2 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y + rectangle_1.height);
            Point point3 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y);
            Point point4 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y + rectangle_2.height);
            Point p[4] = { point1,point2,point4,point3 };
            cout << p[0]<<p[1]<<p[2]<<p[3] << endl;
            for (int i = 0; i < 4; i++) {
                line(frame, p[i%4], p[(i+1)%4], Scalar(0, 255, 0), 2);
            }           //画框
        }
        catch (const char* msg)
        {
            cout << msg << endl;
            //continue;
        }
        // try
        // {
        //     Rect rectangle_1 = point_arrayBlue[point_near[0]];
        //     Rect rectangle_2 = point_arrayBlue[point_near[1]];
        //     if (rectangle_2.x == 0 || rectangle_1.x == 0) {
        //         throw "not enough points";
        //     }
        //     Point point1 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y);
        //     Point point2 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y + rectangle_1.height);
        //     Point point3 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y);
        //     Point point4 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y + rectangle_2.height);
        //     Point p[4] = { point1,point2,point4,point3 };
        //     cout << p[0]<<p[1]<<p[2]<<p[3] << endl;
        //     for (int i = 0; i < 4; i++) {
        //         line(frame, p[i%4], p[(i+1)%4], Scalar(0, 255, 0), 2);
        //     }           
        // }
        // catch (const char* msg)
        // {
        //     cout << msg << endl;
        //     //continue;
        // }
        imshow("video", frame);
        if (waitKey(10) >= 0) {
            break;
        }
    }
    // video.release();
    // cv::destroyAllWindows();
     return 0;
}