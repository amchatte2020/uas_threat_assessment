#include<math.h>
#include "Sensor.h"

//constructor
Sensor::Sensor(unsigned int AssignedId, ThreeDVector Loc) {
	Id = AssignedId;
	Location = Loc;
	SensorRadius = (double) PROXIMITY_SENSOR_RADIUS;
}

bool Sensor::isSensed(ThreeDVector UasLocation) {
	double distance = sqrt ( pow((Location.x - UasLocation.x), 2.0) + pow((Location.y - UasLocation.y), 2.0) + pow((Location.z - UasLocation.z), 2.0) );
	//std::cout << " Sensor Id: " << Id << " Distance " << distance << std::endl;
	if (distance <= SensorRadius )
	{
		return true;
	}
	else
	{
		return false;
	}
}
