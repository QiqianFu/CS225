/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  if (first[curDim] < second[curDim]){
    return true;
  }else if(first[curDim] == second[curDim]){
    return first < second;
  }else{
    return false;
  }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
  double distance1 = 0, distance2=0;
  for(unsigned int i = 0; i < Dim; i++ ){
    distance1 += (potential[i]-target[i])*(potential[i]-target[i]);
    distance2 += (target[i]-currentBest[i])*(target[i]-currentBest[i]);
  }
  if(distance1 < distance2){
    return true;
  }else if(distance1 == distance2){
    return potential < currentBest;
  }else{
    return false;
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
  vector<Point<Dim>> tempt = newPoints;
  if(newPoints.empty()==true){
    root=NULL;
    return;
  }
  quick_select(root, tempt , 0, 0, (int)newPoints.size()-1);

}
template <int Dim>
void KDTree<Dim>::quick_select(KDTreeNode*& root, vector<Point<Dim>>& newPoints, int dimension, int low, int up){
  if(low>up){
    return;
  }
  if(low==up){
    root = new KDTreeNode(newPoints[low]);
    return;
  }
  int dimension_now = (dimension)% Dim; 
  int target = (int)(up-low)/2 + low;
  find_mid(newPoints, low, up,dimension_now,target);
  int middle_one = target;
  root = new KDTreeNode(newPoints[middle_one]);
  quick_select(root->right,newPoints, dimension+1,middle_one+1, up);
  quick_select(root->left,newPoints,dimension+1, low, middle_one-1);
}
template <int Dim>
void KDTree<Dim>::find_mid(vector<Point<Dim>>& newPoints, int left, int right,int dim,int target){
  if(left == right){
    return;
  }
  unsigned int size = newPoints.size();
  int random = (right+left)/2;
  Point<Dim> pivot = newPoints[random];
  swap(random, right,newPoints);
  int store = left;
  
  for( int i = left; i < right; i++){
    if(newPoints[i][dim] < pivot[dim]){
      swap(store, i, newPoints);
      store++;
    }
  }
  swap(store,right,newPoints);
  if(store == target){
    return ;
  }
  if(store>target){
    find_mid(newPoints, left, store-1,dim,target);
  }else{
    find_mid(newPoints,store+1,right,dim,target);
  }
  return ;
  
}

template <int Dim>
void KDTree<Dim>::swap(int x, int y, vector<Point<Dim>>& newPoints){
  Point<Dim> temp = newPoints[x];
  newPoints[x] = newPoints[y];
  newPoints[y] = temp;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  
    /**
     * @todo Implement this function!
     */

  if (root==NULL){
    return Point<Dim>();
  }

  return digui(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::digui(const Point<Dim>& query,KDTreeNode* node,int dim) const{
  if(node->left==NULL && node->right == NULL){

    return node->point;
  }
  bool whichside;
  Point<Dim> tempt,tempt1,best;
  if(smallerDimVal(node->point,query,dim%Dim)){
    if (node->right!=NULL)
    {
      tempt = digui(query,node->right,dim+1);
      whichside=false;
    }else{
      tempt = node->point;
      return tempt;
    }
    
  }else{
    if (node->left!=NULL)
    {
      tempt = digui(query,node->left,dim+1);
      whichside=true;
    }else{
      tempt = node->point;
      return tempt;
    }
  }
  
  bool i = shouldReplace(query, tempt, node->point);
  if(i==true){
    tempt = node->point;
  }
  double query_to_now = (node->point[dim%Dim] - query[dim%Dim])*(node->point[dim%Dim] - query[dim%Dim]);
  

  double distance=0;
  for(unsigned int i = 0; i < Dim; i++ ){
    distance += (tempt[i]-query[i])*(tempt[i]-query[i]);
  }



  if(query_to_now < distance || (query_to_now==distance && node->point < tempt)){   //we should consider the other side
    if(whichside){
      if(node->right!=NULL){
        tempt1 = digui(query, node->right, dim+1);
      }
    }else{
        if(node->left!=NULL){
        tempt1 = digui(query, node->left, dim+1);
      }
    }
    if(shouldReplace(query, tempt, tempt1)){
      best = tempt1;
      return best;
    }
  }
  best = tempt;










  return best;
}