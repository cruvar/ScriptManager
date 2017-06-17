#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class QLineEdit;
class QTextEdit;
class QPushButton;

class ScriptRunner;
class LogWindow;
class FileBrowser;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void setPath();

protected:
    void closeEvent(QCloseEvent *event);

private:

    void initGui();
    void initConnections();

    int dynParameterCounter;

    ScriptRunner *process;
    LogWindow *logWindow;
    FileBrowser *fileBrow;
};

#endif // MAINWINDOW_H
