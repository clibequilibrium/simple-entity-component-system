#pragma once

#include "Base.h"
#include <set>

class System {
  public:
    std::set<Entity> m_Entities;
    virtual void     Update(){};
};