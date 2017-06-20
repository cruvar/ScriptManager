#ifndef DYNAMICPARAMETER_H
#define DYNAMICPARAMETER_H

#include <QWidget>

class DynamicParameter : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicParameter(int count, QWidget *parent = 0);

signals:
    void textChanged(QString);

public slots:

    int getCounter();

    QString getParamString();

private:

    void initGui();

    int counter;

    QString parameter;
};

#endif // DYNAMICPARAMETER_H
