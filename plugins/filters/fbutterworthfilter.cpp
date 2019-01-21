#include "fbutterworthfilter.h"
#include "additionmethods.h"
#include "blockenums.h"
#include "moduleconfig.h"

FButterworthFilter::FButterworthFilter(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("FButterworth");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::FButterworth);
}

FButterworthFilter::~FButterworthFilter()
{
    QMutexLocker lock(&m_mutex);
}

void FButterworthFilter::intputVideoStream(const cv::Mat &frame)
{
    //    if(m_inverseFlag){
    //        m_outFrame = computeDFT(254-frame);
    //    }else{
    //         m_outFrame = computeDFT(frame);
    //    }
    QMutexLocker lock(&m_mutex);
    m_outFrame = computeDFT(frame);
    if(m_inverseFlag){
        m_frame = getInverseButterworthFilter(m_outFrame.size(), m_width, m_order);
    }else{
        m_frame = getButterworthFilter(m_outFrame.size(), m_width, m_order);
    }
    //    m_frame = getButterworthFilter(m_outFrame.size(), m_width, m_order);
    //    if(m_inverseFlag){
    //        m_outFrame =254- computeIDFT(m_outFrame.mul(m_frame));
    //    }
    //    else{
    //        m_outFrame = computeIDFT(m_outFrame.mul(m_frame));
    //    }
    m_outFrame = computeIDFT(m_outFrame.mul(m_frame));
    emit outputVideoStream(m_outFrame);
}

int FButterworthFilter::order() const
{
    return m_order;
}

void FButterworthFilter::setOrder(int order)
{
    m_order = order;
}

void FButterworthFilter::setModuleParameter(const QJsonObject &param)
{
    m_width = param["width"].toDouble();
    m_inverseFlag = param["inverseFlag"].toBool();
    m_order = param["order"].toInt();
}

void FButterworthFilter::getModuleParameter(QJsonObject &param)
{
    param["width"] = m_width;
    param["inverseFlag"] = m_inverseFlag;
    param["order"] = m_order;
}

bool FButterworthFilter::inverseFlag() const
{
    return m_inverseFlag;
}

void FButterworthFilter::setInverseFlag(bool inverseFlag)
{
    m_inverseFlag = inverseFlag;
}

double FButterworthFilter::width() const
{
    return m_width;
}

void FButterworthFilter::setWidth(double width)
{
    m_width = width;
}
