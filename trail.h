#ifndef TRAIL_H
#define TRAIL_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lvector3.h"
#include "lvector4.h"

#include <deque>
#include <vector>

#include "trailNode.h"

class EXPORT_CLASS Trail {
PUBLISHED:
  // These methods are publicly accessible to Python and C++

  Trail( float node_dist = 0.3, float max_length = 1 );
  ~Trail() {};

	/* Append to the right side (i.e. the 'end') of the trail
	Note: If the distance between this node and the second-to-last node is less than
	node_dist, move the last node instead!
  */
  void add_point( TrailNode& node );
  /* Removes and returns the last node in the trail */
  TrailNode popleft();

  float get_length();
  size_t get_size();

  TrailNode get_point( float dist_from_start );

  void debug_display( NodePath parent );

public:
  // C++-only methods:
  
private:
  /* Shortens the trail until it's no longer larger than max_length. */ 
  void shorten_if_necessary();

  std::deque<TrailNode> nodes;

  float node_dist;
  float node_dist_squared;
  float max_length;
  float trail_length;

  LVector4f debug_col;

  NodePath debug_node;
};

#endif
