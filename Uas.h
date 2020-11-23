#ifndef UAS_H
#define UAS_H

#include <iostream>
#include <string>
#include "common.h"


class Uas {
	private:
		ThreeDVector Position;
		ThreeDVector Velocity;
		unsigned int Id;
		bool Valid;
		bool Compliant;
		bool Purposeful;
		bool CourseReversed;
		std::string CurrentReceivedMessage;
		std::string CurrentBroadcastMessage;		
	public:
		Uas(unsigned int AssignedId);
		~Uas();
		ThreeDVector getPosition();
		ThreeDVector getVelocity();
		unsigned int getId();
		bool isValid();
		bool isCompliant();
		bool isPurposeful(); 
		void setValid(bool validity);
		void updatePosition();
		void sendMessage(std::string Message);
		std::string getMessage();
};

#endif
