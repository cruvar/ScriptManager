#include "scriptrunner.h"
#include "defines.h"

#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

ScriptRunner::ScriptRunner(QObject *parent)
    : QObject(parent)
    , process(new QProcess(this))
{
    pythonCommandArguments << "";
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

    process->start("python", pythonCommandArguments);
}

void ScriptRunner::stop()
{
    process->close();
}

void ScriptRunner::setFile(const QString &filePath)
{
    pythonCommandArguments.replace(0, filePath);
    qDebug() << pythonCommandArguments;
}

void ScriptRunner::setArgument(int num, const QString &text)
{
    pythonCommandArguments.replace(num, text);
}

void ScriptRunner::addArgument()
{
    pythonCommandArguments.append("");
}

void ScriptRunner::delArgument()
{
    pythonCommandArguments.removeLast();
}

void ScriptRunner::readStdOut()
{
    QByteArray sout;
    sout = process->readAllStandardOutput();
    emit readyReadStdout(tr(sout));
}

void ScriptRunner::readStdErr()
{
    QByteArray serr;
    serr = process->readAllStandardError();
    emit readyReadStderr(tr(serr));
}
