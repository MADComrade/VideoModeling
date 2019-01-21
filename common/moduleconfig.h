#ifndef MODULECONFIG_H
#define MODULECONFIG_H
#include <QObject>
//!
//! \brief Класс с типами блоков обработки
//!
class CONFUGUATOR {
public:
    /// тип блоков обработки видео
    enum ModuleType { ClearBlock = 0, /// пустой блок
                      VideoInput=1, /// блок видео захвата из файла
                      VideoOutput=2, /// блок вывода видео
                      ImageInput = 3,
                      VideoParamIn = 4,
                      WebCam = 5
                    };
    Q_ENUM(ModuleType)

    /// Тип обработки
    enum BlockProcessing {None = 0, /// пусто
                          IO=1, /// ввод/вывод
                          Filtering, /// фильтрация
                          Binarization, /// бинаризация
                          Transformations,
                          Descriptor,
                          Masking
                         };
    Q_ENUM(BlockProcessing)

    Q_GADGET
    CONFUGUATOR()=delete;
};

#endif // MODULECONFIG_H
