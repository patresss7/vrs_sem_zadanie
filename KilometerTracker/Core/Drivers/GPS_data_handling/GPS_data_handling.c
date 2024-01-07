/*
 * GPS_data_handling.c
 *
 *  Created on: Jan 5, 2024
 *      Author: matej
 */

#include <stdio.h>
#include <math.h>
#include "GPS_data_handling.h"

#define EARTH_RADIUS 6371000 // Radius of the Earth in meters

// Function to convert degrees/minutes format to decimal degrees
float convertToDecimalDegrees(float degrees, float minutes) {
    return degrees + (minutes / 60.0);
}

// Function to convert GPS coordinates to decimal degrees
struct Coordinate convertToDecimal(struct Coordinate coord) {
    struct Coordinate decimalCoord;
    decimalCoord.latitude = convertToDecimalDegrees(floor(coord.latitude / 100), fmod(coord.latitude, 100));
    decimalCoord.longitude = convertToDecimalDegrees(floor(coord.longitude / 100), fmod(coord.longitude, 100));
    return decimalCoord;
}

// Function to convert degrees to radians
double toRadians(double degree) {
    return degree * (M_PI / 180.0);
}

// Function to compute the Haversine distance between two coordinates
double haversineDistance(struct Coordinate coord1, struct Coordinate coord2) {
    // Convert latitude and longitude from degrees to radians
    double lat1 = toRadians(coord1.latitude);
    double lon1 = toRadians(coord1.longitude);
    double lat2 = toRadians(coord2.latitude);
    double lon2 = toRadians(coord2.longitude);

    // Compute differences in coordinates
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Distance in meters
    double distance = EARTH_RADIUS * c;

    return distance;
}
