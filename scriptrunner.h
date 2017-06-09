#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H

#include <QObject>

class QProcess;

class ScriptRunner : public QObject
{
    Q_OBJECT
public:
    explicit ScriptRunner(QObject *parent = 0);
    ~ScriptRunner();

signals:

    void readyReadStdout(QString);

    void readyReadStderr(QString);

public slots:

    void start();

    void setFile(const QString& filePath);

    void setArguments(const QStringList &args);

private:

    void initConnections();

    void readStdOut();

    void readStdErr();

    QProcess *process;

    QString scriptFile;
    QStringList pythonCommandArguments;

};

#endif // SCRIPTRUNNER_H
