#pragma once

#include <QAbstractListModel>

enum {
    IconRole = Qt::UserRole + 1,
    TitleRole,
    CmdRole
};

struct FastItem {
    QString iconName;
    QString title;
    QString cmd;
};

class FastItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FastItemModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column = 1, const QModelIndex &parent = QModelIndex()) const override;

    void reset(QList<FastItem *> infos);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<FastItem *> m_infos;
};
