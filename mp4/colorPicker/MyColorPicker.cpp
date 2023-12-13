#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
MyColorPicker::MyColorPicker(double favourate)
  : lu(favourate) { }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  if(x>y){
    HSLAPixel pixel1(180,1,lu);
    
  }
  return HSLAPixel();
}
