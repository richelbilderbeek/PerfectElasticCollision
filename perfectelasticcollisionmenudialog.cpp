#include "perfectelasticcollisionmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int ribi::PerfectElasticCollisionMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << this->GetHelp() << '\n';
    return 0;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::PerfectElasticCollisionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PerfectElasticCollision",
    "tool to investigate a perfect elastic collision",
    "the 7th of March 2012",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

ribi::Help ribi::PerfectElasticCollisionMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::PerfectElasticCollisionMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::PerfectElasticCollisionMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-08-14: version 1.0: initial version",
    "2012-03-07: version 1.1: added versioning. Added menu screen",
    "2013-11-04: version 1.2: conformized to ProjectRichelBilderbeekConsole",
    "2015-11-20: version 2.0: moved to own GitHub",
  };
}
