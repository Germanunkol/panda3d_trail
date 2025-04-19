#include "trail.h"
#include "lineSegs.h"

Trail::Trail( float node_dist, float max_length )
{
  this->node_dist = node_dist;
  this->node_dist_squared = node_dist*node_dist;
  this->max_length = max_length;
  this->trail_length = 0;

  this->debug_col = LVector4f(
      (float)rand()/(float)RAND_MAX,
      (float)rand()/(float)RAND_MAX,
      (float)rand()/(float)RAND_MAX,
      1 );
}

void Trail::add_point( TrailNode& node )
{
  if( this->nodes.size() > 1 )
  {
    TrailNode& second_last_node = *(this->nodes.end()-2);
    float dist2 = (second_last_node.get_pos() - node.get_pos()).length_squared();
    if( dist2 < this->node_dist_squared )
    {
      TrailNode& last_node = *(this->nodes.end()-1);
      float prev_dist = (last_node.get_pos() - second_last_node.get_pos()).length();
      // Set the last node to the new nodes' position/normal:
      last_node.set_pos( node.get_pos() );
      last_node.set_normal( node.get_normal() );
      float new_dist = sqrt( dist2 );
      this->trail_length = this->trail_length - prev_dist + new_dist;
      this->shorten_if_necessary();
      return;
    }
  }
  
  this->nodes.push_back( node );
  if( this->nodes.size() > 1 )
  {
    TrailNode& second_last_node = *(this->nodes.end()-2);
    TrailNode& last_node = *(this->nodes.end()-1);
    float new_seg_len = (last_node.get_pos() - second_last_node.get_pos()).length();
    this->trail_length += new_seg_len;
  } else {
    this->trail_length = 0;
  }
  this->shorten_if_necessary();
}

TrailNode Trail::get_point( float dist_from_start )
{
  /* Get a point on the path, (possibly lying between two TrailNodes of the path)
   * which is dist_from_start away from the newest position. Since the newest
   * position is the one that was added last, i.e. to the end of the deque, we 
   * need to search from the end of the deque */

  assert( this->nodes.size() > 0 && "Cannot retrieve point from empty trail!" );

  if( this->trail_length <= 0 )
    return this->nodes[0];

  float dist = dist_from_start;
  for( size_t i = this->nodes.size()-1; i >= 1; i-- )
  {
    TrailNode& node_cur = this->nodes[i];
    TrailNode& node_prev = this->nodes[i-1];
    float seg_len = (node_cur.get_pos() - node_prev.get_pos()).length();
    if( seg_len > dist )
    {
      float amount = (1.0 - dist/seg_len);
      // Lerp:
      LPoint3f pos = node_cur.get_pos() * amount + node_prev.get_pos() * (1.0 - amount);
      LVector3f normal = node_cur.get_normal() * amount + node_prev.get_normal() * (1.0 - amount);
      return TrailNode( pos, normal );
    }
    dist -= seg_len;
  }
  return this->nodes[0];   // Return last node if none found
}

TrailNode Trail::popleft()
{
  // Get the node:
  TrailNode first_node = *this->nodes.begin();
  this->nodes.pop_front();     // Actually remove the node
  if( this->nodes.size() > 1 )
  {
    TrailNode& second_node = *this->nodes.begin();
    float seg_len = (second_node.get_pos() - first_node.get_pos()).length();
    this->trail_length -= seg_len;
  } else {
    this->trail_length = 0;
  }
  return first_node;
}

void Trail::shorten_if_necessary()
{
  while( this->trail_length > this->max_length )
  {
    this->popleft();
  }
}

float Trail::get_length()
{
  return this->trail_length;
}

size_t Trail::get_size()
{
  return this->nodes.size();
}

void Trail::debug_display( NodePath parent )
{
  if( this->debug_node )
    this->debug_node.remove_node();

  if( this->nodes.size() == 0 )
    return;
  LineSegs lines;
  lines.set_thickness( 3 );
  lines.set_color( this->debug_col );
  lines.move_to( this->nodes[0].get_pos() );
  for( size_t i = 1; i < this->nodes.size(); i++ )
  {
    TrailNode& node = this->nodes[i];
    lines.draw_to( node.get_pos() );
  }
  this->debug_node = parent.attach_new_node( lines.create() );
}


