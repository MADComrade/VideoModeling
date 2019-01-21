#ifndef FILTERWITHKERNEL_H
#define FILTERWITHKERNEL_H

#include "commonprocessing.h"

class FilterWithKernel: public CommonProcessing
{
public:
    FilterWithKernel(QObject *parent = 0);
    ~FilterWithKernel();
    QStringList kernelList() const;
    int kernelIndex() const;
    void setKernelIndex(int index);

public slots:
    void intputVideoStream(const cv::Mat& frame);

protected:
   int m_kernelIndex=0;
   int m_kernelValue=3;
   QStringList m_kernelList;
   QList<int> m_values;
};

#endif // FILTERWITHKERNEL_H
