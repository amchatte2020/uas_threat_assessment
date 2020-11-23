#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include "common.h"
#include "Uas.h"
#include "Sensor.h"

class Simulator {
	private:
		Uas *UasArray[MAX_SIMULATED_UAS];
		unsigned int LoiterCounter[MAX_SIMULATED_UAS];
		unsigned int Entry[MAX_SIMULATED_UAS];
		unsigned int Transit[MAX_SIMULATED_UAS];
		unsigned int Loiter[MAX_SIMULATED_UAS];
		unsigned int Attack[MAX_SIMULATED_UAS];
		
		Sensor *SensorArray[MAX_SENSORS]; 
		unsigned int UasId;
		bool   SystemActive;
		float  EntryKnobValue;
		float  TransitKnobValue;
		float  LoiterKnobValue;
		float  AttackKnobValue;
		
		unsigned int TimeStep;
			
	public:
		Simulator();
		void simulateUnitTime();
		void getGuiInput(bool& active, float& e, float& t, float& l, float& a);
		void setGuiOutput();
};

#endif
