#include "filebrowser.h"
#include "scriptrunner.h"

#include <QDirModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>

FileBrowser::FileBrowser(ScriptRunner *proc, QWidget *parent)
    : QWidget(parent)
    , process(proc)
{
    initGui();
}

void FileBrowser::setRootIndex(const QString &path)
{
    twBrowser->setRootIndex(model->index(path));
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
