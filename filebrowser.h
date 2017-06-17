#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>

class QDirModel;
class QTreeView;

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit FileBrowser(QWidget *parent = 0);

signals:

public slots:

    void setRootIndex(const QString& path);

private:
    void initGui();

    QDirModel *model;
    QTreeView *twBrowser;

};

#endif // FILEBROWSER_H
