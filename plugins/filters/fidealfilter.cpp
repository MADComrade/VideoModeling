#include "fidealfilter.h"
#include "additionmethods.h"
#include "blockenums.h"
#include "moduleconfig.h"

FIdealFilter::FIdealFilter(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("FIdeal");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::FIdeal);
}

FIdealFilter::~FIdealFilter()
{
    QMutexLocker lock(&m_mutex);
}

void FIdealFilter::intputVideoStream(const cv::Mat &frame)
{
    //    if(m_inverseFlag){
    //        m_outFrame = computeDFT(254-frame);
    //    }else{
    //        m_outFrame = computeDFT(frame);
    //    }
    QMutexLocker lock(&m_mutex);
    m_outFrame = computeDFT(frame);
    if(m_inverseFlag){
        m_frame = getInverseIdealFilter(m_outFrame.size(), m_width);
    }else{
        m_frame = getIdealFilter(m_outFrame.size(), m_width);
    }


    m_outFrame = computeIDFT(m_outFrame.mul(m_frame));
    emit outputVideoStream(m_outFrame);
}

double FIdealFilter::getWidth() const
{
    return m_width;
}

void FIdealFilter::setWidth(double width)
{
    m_width = width;
}

void FIdealFilter::setModuleParameter(const QJsonObject &param)
{
    m_inverseFlag = param["inverseFlag"].toBool();
    m_width = param["width"].toDouble();
}

void FIdealFilter::getModuleParameter(QJsonObject &param)
{
    param["inverseFlag"] = m_inverseFlag;
    param["width"] = m_width;
}

bool FIdealFilter::getInverseFlag() const
{
    return m_inverseFlag;
}

void FIdealFilter::setInverseFlag(bool inverseFlag)
{
    m_inverseFlag = inverseFlag;
}
