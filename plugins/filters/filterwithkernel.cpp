#include "filterwithkernel.h"

FilterWithKernel::FilterWithKernel(QObject *parent)
    :CommonProcessing(parent)
{
    m_kernelList<<"3"<<"5"<<"7"<<"9";
    m_values<<3<<5<<7<<9;
}

FilterWithKernel::~FilterWithKernel()
{

}

QStringList FilterWithKernel::kernelList() const
{
    return m_kernelList;
}

int FilterWithKernel::kernelIndex() const
{
    return m_kernelIndex;
}

void FilterWithKernel::setKernelIndex(int index)
{
    m_kernelIndex = index;
    m_kernelValue = m_values[index];
}

void FilterWithKernel::intputVideoStream(const cv::Mat &frame)
{
    Q_UNUSED(frame)

}
