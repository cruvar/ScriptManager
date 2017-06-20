#include "logwindow.h"

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QSettings>
#include <QDebug>

LogWindow::LogWindow(QWidget *parent) : QDialog(parent)
{
    initGui();
    loadSettings();
}

LogWindow::~LogWindow()
{
    saveSettings();
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
        teLog->setReadOnly(true);
        leMain->addWidget(teLog);
    }
}

void LogWindow::saveSettings()
{
    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup("LogWindowPosition");
    settings.setValue("x", this->x());
    settings.setValue("y", this->y());
    settings.setValue("width", this->width());
    settings.setValue("height", this->height());
    settings.endGroup();
}

void LogWindow::loadSettings()
{
    QSettings settings( "settings.conf", QSettings::IniFormat );

    settings.beginGroup("LogWindowPosition");
    int x = settings.value("x", -1).toInt();
    int y = settings.value("y", -1).toInt();
    int width = settings.value("width", -1).toInt();
    int height = settings.value("height", -1).toInt();
    settings.endGroup();

    if(x > 0 && y > 0 && width > 0 && height > 0) {
        this->setGeometry(x, y, width, height);
    }
}
