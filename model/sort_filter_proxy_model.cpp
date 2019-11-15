#include "sort_filter_proxy_model.h"

sort_filter_proxy_model::sort_filter_proxy_model(QObject *parent):
    QSortFilterProxyModel(parent)
{

}

bool sort_filter_proxy_model::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (filterRegExp().isEmpty())
        return true;

    for (int i = 0; i < sourceModel()->columnCount(); ++i) {
        const auto index = sourceModel()->index(sourceRow, i, sourceParent);
        if (sourceModel()->data(index).toString().toLower().trimmed().contains(filterRegExp()))
            return true;
    }
    return false;
}
