#ifndef STREET_H
#define STREET_H

#include <QWidget>

namespace Ui {
class street;
}

class street : public QWidget
{
    Q_OBJECT

public:
    explicit street(QWidget *parent = 0);
    ~street();

private:
    Ui::street *ui;
};

#endif // STREET_H
