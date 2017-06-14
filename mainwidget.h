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

protected:
    void closeEvent(QCloseEvent *event);

private:

    void initGui();
    void initConnections();

    ScriptRunner *process;
    LogWindow *logWindow;

    QPushButton *btnSetFile;
    QLineEdit *leParams;
    QPushButton *btnStart;

};

#endif // MAINWIDGET_H
