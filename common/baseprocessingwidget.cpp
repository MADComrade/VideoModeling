#include "baseprocessingwidget.h"
#include "ui_baseprocessingwidget.h"

BaseProcessingWidget::BaseProcessingWidget(QWidget *parent) :
    CommonWidget(parent),
    ui(new Ui::BaseProcessingWidget)
{
    ui->setupUi(this);
    this->setOutputImageLable(ui->outVideoImage);
}

BaseProcessingWidget::~BaseProcessingWidget()
{
    delete ui;
}

void BaseProcessingWidget::setSettingsWidget(QWidget *setting)
{
    ui->settingsLayout->addWidget(setting);
}

void BaseProcessingWidget::setTitleWidget(const QString &title)
{
    setWindowTitle(title);
}
