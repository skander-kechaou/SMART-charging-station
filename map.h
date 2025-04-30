#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QFile>
#include <QDataStream>
namespace Ui {
class map;
}

class map : public QDialog
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);
    ~map();

private:
    Ui::map *ui;
};

#endif // MAP_H
