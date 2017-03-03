#ifndef QTPERFECTELASTICCOLLISIONMENUDIALOG_H
#define QTPERFECTELASTICCOLLISIONMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPerfectElasticCollisionMenuDialog;
}

namespace ribi {

class QtPerfectElasticCollisionMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtPerfectElasticCollisionMenuDialog(QWidget *parent = 0);
  QtPerfectElasticCollisionMenuDialog(
    const QtPerfectElasticCollisionMenuDialog&) = delete;
  QtPerfectElasticCollisionMenuDialog& operator=(
    const QtPerfectElasticCollisionMenuDialog&) = delete;
  ~QtPerfectElasticCollisionMenuDialog() noexcept;

private slots:

  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked() noexcept;

private:
  Ui::QtPerfectElasticCollisionMenuDialog *ui;
};

} //~namespace ribi

#endif // QTPERFECTELASTICCOLLISIONMENUDIALOG_H
