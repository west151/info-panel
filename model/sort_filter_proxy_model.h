#ifndef SORT_FILTER_PROXY_MODEL_H
#define SORT_FILTER_PROXY_MODEL_H

#include <QSortFilterProxyModel>

class sort_filter_proxy_model : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    sort_filter_proxy_model(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // SORT_FILTER_PROXY_MODEL_H
