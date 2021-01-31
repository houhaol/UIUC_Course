/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  vector<Vertex> vertexes = g_.getVertices();
  vector<Edge> edges = g_.getEdges();
  
  // for (unsigned int i = 0; i < vertexes.size(); i++)
  // {
  //   residual_.insertVertex(vertexes[i]);
  //   flow_.insertVertex(vertexes[i]);
  // }
  for (Vertex &v : vertexes)
  {
    residual_.insertVertex(v);
    flow_.insertVertex(v);
  }
  for (Edge & e: edges)
  {
    Vertex src = e.source;
    Vertex des = e.dest;

    residual_.insertEdge(src, des);
    residual_.insertEdge(des, src);
    flow_.insertEdge(src, des);

    // asign weights
    residual_.setEdgeWeight(src, des, e.getWeight());
    residual_.setEdgeWeight(des, src, 0);

    flow_.setEdgeWeight(src, des, 0);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int cap = std::numeric_limits<int>::max();
  for (int i = 0; i < int(path.size()) - 1; i++)
  {
    Vertex src = path[i];
    Vertex des = path[i+1];

    if (residual_.getEdgeWeight(src, des) < cap)
    {
      cap = residual_.getEdgeWeight(src, des);
    }
  }
  return cap;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector <Vertex> path;
  maxFlow_ = 0;
  while (findAugmentingPath(source_, sink_, path))
  {
    int cap = pathCapacity(path);
    maxFlow_ += cap;
    for (unsigned i = 0; i < path.size() - 1; i++)
    {
      Vertex src = path[i];
      Vertex des = path[i+1];

      //update flow
      if (flow_.edgeExists(src, des))
      {
        flow_.setEdgeWeight(src, des, flow_.getEdgeWeight(src, des) +cap);
      }
      else
      {
        flow_.setEdgeWeight(des, src, flow_.getEdgeWeight(des, src) -cap);
      }
      
      // update residual
      residual_.setEdgeWeight(src, des, residual_.getEdgeWeight(src, des) - cap);
      residual_.setEdgeWeight(des, src, residual_.getEdgeWeight(des, src) + cap);
      
    }
    
  }
  
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

