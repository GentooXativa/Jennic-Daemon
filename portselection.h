#ifndef PORTSELECTION_H
#define PORTSELECTION_H

#include <QDialog>

namespace Ui {
    class PortSelection;
}

class PortSelection : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelection(QWidget *parent = 0);
    ~PortSelection();

private:
    Ui::PortSelection *ui;
};

#endif // PORTSELECTION_H
