#include "logwindow.h"

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QDebug>

LogWindow::LogWindow(QWidget *parent) : QDialog(parent)
{
    initGui();
}

LogWindow::~LogWindow()
{
    qDebug() << "delete logwindow";
}

void LogWindow::appendMsg(const QString &msg)
{
    teLog->insertPlainText(msg);
}

void LogWindow::initGui()
{
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    QVBoxLayout *leMain = new QVBoxLayout(this);
    {
        teLog = new QPlainTextEdit(this);
        leMain->addWidget(teLog);
    }
}
