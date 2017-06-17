#include "scriptrunner.h"
#include "defines.h"

#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

ScriptRunner::ScriptRunner(QObject *parent)
    : QObject(parent)
    , process(new QProcess(this))
{
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
//    process->start("ping localhost");
    process->start("python", pythonCommandArguments);
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
    emit readyReadStdout(QString(sout));
}

void ScriptRunner::readStdErr()
{
    QByteArray serr;
    serr = process->readAllStandardError();
    emit readyReadStderr(QString(serr));
}
