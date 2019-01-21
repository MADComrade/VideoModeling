#ifndef BLOCKSENUM_H
#define BLOCKSENUM_H
#include <QObject>
//!
//! \brief Класс с типами блоков обработки
//!
class BLOCKSTYPE {
public:
    /// тип блоков обработки видео
    enum ModuleType { ClearBlock = 0, /// пустой блок
                      /// для блоков отводится с 100 до 200
                      MedianFil=100, /// медианный фильтр
                      Gaussian = 101, /// фильтр Гаусса
                      BilateralFil = 102, /// фильтр Bilateral
                      Gamma = 103,
                      Correlation = 104,
                      Histogramma = 105,
                      Logarithm = 106,
                      Negative = 107,
                      FGaussian = 108,
                      FIdeal,
                      FButterworth
                    };
    Q_ENUM(ModuleType)

    Q_GADGET
    BLOCKSTYPE()=delete;
};
#endif // BLOCKSENUM_H
