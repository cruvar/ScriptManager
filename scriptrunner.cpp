#include "scriptrunner.h"

#include <QProcess>
#include <QCoreApplication>
#include <QDebug>
#include <QTranslator>

ScriptRunner::ScriptRunner(QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    initConnections();
}

ScriptRunner::~ScriptRunner()
{
    process->close();
}

void ScriptRunner::initConnections()
{
    connect(process,&QProcess::readyReadStandardOutput,this,&ScriptRunner::readStdOut);
}

void ScriptRunner::start()
{
    process->start("ping localhost");
//    process->waitForFinished(-1); // will wait forever until finished
//    process->start("python.exe", pythonCommandArguments);
    qDebug() << "start";
}

void ScriptRunner::setFile(const QString &filePath)
{
    scriptFile = QCoreApplication::applicationDirPath() + filePath;
    pythonCommandArguments << filePath;
    qDebug() << filePath;
}

void ScriptRunner::setArguments(const QStringList& args)
{
    pythonCommandArguments << args;
}


void ScriptRunner::readStdOut()
{
    QByteArray sout;
    sout = process->readAllStandardOutput();
    emit readyReadStdout(QString(sout).toStdString().c_str());
}

void ScriptRunner::readStdErr()
{
    QByteArray serr;
    serr = process->readAllStandardError();
    emit readyReadStderr(QString(serr).toStdString().c_str());
}
