#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtperfectelasticcollisionmenudialog.h"

#include "perfectelasticcollisionmenudialog.h"
#include "qtaboutdialog.h"
#include "qtperfectelasticcollisionmaindialog.h"
#include "ui_qtperfectelasticcollisionmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtPerfectElasticCollisionMenuDialog::QtPerfectElasticCollisionMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPerfectElasticCollisionMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtPerfectElasticCollisionMenuDialog::~QtPerfectElasticCollisionMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtPerfectElasticCollisionMenuDialog::on_button_start_clicked()
{
  QtPerfectElasticCollisionMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtPerfectElasticCollisionMenuDialog::on_button_about_clicked()
{
  About a = PerfectElasticCollisionMenuDialog().GetAbout();
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtPerfectElasticCollisionMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}
