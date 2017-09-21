#include "final.h"


/************************************************
 calcHistogram is the same impl for rgb and yuv
 ************************************************/
Mat globalHistogram(Mat src){
    vector<Mat> planes;
    split( src, planes );
    
    int histSize = YUVsinglechannel; /* 32 */
    
    
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    
    bool uniform = true;
    bool accumulate = false;
    
    Mat singleChannel, histogram;
    
    /// Compute the histograms:
    calcHist( &planes[0], 1, 0, Mat(), singleChannel, 1, &histSize, &histRange, uniform, accumulate );
    histogram.push_back(singleChannel);
    calcHist( &planes[1], 1, 0, Mat(), singleChannel, 1, &histSize, &histRange, uniform, accumulate );
    histogram.push_back(singleChannel);
    calcHist( &planes[2], 1, 0, Mat(), singleChannel, 1, &histSize, &histRange, uniform, accumulate );
    histogram.push_back(singleChannel);

    return histogram;
    
}



/************************************************
 calcHistogram is the same impl for rgb and yuv
 ************************************************/
Mat blockHistogram(Mat src){
    int blockhistSize = SingleBlockBins; /* 8 */
    
    
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    
    bool uniform = true;
    bool accumulate = false;
    
    Mat singleBlock, allBlocks;
    
    int hDivSize = src.rows/BlocksCount, wDivSize = src.cols/BlocksCount;
    int hh = (BlocksCount*hDivSize);
    int ww = (BlocksCount*wDivSize);
    
    vector<Mat> planes;
    
    for (int  k = 0 ; k < hh ; k+=hDivSize)//k rows
        for( int l = 0 ; l < ww ; l+=wDivSize )//l clos
        {
            
            Mat roi = src(Rect(l,k,wDivSize,hDivSize));
            
            split( roi, planes );
            
            calcHist( &planes[0], 1, 0, Mat(), singleBlock, 1, &blockhistSize, &histRange,  uniform, accumulate );
            allBlocks.push_back(singleBlock);
            calcHist( &planes[1], 1, 0, Mat(), singleBlock, 1, &blockhistSize, &histRange,  uniform, accumulate );
            allBlocks.push_back(singleBlock);
            calcHist( &planes[2], 1, 0, Mat(), singleBlock, 1, &blockhistSize, &histRange,  uniform, accumulate );
            allBlocks.push_back(singleBlock);
            
        }
    
    return allBlocks;
    
}
