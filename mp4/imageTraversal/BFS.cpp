
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  queue_  = queue<Point>();
  visited = vector<vector<int>>(png.width(),vector<int>(png.height()));
  for (unsigned int i =0; i< png.width(); i++){
    for (unsigned int j = 0; j < png.height(); j++){
      visited[i][j]=0;
    }
  }
  orig    = png;
  head_   = start;
  current = start;
  queue_.push(head_);
  length = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  queue_.pop();
  add(head_);
  visited[head_.x][head_.y] = 1;
  return ImageTraversal::Iterator(head_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  return ImageTraversal::Iterator(Point(-1,-1), this);
}

bool BFS::is_visited(int a, int b){
  if(visited[a][b]==0){
    return true;
  }else{
    return false;
  }
}
/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  if (point ==Point(-1,-1)){
    return;
  }
  current = point;
  unsigned x_  = point.x;
  unsigned y_  = point.y;
  if (x_ < orig.width()-1 && calculateDelta(*orig.getPixel(x_+1,y_), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_+1,y_)==true){
    queue_.push(Point(x_+1,y_));
  }
  if (y_ < orig.height()-1 && calculateDelta(*orig.getPixel(x_,y_+1), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_,y_+1)==true){
    queue_.push(Point(x_,y_+1));
  }
  if (x_ > 0 && calculateDelta(*orig.getPixel(x_-1,y_), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_-1,y_)==true){
    queue_.push(Point(x_-1,y_));
  }
  if (y_ > 0 && calculateDelta(*orig.getPixel(x_,y_-1), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_,y_-1)==true) {
    queue_.push(Point(x_,y_-1));
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  if (queue_.empty()==true){
    return Point(-1,-1);
  }
  current = queue_.front();   
  while(is_visited(current.x,current.y)==false){
    queue_.pop();
    if (queue_.empty()==true){
      return Point(-1,-1);
    }
    current = queue_.front();


  } 
  visited[current.x][current.y]=1;
  queue_.pop();
  return current;

}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  if (this->empty()==true){
    return Point(-1,-1);
  }
  Point the_top = queue_.front();
  return the_top;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return queue_.empty();
}
