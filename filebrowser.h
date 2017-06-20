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
    ~FileBrowser();

signals:

public slots:

    void setRootPath(const QString& path);

private:
    void initGui();
    void saveSettings();
    void loadSettings();

    ScriptRunner *process;

    QString rootPath;
    QDirModel *model;
    QTreeView *twBrowser;

};

#endif // FILEBROWSER_H
