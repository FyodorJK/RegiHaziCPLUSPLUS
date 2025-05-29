#pragma once
#include<stdio.h>
#include<iostream>
#include<string.h>
#include"Items.h"




class Character
{
protected:
	std::string name;
	double hitpoints=0;
	double rnHitpoints=0;
	double characterDefence=0;
	double characterAttack=0;
	static int level;
	static int xp;
public:
	std::string getname()const; //kiirasokhoz
	double getHitpoints()const; //resethez
	double getRNHitpoints()const; //szamolashoz, ellenorzeshez
	double getCharacterDefence()const; //szamolashoz
	double getCharacterAttack()const; //szamolashoz
	void setHitpoints(double); //costum
	void setRNHitpoints(double); //costum
	void setCharacterDefence(double); //costum
	void setCharacterAttack(double); //costum
	void setlevelandxp(); //reward
	int getlevel()const; //costum
	virtual void print()const=0; //virtual nyomtatas
};


class Enemy : public Character
{
private:
	int EnemyElement;
	double EnemyPotential;
public:
	Enemy();
	Enemy(std::string, double, double, double, int, double);
	int getEnemyElement()const; //szamolashoz
	double getEnemyPotential()const; //szamolashoz
	double ElementpercentE(const Items&)const; //szamolas konnyito
	std::string Elementprinte(int)const; //stringre konvertal
	void print()const; //nyomtatas
	void setrandomstats(int, int, int); //costum enemy csinalo
	const Enemy& operator=(const Enemy&); //masolashoz
};

class Player: public Character
{
private:
	int abilitynumber;
	bool battleAttack;
	bool battleDefence;
	Items *inventory;
	int inventorysize;
	Items Weaponhand;
	Items Armorbody;
public:
	Player(std::string, int);
	~Player();
	bool getbattleAttackAbility()const; //ellenorzeshez
	bool getbattleDefenceAbility()const; //ellenorzeshez
	Items getWeaponhand()const; //szamolashoz
	void setWeaponhand(Items); //costum
	Items getArmorbody()const; //szamolashoz
	void setArmorbody(Items); //costum
	void print()const; //nyomtatas
	int getInvetorysize()const; //szamolas, segit a keresesben
	void setInvetorysize(int); //costum
	void printinventory()const; //inventory kiirasa
	void addinventoryitem(const Items&); //loot, equip itemek elrakasa
	void removeinventoryitem(int); //equip item torlese
	void beforeBattleAbilty(); //kepesseg
	double battleAttackAbility(double&); //kepesseg
	double battleDefenceAbility(double&,int); //kepesseg
	Items loot(Items*, int, int); //loot generalasa
	double ElementpercentP(const Enemy&)const; //szamolashoz
	Items getInventoryitem(int)const; //item ki
	void durabilityminus(int);
};