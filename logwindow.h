#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>

class QPlainTextEdit;

class LogWindow : public QDialog
{
public:
    explicit LogWindow(QWidget *parent = nullptr);
    ~LogWindow();

public slots:

    void appendMsg(const QString &msg);

private:
    void initGui();
    void initConnections();
    void saveSettings();
    void loadSettings();

    QPlainTextEdit *teLog;
};

#endif // LOGWINDOW_H
