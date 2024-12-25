#pragma once

#include "applet.h"
#include "dsglobal.h"
#include "fastitemmodel.h"

#include <QFileSystemWatcher>

namespace dock {

class ConfigFileHelper : public QObject
{
    Q_OBJECT
public:
    explicit ConfigFileHelper(QObject *parent = nullptr);
    ~ConfigFileHelper();
    QList<FastItem *> getFastItem();

public slots:    
    void reload();

private:
    void clearAll();
    void onFileChanged(const QString &filePath);

signals:
    void loadFinish();

private:
    QList<FastItem *> m_fastItems;
    QFileSystemWatcher *m_fileWatcher;
};

class DevToolsItem : public DS_NAMESPACE::DApplet
{
    Q_OBJECT
    Q_PROPERTY(QString iconName MEMBER m_iconName NOTIFY iconNameChanged FINAL)
    Q_PROPERTY(QAbstractListModel* model MEMBER m_model CONSTANT)
public:
    explicit DevToolsItem(QObject *parent = nullptr);
    virtual bool init() override;

    Q_INVOKABLE void invokeCommand(const QString &cmd);

Q_SIGNALS:
    void iconNameChanged();

private:
    QString m_iconName;
    ConfigFileHelper *m_helper = nullptr;
    FastItemModel *m_model = nullptr;
};

}
