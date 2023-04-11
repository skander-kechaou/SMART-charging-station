#include "image.h"
#include "mainwindow.h"
#include <QPainter>

ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() != 6) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QString id = index.sibling(index.row(), 0).data().toString(); // Get the ID from the model
    QSqlQuery query;
    query.prepare("SELECT imagepath FROM car WHERE licence_plate = ?");
    query.addBindValue(id);
    if (!query.exec() || !query.first()) {
        // Error handling
        return;
    }

    QString imagePath = query.value(0).toString();

    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(70, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation); // Resize the image
    QRect rect = option.rect;
    rect.setWidth(pixmap.width());
    rect.setHeight(pixmap.height());
    rect.moveTop(rect.top() + 10); // Adjust the position of the image

    painter->drawPixmap(rect, pixmap);
}


QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() != 2)
        return QStyledItemDelegate::sizeHint(option, index);

    QString imagePath = index.data().toString();

    QPixmap pixmap(imagePath);
    return pixmap.size();
}
