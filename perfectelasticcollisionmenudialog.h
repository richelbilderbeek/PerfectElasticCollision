#ifndef PERFECTELASTICCOLLISIONMENUDIALOG_H
#define PERFECTELASTICCOLLISIONMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///PerfectElasticCollisionMenuDialog contains the PerfectElasticCollision menu dialog
struct  PerfectElasticCollisionMenuDialog final : public MenuDialog
{
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace ribi

#endif // PERFECTELASTICCOLLISIONMENUDIALOG_H
