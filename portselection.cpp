#include "portselection.h"
#include "ui_portselection.h"

PortSelection::PortSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSelection)
{
    ui->setupUi(this);
}

PortSelection::~PortSelection()
{
    delete ui;
}
