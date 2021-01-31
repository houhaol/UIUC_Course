#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  tra_ = NULL;
  reachEnd = false;
}

ImageTraversal::Iterator::Iterator(PNG inputPng, Point inputStart, double inputTolerance, ImageTraversal * inputTraversal)
{
  png_ = inputPng;
  start_ = inputStart;
  initialStart_ = start_;
  tolerance_ = inputTolerance;
  tra_ = inputTraversal;
  reachEnd = false;

  // store all pts as false (not visited)
  for (unsigned i = 0; i < (png_.width() * png_.height()); i++)
  {
    visited_.push_back(false);
  }

  reachEnd = false;
  if (canVisit(start_))
  {
    visited_[start_.x + start_.y * png_.width()] = true;
  }
}

bool ImageTraversal::Iterator::canVisit(Point inputPoint)
{
  if (inputPoint.x >= png_.width() || inputPoint.y >= png_.height())
  {
    return false;
  }
  
  HSLAPixel initialPixel = png_.getPixel(initialStart_.x, initialStart_.y);
  HSLAPixel inputPixel = png_.getPixel(inputPoint.x, inputPoint.y);

  if (calculateDelta(initialPixel, inputPixel) < tolerance_)
  {
    // return true;
    if (!(visited_[inputPoint.x + inputPoint.y * png_.width()]))
    {
      return true;
    }
  }
  return false;
  
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point right = Point(start_.x + 1, start_.y);
  Point below = Point(start_.x, start_.y + 1);
  Point left = Point(start_.x - 1, start_.y);
  Point above = Point(start_.x, start_.y - 1);
  
  if (canVisit(right))
  {
    tra_->add(right);
  }
  if (canVisit(below))
  {
    tra_->add(below);
  }
  if (canVisit(left))
  {
    tra_->add(left);
  }
  if (canVisit(above))
  {
    tra_->add(above);
  }
  
  if (tra_->empty())
  {
    reachEnd = true;
    return *this;
  }

  Point nextPoint = tra_->pop();
  // True: alr access before so move next
  while (visited_[nextPoint.x + nextPoint.y * png_.width()])
  {
    if (tra_->empty())
    {
      reachEnd = true;
      return *this;
    }
    nextPoint = tra_->pop();
  }
  // has not accessed, store visited value
  start_ = nextPoint;
  visited_[start_.x + start_.y * png_.width()] = true;
  return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return start_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  return (reachEnd != other.reachEnd);
}

