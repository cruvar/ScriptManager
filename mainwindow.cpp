#include "mainwindow.h"
#include "scriptrunner.h"
#include "logwindow.h"
#include "filebrowser.h"
#include "dynamicparameter.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dynParameterCounter(0)
    , process(new ScriptRunner(this))
    , logWindow(new LogWindow(/*this*/))
{
    initGui();
    initConnections();
}

MainWindow::~MainWindow()
{
    delete logWindow;
}

void MainWindow::setPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, QSTRING("Open Directory"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    fileBrow->setRootIndex(dir);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    logWindow->close();
}

void MainWindow::initGui()
{
    QToolBar *tbMain = new QToolBar(this);
    {
        QAction *openAction = new QAction(this);
        {
            openAction->setIcon(QIcon(":/new/icons/icons/open-path.png"));
            connect(openAction,&QAction::triggered,this,&MainWindow::setPath);
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
        QGridLayout *layMain = new QGridLayout(wMain);
        {
            fileBrow = new FileBrowser(this);
            {

            }
            QGroupBox *gbControl = new QGroupBox(QSTRING("Script control:"), wMain);
            {
                QHBoxLayout *layControl = new QHBoxLayout(gbControl);
                {
                    QPushButton *btnAddArg = new QPushButton(QIcon(":/new/icons/icons/add.png"), QSTRING(""), gbControl);
                    QPushButton *btnDelArg = new QPushButton(QIcon(":/new/icons/icons/del.png"), QSTRING(""), gbControl);
//                    connect(btnAddArg,&QPushButton::clicked,this,[=]{
//                        dynParameterCounter++
//                        DynamicParameter *dPar = new DynamicParameter(dynParameterCounter, this);
//                    });

//                    connect(btnDelArg,&QPushButton::clicked,this,[=]{
//                        dynParameterCounter--
//                        layControl->removeWidget();
//                    });

                    QPushButton *btnStart = new QPushButton(QSTRING("Start"), gbControl);
                    connect(btnStart,&QPushButton::clicked,process,&ScriptRunner::start);


                    layControl->setAlignment(Qt::AlignTop);
                    layControl->addWidget(btnAddArg);
                    layControl->addWidget(btnDelArg);
                    layControl->addStretch();
                    layControl->addWidget(btnStart);
                }

            }

            QGroupBox *gbParams = new QGroupBox(QSTRING("Parameters:"), wMain);
            {
                QVBoxLayout *layParams = new QVBoxLayout(gbParams);
                {
                    DynamicParameter *dPar = new DynamicParameter(dynParameterCounter, this);

                    layParams->setAlignment(Qt::AlignTop);
                    layParams->addWidget(dPar);

                }
                gbParams->setLayout(layParams);
            }

            layMain->addWidget(fileBrow, 0,0, 10,1 );
            layMain->addWidget(gbControl, 0,1);
            layMain->addWidget(gbParams, 1,1, 9,1);
        }
    }
    this->setCentralWidget(wMain);
}

void MainWindow::initConnections()
{
    connect(process,&ScriptRunner::readyReadStdout,logWindow,&LogWindow::appendMsg);
    connect(process,&ScriptRunner::readyReadStderr,logWindow,&LogWindow::appendMsg);
}
