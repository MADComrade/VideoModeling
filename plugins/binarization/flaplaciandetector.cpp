#include "flaplaciandetector.h"
#include "additionmethods.h"
#include "blockenums.h"
#include "moduleconfig.h"
#include <QMutexLocker>

using namespace cv;
FLaplacianDetector::FLaplacianDetector(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Laplacian");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Binarization);
    setModuleType(BLOCKSTYPE::ModuleType::Laplacian);
}

FLaplacianDetector::~FLaplacianDetector()
{
    QMutexLocker lock(&m_mutex);
}

void FLaplacianDetector::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    if(m_processingFlag){
        frame.copyTo(m_frame);
        Laplacian( m_frame, m_outFrame, CV_16S, m_kernelSize, m_scale, m_delta, BORDER_DEFAULT );
        convertScaleAbs( m_outFrame, m_outFrame );
    }else{
        m_frame = computeDFT(frame);
        Mat filter = getLaplacianFilter(m_frame.size());

        m_outFrame = computeIDFT(m_frame.mul(filter));
    }
    emit outputVideoStream(m_outFrame);
}

int FLaplacianDetector::delta() const
{
    return m_delta;
}

void FLaplacianDetector::setDelta(int delta)
{
    m_delta = delta;
}

void FLaplacianDetector::setModuleParameter(const QJsonObject &param)
{
    m_processingFlag = param["processingFlag"].toBool();
    m_delta = param["delta"].toInt();
    m_kernelSize = param["kernelSize"].toInt();
    m_scale = param["scale"].toInt();
}

void FLaplacianDetector::getModuleParameter(QJsonObject &param)
{
    param["processingFlag"] = m_processingFlag;
    param["delta"] = m_delta;
    param["kernelSize"] =  m_kernelSize;
    param["scale"] =  m_scale;
}

int FLaplacianDetector::scale() const
{
    return m_scale;
}

void FLaplacianDetector::setScale(int scale)
{
    m_scale = scale;
}


bool FLaplacianDetector::processingFlag() const
{
    return m_processingFlag;
}

void FLaplacianDetector::setProcessingFlag(bool processingFlag)
{
    m_processingFlag = processingFlag;
}
