#pragma once
#include<stdio.h>
#include<iostream>
#include<string.h>

	//Fire = 0
	//Earth = 1
	//Light = 2
	//Darkness = 3
	//Water = 4
	//Wind = 5
	//Non = 6

class Items
{
private:
	std::string itemName;
	int itemElement;
	double itemAttack;
	double itemDefence;
	int Durability;
public:
	Items(std::string, int, double, double, int);
	Items();
	std::string getitemName()const; //ellenorzeshez
	int getItemelement()const; //szamolashoz
	double getItemAttack()const; //szamolashoz
	double getItemDefence()const; //szamolashoz
	int getDurability()const; //szamolashoz, ellenorzeshez
	void setItemAttack(double); //costum
	void setItemDefence(double); //costum
	std::string Elementprinti(int)const; //stringe alakitas
	void print()const; //kiiras
	Items& operator--(int); //durability csokkentesehez
	const Items& operator=(const Items&); //itemek masolasahoz
};

