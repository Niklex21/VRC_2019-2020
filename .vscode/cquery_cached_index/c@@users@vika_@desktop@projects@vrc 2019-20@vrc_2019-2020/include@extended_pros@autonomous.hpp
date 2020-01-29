#ifndef _AUTONOMOUS_HPP_
#define _AUTONOMOUS_HPP_

#include "main.h"
#include "enums/TeamColor.hpp"

namespace extended_pros{
  class AutonomousConf {
    public:
      AutonomousConf();
    private:
      int color = -1;
  };
}
#endif
