#include "affinetransformations.h"
#include "blockenums.h"
#include "moduleconfig.h"

using namespace cv;
AffineTransformations::AffineTransformations(QObject *parent)
    : CommonProcessing(parent)
{
    m_warpMat = cv::Mat(2,3,CV_32FC1);

    m_coeffTri[0] = Point2f(0,0);
    m_coeffTri[1] = Point2f(1,0);
    m_coeffTri[2] = Point2f(0,1);

    m_flagList<<"LINEAR"<<"NEAREST";
    m_flagValues<<INTER_LINEAR<<INTER_NEAREST;

    m_borderModeList<<"CONSTANT"<<"REPLICATER";
    m_borderModeValues<<BORDER_CONSTANT<<BORDER_REPLICATE;

    setBlockProcessingName("AffineTr");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::AffineTr);
}

AffineTransformations::~AffineTransformations()
{
    QMutexLocker lock(&m_mutex);
}

double AffineTransformations::getTopLeftX()
{
    return m_coeffTri[0].x;
}

double AffineTransformations::getTopLeftY()
{
    return m_coeffTri[0].y;
}

double AffineTransformations::getTopRightX()
{
    return m_coeffTri[1].x;
}

double AffineTransformations::getTopRightY()
{
    return m_coeffTri[1].y;
}

double AffineTransformations::getBottomX()
{
    return m_coeffTri[2].x;
}

double AffineTransformations::getBottomY()
{
    return m_coeffTri[2].y;
}

void AffineTransformations::setTopLeftX(double i)
{
    m_coeffTri[0].x = i;
}

void AffineTransformations::setTopLeftY(double i)
{
    m_coeffTri[0].y = i;
}

void AffineTransformations::setTopRightX(double i)
{
    m_coeffTri[1].x = i;
}

void AffineTransformations::setTopRightY(double i)
{
    m_coeffTri[1].y = i;
}

void AffineTransformations::setBottomX(double i)
{
    m_coeffTri[2].x = i;
}

void AffineTransformations::setBottomY(double i)
{
    m_coeffTri[2].y = i;
}

void AffineTransformations::intputVideoStream(const Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    m_srcTri[0] = Point2f( 0,0 );
    m_srcTri[1] = Point2f( m_frame.cols - 1, 0 );
    m_srcTri[2] = Point2f( 0, m_frame.rows - 1 );

    m_dstTri[0] = Point2f( m_frame.cols*m_coeffTri[0].x, m_frame.rows*m_coeffTri[0].y );
    m_dstTri[1] = Point2f( m_frame.cols*m_coeffTri[1].x, m_frame.rows*m_coeffTri[1].y );
    m_dstTri[2] = Point2f( m_frame.cols*m_coeffTri[2].x, m_frame.rows*m_coeffTri[2].y );

    m_outFrame = Mat::zeros( m_frame.rows, m_frame.cols, m_frame.type());
    m_warpMat = getAffineTransform( m_srcTri, m_dstTri );
    warpAffine( m_frame, m_outFrame, m_warpMat, m_outFrame.size(),
                m_flagValues[m_flagIndex],m_borderModeValues[m_borderModeIndex],
                Scalar());

    emit outputVideoStream(m_outFrame);
}

int AffineTransformations::getBorderModeIndex() const
{
    return m_borderModeIndex;
}

void AffineTransformations::setBorderModeIndex(int borderModeIndex)
{
    m_borderModeIndex = borderModeIndex;
}

void AffineTransformations::setModuleParameter(const QJsonObject &param)
{
    m_coeffTri[0].x = param["x0"].toDouble();
    m_coeffTri[0].y = param["y0"].toDouble();
    m_coeffTri[1].x = param["x1"].toDouble();
    m_coeffTri[1].y = param["y1"].toDouble();;
    m_coeffTri[2].x = param["x2"].toDouble();
    m_coeffTri[2].y = param["y2"].toDouble();;
    m_flagIndex = param["flagIndex"].toInt();
    m_borderModeIndex = param["borderModeIndex"].toInt();
}

void AffineTransformations::getModuleParameter(QJsonObject &param)
{
    param["x0"] = m_coeffTri[0].x;
    param["y0"] = m_coeffTri[0].y;
    param["x1"] =m_coeffTri[1].x;
    param["y1"] =m_coeffTri[1].y;
    param["x2"] =m_coeffTri[2].x;
    param["y2"] =m_coeffTri[2].y;
    param["flagIndex"] = m_flagIndex;
    param["borderModeIndex"] = m_borderModeIndex;
}

int AffineTransformations::getFlagIndex() const
{
    return m_flagIndex;
}

void AffineTransformations::setFlagIndex(int flagIndex)
{
    m_flagIndex = flagIndex;
}

QStringList AffineTransformations::getBorderModeList() const
{
    return m_borderModeList;
}

QStringList AffineTransformations::getFlagList() const
{
    return m_flagList;
}
