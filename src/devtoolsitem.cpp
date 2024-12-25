#include "devtoolsitem.h"
#include "fastitemmodel.h"
#include "pluginfactory.h"
#include <applet.h>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QProcess>
#include <QDir>

#define ICON_KEY "icon"
#define TITLE_KEY "title"
#define CMD_KEY "cmd"

const QString CONFIG_PATH = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + QDir::separator() + "devtools.json";

DS_USE_NAMESPACE

namespace dock {

DevToolsItem::DevToolsItem(QObject *parent)
    : DApplet(parent)
    , m_iconName("App")
    , m_helper(new ConfigFileHelper(this))
    , m_model(new FastItemModel(this))
{   
    QMetaObject::invokeMethod(m_helper, &ConfigFileHelper::reload, Qt::QueuedConnection);
    connect(m_helper, &ConfigFileHelper::loadFinish, this, [this]() {
        m_model->reset(m_helper->getFastItem());
    });
}

bool DevToolsItem::init()
{
    DApplet::init();

    return true;
}

void DevToolsItem::invokeCommand(const QString &cmd)
{
    qInfo() << "invoke:" << cmd;
    QProcess::startDetached("/usr/bin/bash", {"-c", cmd});
}

D_APPLET_CLASS(DevToolsItem)

ConfigFileHelper::ConfigFileHelper(QObject *parent)
    : QObject(parent)
    , m_fileWatcher(new QFileSystemWatcher(this))
{
    qInfo() << "config file: " << CONFIG_PATH;
    QFile file(CONFIG_PATH);
    if (file.open(QIODevice::ReadWrite)) {
        if (file.readAll().simplified().isEmpty()) {
            QJsonArray initArray;
            QJsonObject initObject;
            initObject.insert(ICON_KEY, "App");
            initObject.insert(TITLE_KEY, "配置");
            initObject.insert(CMD_KEY, "code " + CONFIG_PATH);
            initArray.append(initObject);
            QJsonDocument doc;
            doc.setArray(initArray);
            auto bytes = doc.toJson();
            file.write(bytes);
            file.close();
        }
    }
    m_fileWatcher->addPath(CONFIG_PATH);
    connect(m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &ConfigFileHelper::onFileChanged);
}

ConfigFileHelper::~ConfigFileHelper()
{
    clearAll();
}

QList<FastItem *> ConfigFileHelper::getFastItem()
{
    return m_fastItems;
}

void ConfigFileHelper::reload()
{
    clearAll();
    QFile file(CONFIG_PATH);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isArray()) {
            QJsonArray rootArray = doc.array();
            for (const auto &jsonValueItem : rootArray) {
                if (jsonValueItem.isObject()) {
                    auto itemObject = jsonValueItem.toObject();
                    if (itemObject.contains(ICON_KEY) && itemObject.contains(TITLE_KEY) && itemObject.contains(CMD_KEY)) {
                        FastItem *fastItem = new FastItem();
                        fastItem->iconName = itemObject.value(ICON_KEY).toString();
                        fastItem->title = itemObject.value(TITLE_KEY).toString();
                        fastItem->cmd = itemObject.value(CMD_KEY).toString();
                        m_fastItems.append(fastItem);
                    } else {
                        qWarning() << "json object is invalid" << itemObject;
                    }
                }
            }
        }
    }
    Q_EMIT loadFinish();
}

void ConfigFileHelper::onFileChanged(const QString &filePath)
{
    if (filePath == CONFIG_PATH) {
        reload();
    }
}

void ConfigFileHelper::clearAll()
{
    qDeleteAll(m_fastItems);
    m_fastItems.clear();
}
}


#include "devtoolsitem.moc"
