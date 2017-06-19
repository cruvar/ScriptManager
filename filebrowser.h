#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>

class QDirModel;
class QTreeView;

class ScriptRunner;

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit FileBrowser(ScriptRunner *proc, QWidget *parent = 0);

signals:

public slots:

    void setRootIndex(const QString& path);

private:
    void initGui();

    ScriptRunner *process;

    QDirModel *model;
    QTreeView *twBrowser;

};

#endif // FILEBROWSER_H
