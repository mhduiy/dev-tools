#include "fastitemmodel.h"

FastItemModel::FastItemModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int FastItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_infos.size();
}

QVariant FastItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const FastItem *info = m_infos[index.row()];
    switch (role) {
    case IconRole:
        return info->iconName;
    case TitleRole:
        return info->title;
    case CmdRole:
        return info->cmd;
    default:
        return QVariant();
    }
}

QModelIndex FastItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column);
}

QHash<int, QByteArray> FastItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IconRole] = "icon";
    roles[TitleRole] = "title";
    roles[CmdRole] = "cmd";
    return roles;
}

void FastItemModel::reset(QList<FastItem *> infos)
{
    beginResetModel();
    m_infos = infos;
    endResetModel();
}