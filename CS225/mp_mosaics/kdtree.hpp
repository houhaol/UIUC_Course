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
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim])
    {
      return (first < second);
    }
    
    return first[curDim] < second[curDim] ? true : false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double targetCurr = 0.0;
    double targetPote = 0.0;
    for (unsigned i = 0; i < Dim; i++)
    {
      targetCurr += (target[i] - currentBest[i])*(target[i] - currentBest[i]); 
      targetPote += (target[i] - potential[i])*(target[i] - potential[i]);
    }
    if (targetPote < targetCurr)
    {
      return true;
    }else if (targetPote > targetCurr)
    {
      return false;
    }else
    {
      return (potential < currentBest);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    this->points = newPoints;
    size = newPoints.size();
    if (size == 1)
    {
      // root = NULL;
      return;
    }
    int left = 0;
    int right = size - 1;

    root = buildTree(0, left, right);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int dim, int left, int right)
{
/*     if (left <= right)
    {
      int middle = (left + right) /2;
      // rearrange points according to quickselect algorithm
      select(left, right, middle, dim);
      KDTreeNode * subroot = new KDTreeNode (this->points[middle]);
      subroot->left = buildTree((dim+1)%Dim, left, middle-1);
      subroot->right = buildTree((dim+1)%Dim, middle+1, right);
      return subroot;
    }else
    {
      return NULL;
    } */
    if (left > right)
    {
      return NULL;
    }
    int middle = (left + right) /2;
    // rearrange points according to quickselect algorithm
    select(left, right, middle, dim);
    KDTreeNode * subroot = new KDTreeNode (this->points[middle]);
    subroot->left = buildTree((dim+1)%Dim, left, middle-1);
    subroot->right = buildTree((dim+1)%Dim, middle+1, right);
    return subroot;
}

template <int Dim>
void KDTree<Dim>::select(int left, int right, int middle, int dim)
{
  if (left == right)
  {
    return;
  }
  int pivotIndex = (left + right) / 2;
  pivotIndex = partition(left, right, pivotIndex, dim);
  
  if (middle == pivotIndex)
  {
    return;
  }
  else if (middle < pivotIndex)
  {
    select(left, pivotIndex-1, middle, dim);
  }
  else if (middle > pivotIndex)
  {
    select(pivotIndex+1, right, middle, dim);
  }
  
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dim)
{ 
  Point<Dim> pivotValue = this->points[pivotIndex];
  // swap list[pivotIndex] and list[right]
  std::swap(this->points[pivotIndex], this->points[right]);
  int storeIndex = left;
  for (int i = left; i < right; i++)
  {
    if (smallerDimVal(this->points[i], pivotValue, dim))
    {
      std::swap(this->points[storeIndex], this->points[i]);
      storeIndex++;
    }
  }
  std::swap(this->points[right], this->points[storeIndex]);
  return storeIndex;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy_(const KDTree<Dim>& other)
{
    this->points = other->points;
    size = points.size();
    if (size == 1)
    {
      // root = NULL;
      return;
    }
    int left = 0;
    int right = size - 1;

    root = buildTree(0, left, right);
    return root;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy_(other);
  
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs)
  {
    destroy_(rhs.root);
    root = copy_(rhs);
  }
  
  return *this;
}

template <int Dim>
void KDTree<Dim>::destroy_(KDTreeNode * subroot) 
{
  if (subroot == NULL)
  {
    return;
  }
  destroy_(subroot->left);
  destroy_(subroot->right);
  
  delete subroot;
  subroot = NULL;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroy_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    // if (points.empty())
    // {
    //   return Point<Dim>();
    // }
    // return nearestNeighbor_(query, 0, points.size() -1 , 0);
    
    return nearestNeighbor_(query, root , 0);
}

// template <int Dim>
// Point<Dim> KDTree<Dim>::nearestNeighbor_(const Point<Dim>& query, int left, int right, int dim) const
// { 
//   Point<Dim> nearest;
//   int middle = (left + right) /2;
//   int nextDim = (dim + 1) % Dim;
//   if (left > right) {
//     return points[middle];
//   }
//   if (smallerDimVal(query, points[middle], dim))
//   {
//     // less than true, go left
//     nearest = nearestNeighbor_(query, left, middle-1, nextDim);
//   }else
//   {
//     nearest = nearestNeighbor_(query, middle+1, right, nextDim);
//   }


//   if (shouldReplace(query, nearest, points[middle]))
//   {
//     nearest = points[middle];
//   }

//   // radius between query and nearest
//   double bestDist = 0;
//   for (int i = 0; i < Dim; i++)
//   {
//     bestDist += (query[i] - nearest[i])*(query[i] - nearest[i]);
//   }
  
//   // split distance
//   double splitDist = (query[dim] - points[middle][dim])*(query[dim] - points[middle][dim]);

//   if (splitDist <= bestDist)
//   {
//     Point<Dim> anotherBest;
//     if (smallerDimVal(query, points[middle], dim)) {
//       // go to another side, in this case, it should be go right
//       anotherBest = nearestNeighbor_(query, middle + 1, right, nextDim);
//     } else {
//       // go left
//       anotherBest = nearestNeighbor_(query, left, middle - 1, nextDim);
//     }
//     if (shouldReplace(query, nearest, anotherBest)) {
//       nearest = anotherBest;
//     }
//   }
//   return nearest;
// } 

template <int Dim>
Point<Dim> KDTree<Dim>::nearestNeighbor_(const Point<Dim>& query, typename KDTree<Dim>::KDTreeNode* curNode, int curDim) const
{ 
  // leaf check
  if (curNode->left == NULL && curNode->right == NULL)
  {
    return curNode->point;
  }
  int nextDim = (curDim + 1) % Dim;
  Point<Dim> nearest = curNode->point;
  Point<Dim> potentialNearest = nearest;

  bool recurseLeft = (smallerDimVal(query, nearest, curDim));
  if (smallerDimVal(query, nearest, curDim))
  {
    if (curNode->left != NULL)
    {
      // less than true, go left
      potentialNearest = nearestNeighbor_(query, curNode->left, nextDim);
    }
  }
  else 
  {
    if ((curNode->right != NULL))
    {
      potentialNearest = nearestNeighbor_(query, curNode->right, nextDim);
    }
    
  }

  if (shouldReplace(query, nearest, potentialNearest))
  {
    nearest = potentialNearest;
  }
  
  // radius between query and nearest
  double bestDist = 0.0;
  for (int i = 0; i < Dim; i++)
  {
    bestDist += (query[i] - nearest[i])*(query[i] - nearest[i]);
  }
  
  // split distance
  double splitDist = (query[curDim] - curNode->point[curDim])*(query[curDim] - curNode->point[curDim]);

  if (splitDist <= bestDist)
  {
    if (recurseLeft)
    {
      if (curNode->right != NULL)
      {
        // go right
        potentialNearest = nearestNeighbor_(query, curNode->right, nextDim);
      }
      
      if (shouldReplace(query, nearest, potentialNearest))
      {
        nearest = potentialNearest;
      }
    }
    else{ 
      if (curNode->left != NULL)
    {
      // go left
      potentialNearest = nearestNeighbor_(query, curNode->left, nextDim);
      if (shouldReplace(query, nearest, potentialNearest))
      {
        nearest = potentialNearest;
      }
    }
    }
  }
  return nearest;
}