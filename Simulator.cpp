#include <iostream>
#include "common.h"
#include "Simulator.h"

//constructor
Simulator::Simulator() {
	UasId = 0;
	ThreeDVector t;
	
	//Instantiate the array of 5 sensors
	
	//Sensor A
	t.x = (double)0;
	t.y = (double)0;
	t.z = (double)Z_CONST;
	SensorArray[0] = new Sensor(0,t);

	//Sensor B	
	t.x = (double)PROXIMITY_SENSOR_RADIUS;
	t.y = (double)0;
	t.z = (double)Z_CONST;
	SensorArray[1] = new Sensor(1,t);

	//Sensor C	
	t.x = (double)0;
	t.y = - (double)PROXIMITY_SENSOR_RADIUS;
	t.z = (double)Z_CONST;
	SensorArray[2] = new Sensor(2,t);
	
	//Sensor D	
	t.x = - (double)PROXIMITY_SENSOR_RADIUS;
	t.y = (double)0;
	t.z = (double)Z_CONST;
	SensorArray[3] = new Sensor(3,t);

	//Sensor E	
	t.x = (double)0;
	t.y = (double)PROXIMITY_SENSOR_RADIUS;
	t.z = (double)Z_CONST;
	SensorArray[4] = new Sensor(4,t);
	
	//Instantiate the UASs
	
	for(UasId=0; UasId < MAX_SIMULATED_UAS; UasId++)
	{
		UasArray[UasId] = new Uas(UasId);
		LoiterCounter[UasId] = 0;
		Entry[UasId] = 0;
		Transit[UasId] = 0;
		Loiter[UasId] = 0;	
		Attack[UasId] = 0;	
	}
	
	TimeStep = 0;
	SystemActive = true;
}

void Simulator::simulateUnitTime() { 
	
	bool A = false;
	bool B = false;
	bool C = false;
	bool D = false;
	bool E = false;
	
	float WeightedEntryValue=0.0;
	float WeightedTransitValue=0.0;
	float WeightedLoiterValue=0.0;
	float WeightedAttackValue=0.0;
	
	std::string message;
	
	//get the system on/off status and knob values from GUI
	getGuiInput(SystemActive, EntryKnobValue, TransitKnobValue, LoiterKnobValue, AttackKnobValue);	
	                                                                                                              
	for(int i=0; i < MAX_SIMULATED_UAS; i++)
	{
		A=SensorArray[0]->isSensed( UasArray[i]->getPosition() );
		B=SensorArray[1]->isSensed( UasArray[i]->getPosition() );
		C=SensorArray[2]->isSensed( UasArray[i]->getPosition() );
		D=SensorArray[3]->isSensed( UasArray[i]->getPosition() );
		E=SensorArray[4]->isSensed( UasArray[i]->getPosition() );
		
		//std::cout << "Time step: " << TimeStep << " Det A: " << A << " Det B: " << B <<  " Det C: " << C <<  " Det D: " << D <<  " Det E: " << E << std::endl;

		//condition for entry satisfied
		if(A || B || C || D || E)
		{
			Entry[i] = 1;
		}
		
		//condition for transit satisfied
		if(B || C || D || E || (B && C) || (B && E) || (D && E) || (D && C))
		{
			Transit[i] = 1;
			LoiterCounter[i]++;
			
			//condition for transit satisified along with time threshold of loiter
			if( LoiterCounter[i] > LOITER_TIME_THRESHOLD)
			{
				Loiter[i]=1;
			}
		}
		
		//condition for attack satisfied
		if( (B && C && A) || (C && D && A) || (D && E && A) || (D && B && A) || (B && A) || (C && A) || (D && A) || (E && A) )
		{
			Attack[i]=1;
		}
			
		//get the weighted values
		WeightedEntryValue = EntryKnobValue * (float) Entry[i] ;
		WeightedTransitValue = TransitKnobValue * (float) Transit[i] ;
		WeightedLoiterValue = LoiterKnobValue * (float) Loiter[i] ;
		WeightedAttackValue = AttackKnobValue * (float) Attack[i] ;
		
		//std::cout << "Time step: " << TimeStep 
		//<< " WeightedEntryValue " << WeightedEntryValue 
		//<< " WeightedTransitValue " << WeightedTransitValue
		//<< " WeightedLoiterValue " << WeightedLoiterValue 
		//<< " WeightedAttackValue " << WeightedAttackValue 
		//<< std::endl;		
		
		
		//Find the largest weighted value and use that for the action determination
		float largestWeightedValue=0.0;
		if( largestWeightedValue < WeightedEntryValue)
		{
			largestWeightedValue = WeightedEntryValue;
		}
		if( largestWeightedValue < WeightedTransitValue)
		{
			largestWeightedValue = WeightedTransitValue;
		}
		if( largestWeightedValue < WeightedLoiterValue)
		{
			largestWeightedValue = WeightedLoiterValue;
		}
		if( largestWeightedValue < WeightedAttackValue)
		{
			largestWeightedValue = WeightedAttackValue;
		}
		
		//set action in increasing order of largest weighted value
		if (largestWeightedValue > (float) WARNING_THRESHOLD)
		{
			message="warning_only";
		}
		if (largestWeightedValue > (float) RETURN_THRESHOLD)
		{
			message="return_to_base";
		}
		if (largestWeightedValue > (float) CAPTURE_THRESHOLD)
		{
			message="capture";
		}
		if (largestWeightedValue > (float) DESTROY_THRESHOLD)
		{
			message="destroy";
		}
		
		if(SystemActive == true)
		{
			//std::cout << "message to be sent: " << message << std::endl;
			UasArray[i]->sendMessage(message);
		}
		UasArray[i]->updatePosition();		
	}
	
	//display simulator state in GUI
	setGuiOutput();
	
	for(int i=0; i < MAX_SIMULATED_UAS; i++)
	{
		if(UasArray[i]->isValid() == false)
		{
			//if a UAS has become invalid in board state delete it and create a new one
			delete UasArray[i];
			UasArray[i] = new Uas(UasId);
			LoiterCounter[i] = 0;
			Entry[i] = 0;
			Transit[i] = 0;
			Loiter[i] = 0;	
			Attack[i] = 0;
			UasId++;
		}
	}
	
	TimeStep++;
}

void Simulator::getGuiInput(bool& active, float& e, float& t, float& l, float& a) {
	//this function must be handled by the GUI
	//filling in constant data for now
	active = true;
	e = 0.2;
	t = 0.5;
	l = 0.5;
	a = 1.0;
}

void Simulator::setGuiOutput()
{
	//this function must be handled by the GUI
	//printing some data that should be represented graphically in the completed project
	for(int i=0; i < MAX_SIMULATED_UAS; i++)
	{
		std::cout << "Time step: " << TimeStep 
			<< " Uas ID " << UasArray[i]->getId() 
			<< " X : " <<  (UasArray[i]->getPosition()).x 
			<< " Y : " <<  (UasArray[i]->getPosition()).y
			<< " Z : " <<  (UasArray[i]->getPosition()).z
			<< " status message: " << UasArray[i]->getMessage() << std::endl;
	}
}
