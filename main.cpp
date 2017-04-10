#include <iostream>  //Grund-Funktionen
#include <math.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include <softPwm.h>
#include <joystick.hh> //Klassen zur Verarbeitung von Sensordaten
//#include <Rotationssensor.h>
#include <libSonar.h>
#include <InterfaceI2C.h> // Schnittstelle
#include <Lenkung.h> //Generelle Steuerung
#include <engine.h> // Klasse um Daten an Motoren weiter zu geben

// Erstellen einzelen Objekte aus den Klassen

//Schnittstellen
Schnittstelle pin;

//Joystick
Joystick joystick;

//Ultraschallsensoren
Sonar rvUltraschallsensor1;
Sonar rvUltraschallsensor2;
Sonar rvUltraschallsensor3;
Sonar lvUltraschallsensor1;
Sonar lvUltraschallsensor2;
Sonar lvUltraschallsensor3;

Sonar rhUltraschallsensor1;
Sonar rhUltraschallsensor2;
Sonar rhUltraschallsensor3;
Sonar lhUltraschallsensor1;
Sonar lhUltraschallsensor2;
Sonar lhUltraschallsensor3;

//Motoren
engine MotorA;
engine MotorB;
engine MotorC;
engine MotorD;
engine MotorCDriveA;
engine MotorCDriveB;
engine MotorCDriveC;
engine MotorCDriveD;

//Lenkung
Lenkung LenkungCDrive;


void SetUp()
{
	wiringPiSetup();

	//SetUp-Funktionen der Klassen aufrufen

	//Schnittstelle
	pin.InterfaceSetUp();

	//Ultraschallsensoren
	rvUltraschallsensor1.init(pin.get_rvUltraschallsensorTrigger1(), pin.get_rvUltraschallsensorEcho1());
	rvUltraschallsensor2.init(pin.get_rvUltraschallsensorTrigger2(), pin.get_rvUltraschallsensorEcho2());
	rvUltraschallsensor3.init(pin.get_rvUltraschallsensorTrigger3(), pin.get_rvUltraschallsensorEcho3());
	lvUltraschallsensor1.init(pin.get_lvUltraschallsensorTrigger1(), pin.get_lvUltraschallsensorEcho1());
	lvUltraschallsensor2.init(pin.get_lvUltraschallsensorTrigger2(), pin.get_lvUltraschallsensorEcho2());
	lvUltraschallsensor3.init(pin.get_lvUltraschallsensorTrigger3(), pin.get_lvUltraschallsensorEcho3());

	rhUltraschallsensor1.init(pin.get_rhUltraschallsensorTrigger1(), pin.get_rhUltraschallsensorEcho1());
	rhUltraschallsensor2.init(pin.get_rhUltraschallsensorTrigger2(), pin.get_rhUltraschallsensorEcho2());
	rhUltraschallsensor3.init(pin.get_rhUltraschallsensorTrigger3(), pin.get_rhUltraschallsensorEcho3());
	lhUltraschallsensor1.init(pin.get_lhUltraschallsensorTrigger1(), pin.get_lhUltraschallsensorEcho1());
	lhUltraschallsensor2.init(pin.get_lhUltraschallsensorTrigger2(), pin.get_lhUltraschallsensorEcho2());
	lhUltraschallsensor3.init(pin.get_lhUltraschallsensorTrigger3(), pin.get_lhUltraschallsensorEcho3());

	//Motoren
	MotorA.initialisEngine(pin.get_RadAf(), pin.get_RadAb());
	MotorB.initialisEngine(pin.get_RadBf(), pin.get_RadBb());
	MotorC.initialisEngine(pin.get_RadCf(), pin.get_RadCb());
	MotorD.initialisEngine(pin.get_RadDf(), pin.get_RadDb());
	MotorCDriveA.initialisEngine(pin.get_cRadAf(), pin.get_cRadAb());
	MotorCDriveB.initialisEngine(pin.get_cRadBf(), pin.get_cRadBb());
	MotorCDriveC.initialisEngine(pin.get_cRadCf(), pin.get_cRadCb());
	MotorCDriveD.initialisEngine(pin.get_cRadDf(), pin.get_cRadDb());
}

int fall()
{
	if (pin.get_Parken() == 1)
	{
		return 0;
	}
	else
	{
		if (pin.get_fahrtModiNormalesFahren() == 1) 
		{
			return 1;
		}

		if (pin.get_fahrtModiDrehen() == 1) 
		{
			return 3;
		}
		
		//if (c-button gedrückt) {return 4;}

		return 2;
	}

}


int main()
{
	void SetUp();

	while (true)
	{
		int xAchse = 50;//eig. Werte von Joystick
		int yAchse = 10;
		int zAchse = 0;

		switch(fall())
		{
			case 0:LenkungCDrive.parken();
				break;
		
			case 1:LenkungCDrive.normaleLenkung(xAchse, yAchse);
				break;

			case 2:LenkungCDrive.driften(xAchse, yAchse);
				break;

			case 3:LenkungCDrive.drehen(zAchse);
				break;
		}

		//Zuweisung der Leistungen den Motoren 
		MotorA.set_power(LenkungCDrive.get_leistungRadA());
		MotorB.set_power(LenkungCDrive.get_leistungRadB());
		MotorC.set_power(LenkungCDrive.get_leistungRadC());
		MotorD.set_power(LenkungCDrive.get_leistungRadD());

		std::cout >> "Stellen Sie sich hier ihren gewünschten Output vor." >> std::endl;//Test
	}

	return 0;
}