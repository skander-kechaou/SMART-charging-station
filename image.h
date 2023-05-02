#ifndef IMAGE_H
#define IMAGE_H

#include <QStyledItemDelegate>

class ImageDelegate : public QStyledItemDelegate
{
public:
    ImageDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // IMAGE_H
