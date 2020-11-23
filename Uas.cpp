#include "Uas.h"

//constructor
Uas::Uas(unsigned int AssignedId) {
	//Initiate the UAS at a random location at the periphery of the world displayed in the GUI
	// -------- 0 -XRANGE--
	// |                  | 
	// |                  |  YRANGE
	// 3        +(origin) 1
	// |                  |
	// |                  |
	// -------- 2 ---------	 
	int boundaryLine = rand() % 4;
	int sign = rand() % 2;
	
	double randX = (double) (rand() % X_RANGE);
	double randY = (double) (rand() % Y_RANGE);
	double randVX = (double) (VX_MIN + rand() % (VX_MAX - VX_MIN));
	double randVY = (double) (VY_MIN + rand() % (VY_MAX - VY_MIN));
	
	Position.z = (double)Z_CONST;
	Velocity.z = (double)VZ_CONST;
	Valid = true;
	Id = AssignedId;
	CurrentReceivedMessage = "";
	CurrentBroadcastMessage = "";
	CourseReversed=false;
		
	if( boundaryLine == 0 )
	{
		 if(sign == 0)
		 {
		 	Position.x = (double)randX;
		 	Velocity.x = - (double)randVX;
		 }
		 else
		 {
		 	Position.x = - (double)randX;	
		 	Velocity.x = (double)randVX;		 		 	
		 }
		 Position.y = (double)Y_RANGE;
		 Velocity.y = - (double)randVY;
	}
	if( boundaryLine == 1 )
	{
		 if(sign == 0)
		 {
		 	Position.y = (double)randY;
		 	Velocity.y = - (double)randVY;
		 }
		 else
		 {
		 	Position.y = - (double)randY;	
		 	Velocity.y = (double)randVY;		 		 	
		 }
		 Position.x = (double)X_RANGE;
		 Velocity.x = - (double)randVX;
	}
	if( boundaryLine == 2 )
	{
		 if(sign == 0)
		 {
		 	Position.x = (double)randX;
		 	Velocity.x = - (double)randVX;
		 }
		 else
		 {
		 	Position.x = - (double)randX;	
		 	Velocity.x = (double)randVX;		 		 	
		 }
		 Position.y = -(double)Y_RANGE;
		 Velocity.y = (double)randVY;
	}
	if( boundaryLine == 3 )
	{
		 if(sign == 0)
		 {
		 	Position.y = (double)randY;
		 	Velocity.y = - (double)randVY;
		 }
		 else
		 {
		 	Position.y = - (double)randY;	
		 	Velocity.y = (double)randVY;		 		 	
		 }
		 Position.x = - (double)X_RANGE;
		 Velocity.x = (double)randVX;
	}
	
	int compliant = rand() % 2;
	if(compliant == 0)
	{
		Compliant=false;
	}
	else
	{
		Compliant=true;		
	}
	
	int purposeful = rand() % 2;
	if(purposeful == 0)
	{
		Purposeful=false;
	}
	else
	{
		Purposeful=true;		
	}
	
	std::cout << "Constructed UAS instance: " <<  Id  << std::endl;
}

//destructor
Uas::~Uas() {
	std::cout << "Destructed UAS instance: " <<  Id  << std::endl;
}

ThreeDVector Uas::getPosition() {
	return Position;
}

ThreeDVector Uas::getVelocity() {
	return Velocity;
}

unsigned int Uas::getId() {
	return Id;
}

void Uas::updatePosition() {
	// compute position of UAV after 1 second of time
	// if UAV hits one of the boundaries set it will be invalid
	// take action based on received message
	// capture or destruction would also set it invalid
	Position.x = Position.x + Velocity.x;
	Position.y = Position.y + Velocity.y;
	Position.z = Position.z + Velocity.z;
	
	//std::cout << "received message: " << CurrentReceivedMessage <<  " Compliant: " << Compliant << std::endl;
		
	if( (Position.x >= (double) X_RANGE) || (Position.x <= - (double) X_RANGE) || (Position.y >= (double) Y_RANGE) || (Position.y <= - (double) Y_RANGE) )
	{
		Valid = false;
		return;
	}
	if (CurrentReceivedMessage == "warning_only")
	{
		CurrentReceivedMessage = "";
		CurrentBroadcastMessage = "received message: warning_only status: continuing course";
	}
	if (CurrentReceivedMessage == "return_to_base")
	{
		CurrentReceivedMessage = "";
		if( Compliant == true && CourseReversed == false)
		{
			CurrentBroadcastMessage = "received message: return_to_base status: reversing course";
			Velocity.x = - Velocity.x;
			Velocity.y = - Velocity.y;
			CourseReversed = true;
		}
	}
	if (CurrentReceivedMessage == "capture")
	{
		CurrentReceivedMessage = "";
		CurrentBroadcastMessage = "status: captured";
		Valid = false;
	}
	if (CurrentReceivedMessage == "destroy")
	{
		CurrentReceivedMessage = "";
		CurrentBroadcastMessage = "status: destroyed";
		Valid = false;
	}
	return;
}

bool Uas::isValid() {
	return Valid;
}

bool Uas::isCompliant() {
	return Compliant;
}

bool Uas::isPurposeful() {
	return Purposeful;
}

void Uas::setValid(bool validity) {
	Valid = validity;
}
		
void Uas::sendMessage(std::string Message) {
	CurrentReceivedMessage = Message;
}

std::string Uas::getMessage() {
	return CurrentBroadcastMessage;
}
