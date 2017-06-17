#include "filebrowser.h"

#include <QDirModel>
#include <QTreeView>
#include <QVBoxLayout>

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
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
            twBrowser->setModel(model);
            twBrowser->setRootIndex(model->index(QDir::homePath()));
            twBrowser->setColumnHidden( 1, true );
            twBrowser->setColumnHidden( 2, true );
            twBrowser->setColumnHidden( 3, true );

        }
        layMain->addWidget(twBrowser);
    }
}
