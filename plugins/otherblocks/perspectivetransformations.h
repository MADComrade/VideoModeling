#ifndef PERSPECTIVETRANSFORMATIONS_H
#define PERSPECTIVETRANSFORMATIONS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonprocessing.h"

class PerspectiveTransformations : public CommonProcessing
{
    Q_OBJECT
public:
    PerspectiveTransformations(QObject *parent = 0);
    ~PerspectiveTransformations();

    double getTopLeftX();
    double getTopLeftY();
    double getTopRightX();
    double getTopRightY();
    double getBottomLeftX();
    double getBottomLeftY();
    double getBottomRightX();
    double getBottomRightY();

    void setTopLeftX(double i);
    void setTopLeftY(double i);
    void setTopRightX(double i);
    void setTopRightY(double i);
    void setBottomLeftX(double i);
    void setBottomLeftY(double i);
    void setBottomRightX(double i);
    void setBottomRightY(double i);

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

private:
    cv::Point2f m_srcTri[4];
    cv::Point2f m_dstTri[4];
    cv::Point2f m_coeffTri[4];

    int m_flagIndex=0;
    QStringList m_flagList;
    QList<int> m_flagValues;

    int m_borderModeIndex=0;
    QStringList m_borderModeList;
    QList<int> m_borderModeValues;

    cv::Mat m_warpMat;

};

#endif // PERSPECTIVETRANSFORMATIONS_H
