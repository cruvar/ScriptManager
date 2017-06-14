#include "mainwidget.h"
#include "scriptrunner.h"
#include "logwindow.h"
#include "defines.h"

#include <QLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QPushButton>
#include <QToolBar>
#include <QtGui>

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , process(std::make_shared<ScriptRunner>(this))
    , logWindow(new LogWindow())
{
    initGui();
    initConnections();
}

MainWidget::~MainWidget()
{
    qDebug() << "delete mainwindow";
    delete logWindow;
}

void MainWidget::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                QSTRING("Открыть файл"),
                                QDir::currentPath(),
                                "Python scripts(*.py);;All files (*.*)");
    process->setFile(filePath);
}

void MainWidget::initGui()
{
    setAttribute(Qt::WA_DeleteOnClose);

    QToolBar *tbMain = new QToolBar(this);
    {
        QAction *openAction = new QAction(this);
        {
            openAction->setIcon(QIcon(":/new/icons/icons/open.png"));
            connect(openAction,&QAction::triggered,this,&MainWidget::openFile);
            tbMain->addAction(openAction);
        }

        QAction *showLogAction = new QAction(this);
        {
            showLogAction->setIcon(QIcon(":/new/icons/icons/log.png"));
            connect(showLogAction,&QAction::triggered,logWindow,&LogWindow::open);
            tbMain->addAction(showLogAction);
        }
    }
    this->addToolBar(tbMain);

    QWidget *wMain = new QWidget(this);
    {
        QVBoxLayout *layMain = new QVBoxLayout(wMain);
        {
            QHBoxLayout *layTop = new QHBoxLayout;
            {
                QGroupBox *gbScripts = new QGroupBox(QSTRING("Scripts:"), this);
                {
                    QHBoxLayout *layScripts = new QHBoxLayout(gbScripts);
                    {
                        leParams = new QLineEdit(this);
                        btnStart = new QPushButton(QSTRING("Start"), this);
                        connect(btnStart,&QPushButton::clicked,process.get(),&ScriptRunner::start);

                        layScripts->addWidget(leParams);
                        layScripts->addWidget(btnStart);
                    }
                }
                layTop->addWidget(gbScripts);
            }
            layMain->addLayout(layTop);
        }
    }
    this->setCentralWidget(wMain);
}

void MainWidget::initConnections()
{
    connect(process.get(),&ScriptRunner::readyReadStdout,logWindow,&LogWindow::appendMsg);
    connect(process.get(),&ScriptRunner::readyReadStderr,logWindow,&LogWindow::appendMsg);
}
