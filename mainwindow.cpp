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

void MainWindow::addParam()
{
    dynParameterCounter++;
    DynamicParameter *dPar = new DynamicParameter(dynParameterCounter, this);
    layParams->addWidget(dPar);
}

void MainWindow::delParam()
{
    for(int i = 0; i < layParams->count(); ++i){
        DynamicParameter *dPar = qobject_cast<DynamicParameter*>(layParams->itemAt(i)->widget());
        if(dPar->getCounter() == dynParameterCounter){
            dynParameterCounter--;
            dPar->hide();
            delete dPar;
        }
    }
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
            QGroupBox *gbFileBrowser = new QGroupBox(QSTRING("Files:"),wMain);
            {
                QVBoxLayout *layFiles = new QVBoxLayout(gbFileBrowser);
                {
                    fileBrow = new FileBrowser(process, gbFileBrowser);
                    layFiles->setMargin(0);
                    layFiles->addWidget(fileBrow);
                }
                gbFileBrowser->setLayout(layFiles);
            }

            QGroupBox *gbControl = new QGroupBox(QSTRING("Script control:"), wMain);
            {
                QHBoxLayout *layControl = new QHBoxLayout(gbControl);
                {
                    QPushButton *btnAddArg = new QPushButton(QIcon(":/new/icons/icons/add.png"), QSTRING(""), gbControl);
                    QPushButton *btnDelArg = new QPushButton(QIcon(":/new/icons/icons/del.png"), QSTRING(""), gbControl);
                    connect(btnAddArg,&QPushButton::clicked,this,&MainWindow::addParam);
                    connect(btnDelArg,&QPushButton::clicked,this,&MainWindow::delParam);


                    QPushButton *btnStart = new QPushButton(QSTRING("Start"), gbControl);
                    QPushButton *btnStop = new  QPushButton(QSTRING("Stop"), gbControl);
                    connect(btnStart,&QPushButton::clicked,process,&ScriptRunner::start);
                    connect(btnStop,&QPushButton::clicked,process,&ScriptRunner::stop);

                    layControl->setAlignment(Qt::AlignTop);
                    layControl->addWidget(btnAddArg);
                    layControl->addWidget(btnDelArg);
                    layControl->addStretch();
                    layControl->addWidget(btnStart);
                    layControl->addWidget(btnStop);
                }

            }

            QGroupBox *gbParams = new QGroupBox(QSTRING("Parameters:"), wMain);
            {
                layParams = new QVBoxLayout(gbParams);
                {

                }                
                layParams->setAlignment(Qt::AlignTop);
                gbParams->setLayout(layParams);
            }

            layMain->addWidget(gbFileBrowser, 0,0, 10,1 );
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
