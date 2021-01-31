#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  myBase = new PNG(png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ImageTraversal * tra = & traversal; // point to the address
  ColorPicker * color = & colorPicker;
  traverseVec.push_back(tra);
  colorVec.push_back(color);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  animation.addFrame(*myBase); // add first image frame
  for (unsigned i = 0; i < traverseVec.size(); i++)
  {
    ImageTraversal::Iterator begin = traverseVec[i]->begin();
    ImageTraversal::Iterator end = traverseVec[i]->end();
    unsigned frameNum = 0;
    for (ImageTraversal::Iterator it = begin; it != end; ++it)
    {
      if (frameNum == frameInterval)
      {
        animation.addFrame(*myBase); // final frame
        frameNum = 0;
      }
      // visiting pixels
      HSLAPixel & original = myBase->getPixel((*it).x, (*it).y); // reference variable here. If not use &, original is copy of mybase->getpixel. So what you have done is bascially change original, not the mybase pixel. If use &, alias to mybase->getpixel, then values of mybase->getpixel would be changed.
      HSLAPixel updatePixel = colorVec[i]->getColor((*it).x, (*it).y);

      original.h = updatePixel.h;
      original.s = updatePixel.s;
      original.l = updatePixel.l;
      original.a = updatePixel.a;
      frameNum += 1;
    }
    animation.addFrame(*myBase);
  }
  return animation;
}
