#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>
#include "common.h"


class Sensor {
	private:
		ThreeDVector Location;
		unsigned int Id;
		double SensorRadius;		
	public:
		Sensor(unsigned int AssignedId, ThreeDVector Loc);
		bool isSensed(ThreeDVector UasLocation);
};

#endif
