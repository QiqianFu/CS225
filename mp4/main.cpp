
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;       png.readFromFile("tests/pacman.png");
  DFS dfs(png, Point(40, 40), 0.05);
  DFS dfs2(png, Point(120, 120), 0.05);
  FloodFilledImage image(png);
  MyColorPicker picker(0.1);
  RainbowColorPicker rainbow(0.05);


  image.addFloodFill( dfs, picker );
  image.addFloodFill( dfs2, picker );


  Animation animation = image.animate(10000);



  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  




  return 0;
}
