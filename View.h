#include "GameObject.h"
#include "Point2D.h"

#ifndef VIEW_H
#define VIEW_H

const int view_maxsize = 20;

class View
{
public:

  // Constructors/Destructors
  View();

  //Public Member Functions
  void Clear();
  void Plot(GameObject* ptr);
  void Draw();

private:
  
  // Private member variables
  int size;
  double scale;
  Point2D origin;
  char grid[view_maxsize][view_maxsize][2];

  // Private methods
   bool GetSubscripts(int& out_x, int& out_y, Point2D location);

};

#endif // VIEW_H
