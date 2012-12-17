/*
    algorithm.h - (c) Michael Weber, Jr. (2012)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <math.h>

struct SoilLayer
{
    double depth;       // Depth to the soil layer. It is assummed that each layer is infinitly deep unless there is a layer below it
    double c;           // Cohesion of the soil
    double friction;    // Friction angle in rad
    double weight;      // Unit Weight of Soil

    // These values are calculated
    double width;       // Width of the soil layer
};

class Algorithm
{
public:
    Algorithm();

    double height;          // Height of the slope
    double slope;           // This is the horizontal value of the slope of the form slope/1 such that height*slope = width of slope
    double kv;              // Verticle loading of the soil
    double kh;              // Horizontal loading of the soil
    int numOfLayers;        // The number of soil layers
    SoilLayer **layers;     // Pointer to the soil layer data

    void calculate();       // Runs the calculations

    double ** results;      // Where all the results are dumped

    void dump();            // Debug function to check for the correct functionality
};

#endif // ALGORITHM_H
