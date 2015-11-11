#include "manual.h"
#include "ui_manual.h"

Manual::Manual(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Manual)
{
  ui->setupUi(this);
}

Manual::~Manual()
{
  delete ui;
}
