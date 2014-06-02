#include <Arduino.h>

// The distance meter class
class CDistanceMeter{
	const int TriggerPin;
	const int EchoPin;
private:
	// forbid copy
	CDistanceMeter(const CDistanceMeter &);
public:
	// the constructor to initialize the distance meter
	CDistanceMeter(int triggerPin, int echoPin);
	// get duration, which is a time in microseconds
	unsigned long getDuration();
	// get distance
	// acoustic velocity is 343 m/s , take only the way back
	double getDistance() {
		return getDuration()*(343.0 / 2.0 / 1e+6);
	}
};

unsigned long CDistanceMeter::getDuration()
{
	//TODO: take more than one measuring point and build the mean value

	// trigger measurement
	digitalWrite(TriggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TriggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TriggerPin, LOW);
	// measurement
	return pulseIn(EchoPin, HIGH);
}

CDistanceMeter::CDistanceMeter(int triggerPin, int echoPin) : TriggerPin(triggerPin) , EchoPin(echoPin)
{
	// configure button pins
	pinMode(TriggerPin , OUTPUT);
	pinMode(EchoPin , INPUT);
}

void initialization()
{
	// general initialization
	init();
	//FORTESTING:
	Serial.begin(9600);
}

int main(void)
{
	const int TriggerPin = 12;
	const int EchoPin = 13;

	initialization();
	CDistanceMeter distanceMeter(TriggerPin, EchoPin);

	while (true)
	{
		//FORTESTING:
		Serial.println(distanceMeter.getDistance());
		delay(500);
	}
	return 0; // never reached
}
