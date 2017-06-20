#include "filebrowser.h"
#include "scriptrunner.h"

#include <QSettings>
#include <QDirModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>

FileBrowser::FileBrowser(ScriptRunner *proc, QWidget *parent)
    : QWidget(parent)
    , process(proc)
{
    initGui();
    loadSettings();
}

FileBrowser::~FileBrowser()
{
    saveSettings();
}

void FileBrowser::setRootPath(const QString &path)
{
    rootPath = path;
    twBrowser->setRootIndex(model->index(rootPath));
}

void FileBrowser::initGui()
{
    QVBoxLayout *layMain = new QVBoxLayout(this);
    {
        twBrowser = new QTreeView(this);
        {
            model = new QDirModel(twBrowser);
            model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
            model->setNameFilters(QStringList() << "*.py");
            twBrowser->setModel(model);
            twBrowser->setRootIndex(model->index(QDir::homePath()));
            twBrowser->setColumnHidden( 1, true );
            twBrowser->setColumnHidden( 2, true );
            twBrowser->setColumnHidden( 3, true );
            connect(twBrowser,&QTreeView::doubleClicked,this,[=](QModelIndex index){
                QDirModel model;
                if(model.fileInfo(index).absoluteFilePath().endsWith(".py")){
                    process->setFile(model.fileInfo(index).absoluteFilePath());
                } else return;
            });

        }
        layMain->addWidget(twBrowser);
    }
}

void FileBrowser::saveSettings()
{
    QSettings settings( "settings.conf", QSettings::IniFormat );
    settings.beginGroup( "FileBrowserSettings" );
    settings.setValue( "RootPath", rootPath );
    settings.endGroup();
}

void FileBrowser::loadSettings()
{
    QSettings settings( "settings.conf", QSettings::IniFormat );
    settings.beginGroup( "FileBrowserSettings" );
    QString path = settings.value("RootPath", QDir::currentPath()).toString();
    settings.endGroup();

    this->setRootPath(path);
}
