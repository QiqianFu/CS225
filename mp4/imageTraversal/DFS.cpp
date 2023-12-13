#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  array = vector<Point>();
  orig = png ;
  visited = vector<vector<int>>(png.width(),vector<int>(png.height()));
  for (unsigned int i =0; i< png.width(); i++){
    for (unsigned int j = 0; j < png.height(); j++){
      visited[i][j]=0;
    }
  }
  head_ = start;
  current = start;
  length = tolerance;
  array.push_back(head_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  array.pop_back();
  add(head_);
  visited[head_.x][head_.y] = 1;
  return ImageTraversal::Iterator(head_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  return ImageTraversal::Iterator(Point(-1,-1),this);
}

bool DFS::is_visited(int a, int b){
  if(visited[a][b]==0){
    return true;
  }else{
    return false;
  }
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  if (point ==Point(-1,-1)){
    return;
  }
  visited[point.x][point.y]=1;
  current = point;
  unsigned x_  = point.x;
  unsigned y_  = point.y;
  if(x_ > 2000){
    std::cout<<point<<std::endl;

  }

  if (x_ < orig.width()-1 && calculateDelta(*orig.getPixel(x_+1,y_), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_+1,y_)==true){
    array.push_back(Point(x_+1,y_));
  }
  if (y_ < orig.height()-1 && calculateDelta(*orig.getPixel(x_,y_+1), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_,y_+1)==true){
    array.push_back(Point(x_,y_+1));
  }
  if (x_ > 0 && calculateDelta(*orig.getPixel(x_-1,y_), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_-1,y_)==true){
    array.push_back(Point(x_-1,y_));
  }
  if (y_ > 0 && calculateDelta(*orig.getPixel(x_,y_-1), *orig.getPixel(head_.x,head_.y))<length && is_visited(x_,y_-1)==true) {
    array.push_back(Point(x_,y_-1));
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  if (array.empty()==true){
    return Point(-1,-1);
  }
  current = array.back();
  if(current.x > 2000){
    std::cout<<current<<std::endl;

  }
  
  while(is_visited(current.x,current.y)==false){
    if (array.empty()==true){
      return Point(-1,-1);
    }

    array.pop_back();
    current = array.back();
    if (array.empty()==true){
      return Point(-1,-1);
    }
    if(current.x > 2000){
      std::cout<<current<<std::endl;

    }

  }
  visited[current.x][current.y]=1;
  array.pop_back();
  return current;





}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  if (this->empty()==true){
    return Point(-1,-1);
  }
  return array.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  return array.empty();
}
