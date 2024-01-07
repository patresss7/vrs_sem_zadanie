/*
 * GPS_data_handling.h
 *
 *  Created on: Jan 5, 2024
 *      Author: matej
 */

#ifndef DRIVERS_GPS_DATA_HANDLING_GPS_DATA_HANDLING_H_
#define DRIVERS_GPS_DATA_HANDLING_GPS_DATA_HANDLING_H_

struct Coordinate {
    float latitude;
    float longitude;
};

double haversineDistance(struct Coordinate coord1, struct Coordinate coord2);

#endif /* DRIVERS_GPS_DATA_HANDLING_GPS_DATA_HANDLING_H_ */
