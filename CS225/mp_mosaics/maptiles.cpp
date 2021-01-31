/*
 * @Author: Houhao
 * @Date: 2020-08-25 19:08:29
 * @LastEditors: Houhao
 * @LastEditTime: 2020-10-30 18:34:32
 * @FilePath: \cs225git\mp_mosaics\maptiles.cpp
 */
/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    std::vector<Point<3>> points_;
    map<Point<3>, TileImage*> tiles_;

    // tiles map and points
    for (unsigned i = 0; i < theTiles.size(); i++)
    {
        LUVAPixel pixel = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(pixel);
        points_.push_back(point);
        tiles_[point] = &theTiles[i];
    }
    
    // kdtree based on points_
    KDTree<3> * kdtree = new KDTree<3> (points_);

    // search process
    for (int i = 0; i < theSource.getRows(); i++)
    {
        for (int j = 0; j < theSource.getColumns(); j++)
        {
            LUVAPixel sourcePixel = theSource.getRegionColor(i,j);
            Point<3> sourcePoint = convertToXYZ(sourcePixel);
            Point<3> outPoint = kdtree->findNearestNeighbor(sourcePoint);
            TileImage * outTileImg = tiles_[outPoint];
            output->setTile(i, j, outTileImg);
        }
        
    }
    return output;
}

