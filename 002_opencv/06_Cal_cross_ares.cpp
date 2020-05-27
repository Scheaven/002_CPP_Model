bool ImageOverlap(cv::Mat &img1,cv::Mat &img2,std::vector<cv::Point> &vPtsImg1,std::vector<cv::Point> &vPtsImg2)
{
    cv::Mat g1(img1,Rect(0,0,img1.cols,img1.rows));
    cv::Mat g2(img2,Rect(0,0,img2.cols,img2.rows));

    cv::cvtColor(g1,g1,CV_BGR2GRAY);
    cv::cvtColor(g2,g2,CV_BGR2GRAY);

    std::vector<cv::KeyPoint> keypoints_roi, keypoints_img;  /* keypoints found using SIFT */
    cv::Mat descriptor_roi, descriptor_img;             /* Descriptors for SIFT */
    cv::FlannBasedMatcher matcher;                      /* FLANN based matcher to match keypoints */
    std::vector<cv::DMatch> matches, good_matches;
    cv::SIFT sift;
    int i, dist=80;

    sift(g1, Mat(), keypoints_roi, descriptor_roi);      /* get keypoints of ROI image */
    sift(g2, Mat(), keypoints_img, descriptor_img);         /* get keypoints of the image */
    matcher.match(descriptor_roi, descriptor_img, matches);

    double max_dist = 0; double min_dist = 1000;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptor_roi.rows; i++ )
    {
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    for (i=0; i < descriptor_roi.rows; i++)
    {
        if (matches[i].distance < 3*min_dist)
        {
            good_matches.push_back(matches[i]);
        }
    }

    //printf("%ld no. of matched keypoints in right image\n", good_matches.size());
    /* Draw matched keypoints */

    //Mat img_matches;
    //drawMatches(img1, keypoints_roi, img2, keypoints_img,
    //    good_matches, img_matches, Scalar::all(-1),
    //    Scalar::all(-1), vector<char>(),
    //    DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    //imshow("matches",img_matches);

    vector<Point2f> keypoints1, keypoints2;
    for (i=0; i<good_matches.size(); i++)
    {
        keypoints1.push_back(keypoints_img[good_matches[i].trainIdx].pt);
        keypoints2.push_back(keypoints_roi[good_matches[i].queryIdx].pt);
    }
    //计算单应矩阵
    Mat H = findHomography( keypoints1, keypoints2, CV_RANSAC );

    //show stitchImage
    // cv::Mat stitchedImage;
    // int mRows = img2.rows;
    // if (img1.rows> img2.rows)
    // {
        // mRows = img1.rows;
    // }
    // stitchedImage = Mat::zeros(img2.cols+img1.cols, mRows, CV_8UC3);
    // warpPerspective(img2,stitchedImage,H,Size(img2.cols+img1.cols,mRows));
    // Mat half(stitchedImage,Rect(0,0,img1.cols,img1.rows));
    // img1.copyTo(half);
    // imshow("stitchedImage",stitchedImage);

    std::vector<cv::Point> vSrcPtsImg1;
    std::vector<cv::Point> vSrcPtsImg2;

    vSrcPtsImg1.push_back(cv::Point(0,0));
    vSrcPtsImg1.push_back(cv::Point(0,img1.rows));
    vSrcPtsImg1.push_back(cv::Point(img1.cols,img1.rows));
    vSrcPtsImg1.push_back(cv::Point(img1.cols,0));

    vSrcPtsImg2.push_back(cv::Point(0,0));
    vSrcPtsImg2.push_back(cv::Point(0,img2.rows));
    vSrcPtsImg2.push_back(cv::Point(img2.cols,img2.rows));
    vSrcPtsImg2.push_back(cv::Point(img2.cols,0));

    //计算图像2在图像1中对应坐标信息
    std::vector<cv::Point> vWarpPtsImg2;
    for(int i = 0;i < vSrcPtsImg2.size();i++ )
    {
        cv::Mat srcMat = Mat::zeros(3,1,CV_64FC1);
        srcMat.at<double>(0,0) = vSrcPtsImg2[i].x;
        srcMat.at<double>(1,0) = vSrcPtsImg2[i].y;
        srcMat.at<double>(2,0) = 1.0;

        cv::Mat warpMat = H * srcMat;
        cv::Point warpPt;
        warpPt.x = cvRound(warpMat.at<double>(0,0)/warpMat.at<double>(2,0));
        warpPt.y = cvRound(warpMat.at<double>(1,0)/warpMat.at<double>(2,0));

        vWarpPtsImg2.push_back(warpPt);
    }
    //计算图像1和转换后的图像2的交点
    if(!PolygonClip(vSrcPtsImg1,vWarpPtsImg2,vPtsImg1))
        return false;

    for (int i = 0;i < vPtsImg1.size();i++)
    {
        cv::Mat srcMat = Mat::zeros(3,1,CV_64FC1);
        srcMat.at<double>(0,0) = vPtsImg1[i].x;
        srcMat.at<double>(1,0) = vPtsImg1[i].y;
        srcMat.at<double>(2,0) = 1.0;

        cv::Mat warpMat = H.inv() * srcMat;
        cv::Point warpPt;
        warpPt.x = cvRound(warpMat.at<double>(0,0)/warpMat.at<double>(2,0));
        warpPt.y = cvRound(warpMat.at<double>(1,0)/warpMat.at<double>(2,0));
        vPtsImg2.push_back(warpPt);
    }
    return true;
}