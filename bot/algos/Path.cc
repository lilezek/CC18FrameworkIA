#include "Path.h"

std::ostream & operator<<(std::ostream & o, const Path & p) {
  auto arrow = "";
  for (const Step & s: p) {
    o << arrow << s.point;
    arrow = " -> ";
  }
}