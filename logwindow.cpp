#include "logwindow.h"

#include <QPlainTextEdit>
#include <QVBoxLayout>

LogWindow::LogWindow(QWidget *parent) : QDialog(parent)
{
    initGui();
}

void LogWindow::appendMsg(const QString &msg)
{
    teLog->insertPlainText(msg);
}

void LogWindow::initGui()
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    QVBoxLayout *leMain = new QVBoxLayout(this);
    {
        teLog = new QPlainTextEdit(this);
        leMain->addWidget(teLog);
    }
}
