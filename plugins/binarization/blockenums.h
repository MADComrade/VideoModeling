#ifndef BLOCKENUMS_H
#define BLOCKENUMS_H
#include <QObject>
//!
//! \brief Класс с типами блоков обработки
//!
class BLOCKSTYPE {
public:
    /// тип блоков обработки видео
    enum ModuleType { ClearBlock = 0, /// пустой блок
                      /// для блоков отводится с 100 до 200
                      ThresholdBin = 300, /// блок бинаризации
                      AThresholdBin = 301,
                      Laplacian,
                      Canny
                    };
    Q_ENUM(ModuleType)

    Q_GADGET
    BLOCKSTYPE()=delete;
};
#endif // BLOCKENUMS_H
