// PerfectElasticCollision, WebAssembly core
// Copyright (C) 2010-2026 Richel Bilderbeek, GPL-3.0
//
// Dependency-free port of
// ribi::QtPerfectElasticCollisionMainDialog::DoPerfectElasticCollision
// (see qtperfectelasticcollisionmaindialog.cpp), compiled to WebAssembly
// with Emscripten for the website's Play page.
//
// Angles are in radians, clockwise, with 12 o'clock being 0.0
// and 3 o'clock being 0.5 * pi (screen coordinates, y points down).
#include <cmath>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

namespace {

constexpr double pi = 3.14159265358979323846;

/// Results of the last collision: angle1, speed1, angle2, speed2
double g_result[4] = {0.0, 0.0, 0.0, 0.0};

/// Obtain the angle in radians between two deltas
/// 12 o'clock is 0.0 * pi
///  3 o'clock is 0.5 * pi
///  6 o'clock is 1.0 * pi
///  9 o'clock is 1.5 * pi
double GetAngleClockScreen(const double dx, const double dy)
{
  double a = std::atan2(dx, -dy);
  if (a < 0.0) a += 2.0 * pi;
  return a;
}

void DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2)
{
  //The length of the impulse of player 1 (assumes both players have equal mass!)
  const double A = speed1;
  //The length of the impulse of player 2 (assumes both players have equal mass!)
  const double E = speed2;
  //The angles between the two globes
  const double c = angleCollision;
  //The angle between c and the impulse direction of player 1
  const double a = c - angle1;
  //The angle between c and the impulse direction of player 2
  const double b = c + pi - angle2;

  //Separate the impulses into parts parallel and orthogonal to the collision
  const double B = A * std::cos(a);
  const double C = A * std::sin(a);
  const double F = E * std::cos(b);
  const double G = E * std::sin(b);

  //Separate the impulses in X and Y directions
  const double BdX = B *  std::sin(c + (0.0 * pi));
  const double BdY = B * -std::cos(c + (0.0 * pi));
  const double CdX = C *  std::sin(c + (1.5 * pi));
  const double CdY = C * -std::cos(c + (1.5 * pi));
  const double FdX = F *  std::sin(c + (1.0 * pi));
  const double FdY = F * -std::cos(c + (1.0 * pi));
  const double GdX = G *  std::sin(c + (0.5 * pi));
  const double GdY = G * -std::cos(c + (0.5 * pi));

  //The resulting impulses
  const double DdX = CdX + FdX;
  const double DdY = CdY + FdY;
  const double HdX = BdX + GdX;
  const double HdY = BdY + GdY;

  angle1 = GetAngleClockScreen(DdX, DdY);
  angle2 = GetAngleClockScreen(HdX, HdY);
  speed1 = std::sqrt((DdX * DdX) + (DdY * DdY));
  speed2 = std::sqrt((HdX * HdX) + (HdY * HdY));
}

} //~namespace

extern "C" {

/// Calculate a perfect elastic collision between two globes of equal mass.
/// Read the results with pec_get_result
EMSCRIPTEN_KEEPALIVE
void pec_collide(
  const double angle_collision,
  const double angle1,
  const double speed1,
  const double angle2,
  const double speed2)
{
  double a1 = angle1;
  double s1 = speed1;
  double a2 = angle2;
  double s2 = speed2;
  DoPerfectElasticCollision(angle_collision, a1, s1, a2, s2);
  g_result[0] = a1;
  g_result[1] = s1;
  g_result[2] = a2;
  g_result[3] = s2;
}

/// Get a result of the last pec_collide call:
/// 0: angle1, 1: speed1, 2: angle2, 3: speed2
EMSCRIPTEN_KEEPALIVE
double pec_get_result(const int index)
{
  if (index < 0 || index > 3) return 0.0;
  return g_result[index];
}

} //~extern "C"
