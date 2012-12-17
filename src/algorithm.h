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
