#include "mainwindow.h"
#include "scriptrunner.h"
#include "logwindow.h"
#include "filebrowser.h"
#include "dynamicparameter.h"
#include "defines.h"

#include <QSettings>
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
    loadSettings();
    initConnections();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete logWindow;
}

void MainWindow::setPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, QSTRING("Open Directory"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    fileBrow->setRootPath(dir);
}

void MainWindow::addParam()
{
    dynParameterCounter++;
    DynamicParameter *dPar = new DynamicParameter(dynParameterCounter, this);
    layParams->addWidget(dPar);
    process->addArgument();
    connect(dPar,&DynamicParameter::textChanged,this, [=](QString str){
        process->setArgument(dynParameterCounter, str);
    }, Qt::UniqueConnection);
}

void MainWindow::delParam()
{
    for(int i = 0; i < layParams->count(); ++i){
        DynamicParameter *dPar = qobject_cast<DynamicParameter*>(layParams->itemAt(i)->widget());
        if(dPar->getCounter() == dynParameterCounter){
            dynParameterCounter--;
            process->delArgument();
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

void MainWindow::saveSettings()
{
    QSettings settings( "settings.conf", QSettings::IniFormat );
    settings.beginGroup( "MainWindowPosition" );
    settings.setValue( "x", this->x() );
    settings.setValue( "y", this->y() );
    settings.setValue( "width", this->width() );
    settings.setValue( "height", this->height() );
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings settings( "settings.conf", QSettings::IniFormat );

    settings.beginGroup( "MainWindowPosition" );
    int x = settings.value( "x", -1 ).toInt();
    int y = settings.value( "y", -1 ).toInt();
    int width = settings.value( "width", -1 ).toInt();
    int height = settings.value( "height", -1 ).toInt();
    settings.endGroup();

    if( x > 0 && y > 0 && width > 0 && height > 0 ) {
        this->setGeometry( x, y, width, height );
    }
}
