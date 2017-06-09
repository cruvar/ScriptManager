#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDialog>
#include <memory>

class QLineEdit;
class QTextEdit;

class ScriptRunner;

class MainWidget : public QDialog
{
    Q_OBJECT

public:
    MainWidget(QDialog *parent = 0);
    ~MainWidget();

public slots:

    void setFilePath();

private:

    void initGui();
    void initConnections();

    std::shared_ptr<ScriptRunner> process;

    QPushButton *btnSetFile;
    QLineEdit *leParams;
    QPushButton *btnStart;

    QTextEdit *teOut;

};

#endif // MAINWIDGET_H
