#pragma once
#ifndef Lenkung_H
#define Lenkung_H

#include <interfaceI2C.h>
#include <math.h>

class Lenkung 
{
private:
	//feste Werte
	double d�mpfung = 0.5;//Damit beim drehen keine 100% Motorauslastung
	double lamda  = 0.5; //Faktor um faktorBremsen zu reduzieren
		
	//zu berechnende Werte 
	double alpha;//Winkel alpha zwischen l�ngeLeistung und X-Achse
	double beta;//Winkel beta zwischen aktuellen Vektor und 45� vektor
	double l�ngeLeistung;//aktuelle Gesamtleistung
	double Vektor1;// l�ngeLeistung aufgeteit auf jeweise 2 R�der
	double Vektor2;
	
	// Ergebnisse
	double leistungRadA;//Rad links vorne
	double leistungRadB;//Rad rechts vorne
	double leistungRadC;//Rad rechts hinten
	double leistungRadD;//Rad links hinten

public:
	//Berechnungen der einzelnen L�ngen etc. nur Klassen intern ben�tigt
	void berechnungenL�nge(int xAchse, int yAchse);
	void berechnungWinkel(int xAchse, int yAchse);
	
	//verschiedene Aufteilungen der Lestungen je nach Modi
	void normaleLenkung(int xAchse, int yAchse);
	void driften(int xAchse, int yAchse);
	void drehen(int zAchse);
	void parken();
	
	//Ausgabe der verschiedenen Leistungen
	double get_leistungRadA() { return leistungRadA; }
	double get_leistungRadB() { return leistungRadB; }
	double get_leistungRadC() { return leistungRadC; }
	double get_leistungRadD() { return leistungRadD; }
};
#endif