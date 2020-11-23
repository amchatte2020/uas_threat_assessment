#include "common.h"
#include "Simulator.h"

int main()
{
	Simulator s;
	for (int i=0; i<SIMULATED_TIME_DURATION; i++)
	{
		s.simulateUnitTime();
	}
	
	return 0;
}
