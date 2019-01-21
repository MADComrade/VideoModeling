#include "additionmethods.h"
using namespace cv;
/// <summary>
/// Gets the Gaussian filter.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="sigma">The sigma.</param>
/// <param name="invert">if set to <c>true</c> [invert].</param>
/// <returns></returns>
Mat getGaussianFilter(Size size, double sigma, bool invert) {
    Mat filter = Mat::zeros(size, CV_32F);
     Point2i center(size.width / 2, size.height / 2);

     for (int i = 0; i < filter.rows; i++)
     {
      for (int j = 0; j < filter.cols; j++)
      {
       Point p(j - center.x, i - center.y);
       double e = exp(-norm(p)*norm(p) / (2*sigma*sigma));
       filter.at<float>(i, j) = static_cast<float>(invert ? 1 - e : e);
      }
     }
     shiftImageToCenter(filter);
     return filter;
}

/// <summary>
/// Applies the Gaussian filter.
/// </summary>
/// <param name="src">The source.</param>
/// <param name="sigma">The sigma.</param>
/// <returns></returns>
Mat applyGaussianFilter(Mat src, double sigma)
{
    // create Gaussian kernels
    Mat kernelX = getGaussianKernel(src.size().width, sigma, CV_32F);
    Mat kernelY = getGaussianKernel(src.size().height, sigma, CV_32F);

    Mat dst;
    sepFilter2D(src, dst, -1, kernelX, kernelY);

    return dst;
}

/// <summary>
/// Computes the DFT.
/// </summary>
/// <param name="image">The image.</param>
/// <returns></returns>
Mat computeDFT(Mat image) {
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize(image.rows);
    int n = getOptimalDFTSize(image.cols); // on the border add zero values

    copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complex;
    merge(planes, 2, complex);					 // Add to the expanded another plane with zeros
    dft(complex, complex, DFT_COMPLEX_OUTPUT);  // Fourier transform
    return complex;
}

/// <summary>
/// Computes the inverse Furrier discrete transform.
/// </summary>
/// <param name="image">The image.</param>
/// <returns></returns>
Mat computeIDFT(Mat image) {
    Mat dst;
    idft(image, dst, DFT_REAL_OUTPUT | DFT_SCALE);
    dst.convertTo(dst, CV_8UC1);
    return dst;
}

/// <summary>
/// Gets the ideal filter.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="width">The width.</param>
/// <returns></returns>
Mat getIdealFilter(cv::Size size, double width)
{
    // check if kernel size is valid
    int minsize = std::min(size.width, size.height);

    if (minsize < width) { width = minsize; }

    //check if size is odd

    //iterate array
    Mat filter = Mat::zeros(size, CV_32FC2);
    Point2i center(size.width / 2, size.height / 2);

    for (int i = 0; i < filter.rows; i++)
    {
        for (int j = 0; j < filter.cols; j++)
        {
            Point p(j - center.x, i - center.y);
            if (norm(p) <= width) {
                filter.at<Vec2f>(i, j) = Vec2f(1.0f, 1.0f);
            }
        }
    }
    shiftImageToCenter(filter);
    return filter;
}

/// <summary>
/// Gets the inverse ideal filter.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="width">The width.</param>
/// <returns></returns>
Mat getInverseIdealFilter(cv::Size size, double width)
{
    Mat m = getIdealFilter(size, width);
    Mat ones = Mat(size, CV_32FC2, cv::Scalar(1.0f, 1.0f));
    return ones - m;
}

/// <summary>
/// Gets the butterworth filter.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="width">The width.</param>
/// <param name="order">The order.</param>
/// <returns></returns>
Mat getButterworthFilter(cv::Size size, double width, int order)
{
    // check if kernel size is valid
    int minsize = std::min(size.width, size.height);
    if (minsize < width) { width = minsize; }

    //check if size is odd

    Mat filter = Mat::zeros(size, CV_32FC2);
    Point2i center(size.width / 2, size.height / 2);

    for (int i = 0; i < filter.rows; i++)
    {
        for (int j = 0; j < filter.cols; j++)
        {
            Point p(j - center.x, i - center.y);
            float f = static_cast<float>(1 / (1 + pow(norm(p) / width, 2 * order)));
            filter.at<Vec2f>(i, j) = Vec2f(f, f);
        }
    }

    shiftImageToCenter(filter);
    return filter;
}

/// <summary>
/// Gets the inverse Butterworth filter.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="width">The width.</param>
/// <param name="order">The order.</param>
/// <returns></returns>
Mat getInverseButterworthFilter(cv::Size size, double width, int order)
{
    Mat m = getButterworthFilter(size, width, order);
    Mat ones = Mat(size, CV_32FC2, cv::Scalar(1.0f, 1.0f));
    return ones - m;
}

/// <summary>
/// Gets the Laplacian filter.
/// </summary>
/// <param name="size">The size.</param>
/// <returns></returns>
Mat getLaplacianFilter(Size size)
{
    const double PI = 3.14159265358979323846;

    Mat filter = Mat::zeros(size, CV_32FC2);
    Point2i center(size.width / 2, size.height / 2);

    for (int i = 0; i < filter.rows; i++)
    {
        for (int j = 0; j < filter.cols; j++)
        {
            Point p(j - center.x, i - center.y);
            float f = static_cast<float>(-4.0 * PI * PI * norm(p)*norm(p));
            filter.at<Vec2f>(i, j) = Vec2f(f, f);
        }
    }

    shiftImageToCenter(filter);
    return filter;
}

/// <summary>
/// Shifts the image to center.
/// </summary>
/// <param name="img">The image.</param>
void shiftImageToCenter(Mat img) {
    // crop if it has an odd number of rows or columns
    img = img(Rect(0, 0, img.cols & -2, img.rows & -2));

    int cx = img.cols / 2;
    int cy = img.rows / 2;

    Mat q0(img, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(img, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(img, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(img, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
}
