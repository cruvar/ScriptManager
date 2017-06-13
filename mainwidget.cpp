#include "mainwidget.h"
#include "scriptrunner.h"
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
{
    initGui();
    initConnections();
}

MainWidget::~MainWidget()
{

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
//            connect(showLogAction,&QAction::triggered,this,/*show the mf log*/)
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
                        btnSetFile = new QPushButton(QSTRING("Set_script"), this);
                        leParams = new QLineEdit(this);
                        btnStart = new QPushButton(QSTRING("Start"), this);

                        layScripts->addWidget(btnSetFile);
                        layScripts->addWidget(leParams);
                        layScripts->addWidget(btnStart);
                    }
                }
                layTop->addWidget(gbScripts);
            }

            QVBoxLayout *layBottom = new QVBoxLayout;
            {
                QGroupBox *gbOut = new QGroupBox(QSTRING("Output:"),this);
                {
                    QVBoxLayout *layOut = new QVBoxLayout(gbOut);
                    {
                        teOut = new QTextEdit(this);
                        layOut->addWidget(teOut);
                    }
                }
                layBottom->addWidget(gbOut);
            }
            layMain->addLayout(layTop);
            layMain->addLayout(layBottom);
        }
    }
    this->setCentralWidget(wMain);
}

void MainWidget::initConnections()
{
    connect(process.get(),&ScriptRunner::readyReadStdout,teOut,&QTextEdit::insertPlainText);
    connect(process.get(),&ScriptRunner::readyReadStderr,teOut,&QTextEdit::insertPlainText);
    connect(btnSetFile,&QPushButton::clicked,this,&MainWidget::openFile);
    connect(btnStart,&QPushButton::clicked,process.get(),&ScriptRunner::start);
}
