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
                      AffineTr = 400, /// с 400 до 500
                      PerspectiveTr = 401,
                      Povod = 402,
                      Scale,
                      Rotate,
                      Translate,
                      ROI,
                      Delay,
                      GaussianNoise,
                      SaltAndPaperNoise
                    };
    Q_ENUM(ModuleType)

    Q_GADGET
    BLOCKSTYPE()=delete;
};
#endif // BLOCKENUMS_H
