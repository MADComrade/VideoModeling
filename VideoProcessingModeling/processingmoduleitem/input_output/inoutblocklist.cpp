#include "inoutblocklist.h"

QMap<QString, int> InOutBlockList::getBlocks()
{
    QMap<QString, int> bloks;
    bloks["Input"]=CONFUGUATOR::VideoInput;
    bloks["Output"]=CONFUGUATOR::VideoOutput;
    bloks["Image In"]=CONFUGUATOR::ImageInput;
    bloks["Video In"]=CONFUGUATOR::VideoParamIn;
    bloks["WebCam"]=CONFUGUATOR::WebCam;

    return bloks;
}

QString InOutBlockList::getBlockGroupName()
{
    return QString("Input and output blocks");
}

