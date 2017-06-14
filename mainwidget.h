#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <memory>

class QLineEdit;
class QTextEdit;
class QPushButton;

class ScriptRunner;
class LogWindow;

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:

    void openFile();

private:

    void initGui();
    void initConnections();

    std::shared_ptr<ScriptRunner> process;
    LogWindow *logWindow;

    QPushButton *btnSetFile;
    QLineEdit *leParams;
    QPushButton *btnStart;

};

#endif // MAINWIDGET_H
