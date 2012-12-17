#include "algorithm.h"

/*
 * This calculates the factor of safety at 30 different points and three different radii
 * Specifically the points are alligned such that there are 10 in each row at heights 1.1, 1.3 and 1.5 times the height of the slope
 * The radius is set as the distance from the point to the toe multipled by 1.1
 * These are chosen more or less arbitrary because guidence is not easy to find
 * Then at each point the program calculates the FS using the same procedure as example 10.2 in the text
 */

Algorithm::Algorithm()
{
}

// Some basic constants so we don't have to keep calling the sin/cos functions
const double PI = 4.0*atan(1.0);
const double PI_2 = 8.0*atan(1.0);
const double PI_180 = PI/180;

// Helper functions
inline double square(double x)
{
    return x*x;
}

inline double dist(double x1, double y1, double x2, double y2)
{
    return sqrt(square(x1-x2)+square(y1-y2));
}

inline double abs(double x)
{
    return x < 0 ? -x : x;
}

void Algorithm::calculate()
{
    // We need to set the width of each layer
    for(int l = 0; l < numOfLayers; l++)
    {
        layers[l]->width = -1; // This means the layer goes on forever
        for(int i = 0; i < numOfLayers; i++)
        {
            if(l == i) continue;
            if(layers[l]->depth < layers[i]->depth)
            {
                if(layers[l]->width < 0 || layers[l]->depth + layers[l]->width > layers[i]->depth)
                    layers[l]->width = layers[i]->depth - layers[l]->depth;
            }
        }
    }

    results = new double*[30]; // Thirty different rows of results

    for(int i = 0; i < 3; i++)
    {
        double point_y = height * (i == 0 ? 1.5 : i == 1.5 ? 2.0 : 2.5);
        for(int j = 0; j < 10; j++)
        {
            double point_x = height * slope * (j+1) / 11;

            double radius = sqrt(point_x*point_x + point_y*point_y) * 1.1; // calculate the radius, assume the toe is at 0, 0

            // This might get a little ugly but this will calculate the area and center of gravity for each layer
            double *areas = new double[numOfLayers];
            double *cy = new double[numOfLayers];
            double *cx = new double[numOfLayers];
            double max_depth = 0.0;
            double max_x = 0.0;
            double min_x = 0.0;
            // We are essentially doing a ray cast
            bool hasStarted = false, hasLeft = false;
            for(double r = PI; r < PI_2; r += PI_180)
            {
                double x = point_x - radius * cos(r);
                double y = point_y + radius * sin(r);
                if(y > height)
                {
                    continue; // we know this will not intersect
                }

                if(x < 0 && y > 0)
                {
                    if(!hasStarted)
                    {
                        hasStarted = true;
                        min_x = x;
                    }
                }

                if(y > max_depth) max_depth = y;    // We need to know the max depth the cg

                // We need the ray in x = my + b form so that we can determine where the intersections are
                double r_slope = (point_x-x)/(point_y-y);
                double r_b = x - r_slope*y;

                // we split the slope into three areas: before, middle and after
                if(x < 0)   // The radius before the slope
                {
                    if(y > 0) continue; // we still do not interact

                    for(int l = 0; l < numOfLayers; l++)
                    {
                        double start_y = height - layers[l]->depth;
                        double end_y = height - layers[l]->depth - layers[l]->width;
                        if(start_y > y && (end_y < 0 || layers[l]->width < 0))
                        {
                            areas[l] += dist(end_y < y ? end_y*r_slope+r_b : x, end_y < y ? end_y : y, start_y > 0 ? r_b : start_y*r_slope+r_b, start_y > 0 ? 0 : start_y);
                        }
                    }
                }
                else if(x > height * slope) // The radius is after the slope
                {
                    if(!hasLeft)
                    {
                        hasLeft = true;
                        max_x = x;
                    }

                    for(int l = 0; l < numOfLayers; l++)
                    {
                        double start_y = height - layers[l]->depth;
                        double end_y = height - layers[l]->depth - layers[l]->width;
                        if(start_y > y && (end_y < height || layers[l]->width < 0))
                        {
                            areas[l] += dist(end_y < y ? end_y*r_slope+r_b : x, end_y < y ? end_y : y, start_y > height ? r_b : start_y*r_slope+r_b, start_y > height ? height : start_y);
                        }
                    }
                }
                else // this should be the transition
                {
                    if(!hasLeft)
                    {
                        hasLeft = true;
                        max_x = x;
                    }

                    for(int l = 0; l < numOfLayers; l++)
                    {
                        double start_y = height - layers[l]->depth;
                        double end_y = height - layers[l]->depth - layers[l]->width;
                        double slope_x = r_b/(slope-r_slope);
                        double slope_y = slope_x/slope;
                        if(start_y > y && (end_y < slope_y || layers[l]->width < 0))
                        {
                            areas[l] += dist(end_y < y ? end_y*r_slope+r_b : x, end_y < y ? end_y : y, start_y > slope_y ? slope_x : start_y*r_slope+r_b, start_y > slope_y ? slope_y : start_y);
                        }
                    }
                }
            }

            // Now that we know the area, we need to know the cg's
            // This is a gross approximation but I am not sure what a better way would be
            for(int l = 0; l < numOfLayers; l++)
            {
                cy[l] = layers[l]->width < 0 ? height - layers[l]->depth - (layers[l]->depth - max_depth) / 2 : height - layers[l]->depth - (layers[l]->width / 2);
                if(layers[l]->depth + (layers[l]->width < 0 ? height : layers[l]->width) >= height) cx[l] = (max_x - min_x) / 2;
                else cx[l] = (max_x - slope * (height - layers[l]->depth - layers[l]->width)) / 2;
            }

            // Now we calculate the results
            int z = i * 10 + j;
            results[z] = new double[6];
            results[z][0] = point_x;
            results[z][1] = point_y;
            results[z][2] = radius;
            results[z][3] = 0;
            results[z][4] = 0;
            for(int l = 0; l < numOfLayers; l++)
            {
                printf("%lf, %lf, %lf\n", cx[l], max_x, min_x);
                results[z][3] += (areas[l]*layers[l]->weight*(1-kv))*abs(point_x-cx[l])+kh*areas[l]*layers[l]->weight*(point_y-cy[l]);
                results[z][4] += layers[l]->c*cx[l]*2*radius +
                        ((areas[l]*layers[l]->weight*(1-kv))*abs(point_x-cx[l])-kh*areas[l]*layers[l]->weight*(point_y-cy[l]))*tan(layers[l]->friction);
            }
            results[z][5] = results[z][4]/results[z][3];
        }
    }
}

void Algorithm::dump()
{
    printf("Height of Slope: %lf\n", height);
    printf("Slope of Embankment: %lf\n", slope);
    printf("Kv: %lf\n", kv);
    printf("Kh: %lf\n", kh);
    printf("Number of Soil Layers: %d\n", numOfLayers);
    for(int i = 0; i < numOfLayers; i++)
    {
        printf("\t%d: depth = %lf, weight = %lf, c = %lf, friction = %lf\n", i, layers[i]->depth, layers[i]->weight, layers[i]->c, layers[i]->friction);
    }
}
