#ifndef AFFINETRANSFORMATIONS_H
#define AFFINETRANSFORMATIONS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonprocessing.h"


class AffineTransformations : public CommonProcessing
{
    Q_OBJECT
public:
    AffineTransformations(QObject *parent = 0);
    ~AffineTransformations();

    double getTopLeftX();
    double getTopLeftY();
    double getTopRightX();
    double getTopRightY();
    double getBottomX();
    double getBottomY();

    void setTopLeftX(double i);
    void setTopLeftY(double i);
    void setTopRightX(double i);
    void setTopRightY(double i);
    void setBottomX(double i);
    void setBottomY(double i);

    QStringList getFlagList() const;

    QStringList getBorderModeList() const;

    int getFlagIndex() const;
    void setFlagIndex(int flagIndex);

    int getBorderModeIndex() const;
    void setBorderModeIndex(int borderModeIndex);

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
public slots:
    void intputVideoStream(const cv::Mat& frame);

protected:
    cv::Point2f m_srcTri[3];
    cv::Point2f m_dstTri[3];
    cv::Point2f m_coeffTri[3];

    int m_flagIndex=0;
    QStringList m_flagList;
    QList<int> m_flagValues;

    int m_borderModeIndex=0;
    QStringList m_borderModeList;
    QList<int> m_borderModeValues;

    cv::Mat m_warpMat;
};

#endif // AFFINETRANSFORMATIONS_H
