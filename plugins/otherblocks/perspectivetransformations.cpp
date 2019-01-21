#include "perspectivetransformations.h"
#include "blockenums.h"
#include "moduleconfig.h"
using namespace cv;

PerspectiveTransformations::PerspectiveTransformations(QObject *parent)
    : CommonProcessing(parent)
{
    m_warpMat = cv::Mat(3,3,CV_32FC1);

    m_coeffTri[0] = Point2f(0,0);
    m_coeffTri[1] = Point2f(1,0);
    m_coeffTri[2] = Point2f(0,1);
    m_coeffTri[3] = Point2f(1,1);

    m_flagList<<"LINEAR"<<"NEAREST";
    m_flagValues<<INTER_LINEAR<<INTER_NEAREST;

    m_borderModeList<<"CONSTANT"<<"REPLICATER";
    m_borderModeValues<<BORDER_CONSTANT<<BORDER_REPLICATE;

    setBlockProcessingName("PerspectiveTr");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::PerspectiveTr);
}

PerspectiveTransformations::~PerspectiveTransformations()
{
    QMutexLocker lock(&m_mutex);
}

double PerspectiveTransformations::getTopLeftX()
{
    return m_coeffTri[0].x;
}

double PerspectiveTransformations::getTopLeftY()
{
    return m_coeffTri[0].y;
}

double PerspectiveTransformations::getTopRightX()
{
    return m_coeffTri[1].x;
}

double PerspectiveTransformations::getTopRightY()
{
    return m_coeffTri[1].y;
}

double PerspectiveTransformations::getBottomLeftX()
{
    return m_coeffTri[2].x;
}

double PerspectiveTransformations::getBottomLeftY()
{
    return m_coeffTri[2].y;
}

double PerspectiveTransformations::getBottomRightX()
{
    return m_coeffTri[3].x;
}

double PerspectiveTransformations::getBottomRightY()
{
    return m_coeffTri[3].y;
}

void PerspectiveTransformations::setTopLeftX(double i)
{
    m_coeffTri[0].x = i;
}

void PerspectiveTransformations::setTopLeftY(double i)
{
    m_coeffTri[0].y = i;
}

void PerspectiveTransformations::setTopRightX(double i)
{
    m_coeffTri[1].x = i;
}

void PerspectiveTransformations::setTopRightY(double i)
{
    m_coeffTri[1].y = i;
}

void PerspectiveTransformations::setBottomLeftX(double i)
{
    m_coeffTri[2].x = i;
}

void PerspectiveTransformations::setBottomLeftY(double i)
{
    m_coeffTri[2].y = i;
}

void PerspectiveTransformations::setBottomRightX(double i)
{
    m_coeffTri[3].x = i;
}

void PerspectiveTransformations::setBottomRightY(double i)
{
    m_coeffTri[3].y = i;
}

QStringList PerspectiveTransformations::getFlagList() const
{
    return m_flagList;
}

QStringList PerspectiveTransformations::getBorderModeList() const
{
    return m_borderModeList;
}

int PerspectiveTransformations::getFlagIndex() const
{
    return m_flagIndex;
}

void PerspectiveTransformations::setFlagIndex(int flagIndex)
{
    m_flagIndex = flagIndex;
}

int PerspectiveTransformations::getBorderModeIndex() const
{
    return  m_borderModeIndex;
}

void PerspectiveTransformations::setBorderModeIndex(int borderModeIndex)
{
    m_borderModeIndex = borderModeIndex;
}

void PerspectiveTransformations::setModuleParameter(const QJsonObject &param)
{
    m_coeffTri[0].x = param["x0"].toDouble();
    m_coeffTri[0].y = param["y0"].toDouble();
    m_coeffTri[1].x = param["x1"].toDouble();
    m_coeffTri[1].y = param["y1"].toDouble();
    m_coeffTri[2].x = param["x2"].toDouble();
    m_coeffTri[2].y = param["y2"].toDouble();
    m_coeffTri[3].x = param["x3"].toDouble();
    m_coeffTri[3].y = param["y3"].toDouble();
    m_flagIndex = param["flagIndex"].toInt();
    m_borderModeIndex = param["borderModeIndex"].toInt();
}

void PerspectiveTransformations::getModuleParameter(QJsonObject &param)
{
    param["x0"] = m_coeffTri[0].x;
    param["y0"] = m_coeffTri[0].y;
    param["x1"] =m_coeffTri[1].x;
    param["y1"] =m_coeffTri[1].y;
    param["x2"] =m_coeffTri[2].x;
    param["y2"] =m_coeffTri[2].y;
    param["x3"] =m_coeffTri[3].x;
    param["y3"] =m_coeffTri[3].y;
    param["flagIndex"] = m_flagIndex;
    param["borderModeIndex"] = m_borderModeIndex;
}

void PerspectiveTransformations::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    m_srcTri[0] = Point2f( 0,0 );
    m_srcTri[1] = Point2f( m_frame.size().width - 1, 0 );
    m_srcTri[2] = Point2f( 0, m_frame.size().height - 1 );
    m_srcTri[3] = Point2f(  m_frame.size().width - 1, m_frame.size().height - 1 );

    m_dstTri[0] = Point2f( m_frame.size().width*m_coeffTri[0].x, m_frame.size().height*m_coeffTri[0].y );
    m_dstTri[1] = Point2f( m_frame.size().width*m_coeffTri[1].x, m_frame.size().height*m_coeffTri[1].y );
    m_dstTri[2] = Point2f( m_frame.size().width*m_coeffTri[2].x, m_frame.size().height*m_coeffTri[2].y );
    m_dstTri[3] = Point2f( m_frame.size().width*m_coeffTri[3].x, m_frame.size().height*m_coeffTri[3].y );

    m_warpMat = getPerspectiveTransform(m_srcTri,m_dstTri);
    // преобразование перспективы
    m_outFrame = Mat::zeros( m_frame.rows, m_frame.cols, m_frame.type());

    warpPerspective(m_frame, m_outFrame, m_warpMat, m_outFrame.size(),
                m_flagValues[m_flagIndex],m_borderModeValues[m_borderModeIndex],
                Scalar());

    emit outputVideoStream(m_outFrame);
}
