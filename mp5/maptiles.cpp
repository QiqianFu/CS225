/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <stdio.h>
using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    map<Point<3>,int> the_map;
    vector<Point<3>> newPoints;
    int count=0;
    MosaicCanvas* the_canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    for(unsigned int i = 0 ; i< theTiles.size();i++){
        HSLAPixel avercolor = theTiles[i].getAverageColor();
        Point<3> averpoint = convertToLAB(avercolor);
        newPoints.push_back(averpoint);
        the_map.insert(pair<Point<3>,int>(averpoint,count));
        count++;
    }
    KDTree<3> mytree(newPoints);
    for(int i = 0 ; i< theSource.getRows();i++){
        for(int j = 0; j< theSource.getColumns(); j++){
            TileImage* the_image = get_match_at_idx(mytree,the_map,theTiles,theSource,i,j);
            the_canvas->setTile(i,j,the_image);
        }
    }
    return the_canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
