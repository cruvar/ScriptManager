#include "dynamicparameter.h"
#include "defines.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

DynamicParameter::DynamicParameter(int count, QWidget *parent)
    : QWidget(parent)
    , counter(count)
{
    initGui();
}

int DynamicParameter::getCounter()
{
    return counter;
}

QString DynamicParameter::getParamString()
{
    return parameter;
}

void DynamicParameter::initGui()
{
    QHBoxLayout *layMain = new QHBoxLayout(this);
    {
        QLineEdit *leParam = new QLineEdit(this);
        connect(leParam,&QLineEdit::textChanged,this,[=](QString str){
            parameter = str;
        });

        layMain->setMargin(0);
        layMain->addWidget(new QLabel(QSTRING("Par #%1").arg(counter)));
        layMain->addWidget(leParam);
    }
    this->setLayout(layMain);
}
