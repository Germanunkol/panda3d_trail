#ifndef TRAILNODE_H
#define TRAILNODE_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

class EXPORT_CLASS TrailNode {
PUBLISHED:
  // These methods are publicly accessible to Python and C++

  TrailNode( LPoint3f pos, LVector3f normal = LVector3f(0,0,0) );
  ~TrailNode() {};

  LPoint3f get_pos() { return this->position; }
  void set_pos( LPoint3f position ) { this->position = position; }

  LVector3f get_normal() { return this->normal; }
  void set_normal( LVector3f normal ) { this->normal = normal; }

public:
  // C++-only methods:
  
private:
  LPoint3f position;
  LVector3f normal;
};

#endif
