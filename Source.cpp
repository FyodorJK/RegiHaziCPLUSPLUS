//Nemeth Akos
//HOM2DS
//Harcosok Utja
//rekord: lvl 10
#include<string.h>
#include<stdio.h>
#include<iostream>
#include <fstream>
#include<time.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include"Items.h"
#include"Character.h"


int random(int veg) {
	int randomNum;
	randomNum = (std::rand() % (veg + 1));
	return randomNum;
}

void Equip(Player& you) {
	if (you.getInvetorysize() == 0)
	{
		return;
	}
	you.printinventory();
	std::cout << "Choose an items" << std::endl;
	int chosen, to = 0;
	bool affirm = false, slot = false;
	while (affirm != true)
	{
		std::cin >> chosen;
		if (chosen <= you.getInvetorysize()-1 && chosen >= 0) {
			affirm = true;
		}
	}
	std::cout << "Equip it to: " << std::endl << "1: Hand" << std::endl << "2: Body" << std::endl;
	while (slot != true)
	{
		std::cin >> to;
		if (to == 1 || to == 2) {
			slot = true;
		}
	}
	if (affirm == true && slot == true) {
		if (to == 1) {
			if (you.getWeaponhand().getitemName() != "Fist") {
				you.addinventoryitem(you.getWeaponhand());
			}
			you.setWeaponhand(you.getInventoryitem(chosen));
			you.removeinventoryitem(chosen);
		}
		else
		{
			if(you.getArmorbody().getitemName() != "Clothes") {
				you.addinventoryitem(you.getArmorbody());
		}
				you.setArmorbody(you.getInventoryitem(chosen));
				you.removeinventoryitem(chosen);
		}
	}
}

void attacking(Player& you, Enemy enemy) {
	bool end = false;
	int answer = 0;
	bool answerbool = false;
	while (end != true) { 
		while (answerbool != true) {
			std::cout << "Choose: " << std::endl << "1: Attack!" << std::endl << "2: Equip a weapon or an armor" << std::endl;
			std::cin >> answer;
			if (answer == 1 || answer == 2)
			{
				answerbool = true;
			}
		}
		answerbool = false;
		if (answer == 2) {
			int finished = 2;
			while (finished != 1) {
				Equip(you);
				std::cout << "Are you ready?" << std::endl << "1: Yes" << std::endl << "2: No" << std::endl;
				std::cin >> finished;
			}
		}
		double dmg = ((you.getCharacterAttack() + you.getWeaponhand().getItemAttack()) - (enemy.getCharacterDefence()/10)) * enemy.ElementpercentE(you.getWeaponhand());
		if (you.getbattleAttackAbility() == true) {
			you.battleAttackAbility(dmg);
		}
		enemy.setRNHitpoints(enemy.getRNHitpoints() - dmg);
		std::cout << you.getname() << " dealt " << dmg << " dmg!" << std::endl;
		std::cout << enemy.getname() << " has " << enemy.getRNHitpoints() << "/" << enemy.getHitpoints() << " HP!" << std::endl;
		you.durabilityminus(1);
		if (you.getWeaponhand().getDurability() == 0) {
			std::cout << "Your weapon is broken, equip a new one in the next round!" << std::endl;
			Items hand("Fist", 6, 1, 0, 9999);
			you.setWeaponhand(hand);
		}
		if (you.getRNHitpoints() <= 0) {
			std::cout << you.getname() << " died, becouse of self-harm, dummy!" << std::endl << "Better luck next time" << std::endl;
			return;
		}
		if (enemy.getRNHitpoints() <= 0) {
			end = true;
		}
		else
		{
			dmg = (enemy.getCharacterAttack() - you.getArmorbody().getItemDefence() / 10) * you.ElementpercentP(enemy);
			if (you.getbattleDefenceAbility() == true) {
				you.battleDefenceAbility(dmg, random(100));
			}
			you.setRNHitpoints(you.getRNHitpoints() - dmg);
			std::cout << enemy.getname() << " dealt " << dmg << " dmg!" << std::endl;
			std::cout << you.getname() << " has " << you.getRNHitpoints() << "/" << you.getHitpoints() << " HP!" << std::endl;
			you.durabilityminus(2);
			if (you.getArmorbody().getDurability() == 0) {
				std::cout << "Your weapon is broken, equip a new one in the next round!" << std::endl;
				Items clothes("Clothes", 6, 0, 1, 9999);
				you.setArmorbody(clothes);
			}
			if (you.getRNHitpoints() <= 0) {
				end = true;
				std::cout << you.getname() << " died!" << std::endl << "Better luck next time!" << std::endl;
			}
		}
	}

}

void Attack(Player& you, Enemy* tombe, int sizee, Items* tombi, int sizei) {
	Enemy eins, zwei, drei;
	eins = tombe[random(sizee-1)];
	eins.setrandomstats(random((eins.getHitpoints() * eins.getEnemyPotential()) * eins.getlevel()), random((eins.getCharacterAttack() * eins.getEnemyPotential()) * eins.getlevel()), random((eins.getCharacterDefence() * eins.getEnemyPotential()) * eins.getlevel()));
	std::cout << std::endl;
	eins.print();
	zwei = tombe[random(sizee-1)];
	zwei.setrandomstats(random((zwei.getHitpoints() * zwei.getEnemyPotential()) * zwei.getlevel()), random((zwei.getCharacterAttack() * zwei.getEnemyPotential()) * zwei.getlevel()), random((zwei.getCharacterDefence() * zwei.getEnemyPotential()) * zwei.getlevel()));
	zwei.print();
	drei = tombe[random(sizee-1)];
	drei.setrandomstats(random((drei.getHitpoints() * drei.getEnemyPotential()) * drei.getlevel()), random((drei.getCharacterAttack() * drei.getEnemyPotential()) * drei.getlevel()), random((drei.getCharacterDefence() * drei.getEnemyPotential()) * drei.getlevel()));
	drei.print();
	std::cout << "Choose a path from 1 to 3: " << std::endl;
	int chosen = 0;
	bool answer = false;
	while (answer != true) {
		std::cin >> chosen;
		if (chosen >= 1 && chosen <= 3) {
			answer = true;
		}
	}
	switch (chosen) {
	case 1: attacking(you, eins); break;
	case 2: attacking(you, zwei); break;
	case 3: attacking(you, drei); break;
	}
	if (you.getRNHitpoints() > 0) {
		you.addinventoryitem(you.loot(tombi, random(sizei - 1), random(you.getlevel())));
		std::cout << you.getname() << " got an:" << std::endl;
		you.getInventoryitem(you.getInvetorysize() - 1).print();
		you.setlevelandxp();
	}
}

void Statistics(Player& you) {
	you.print();
}

bool mainplace(Player& you, Enemy* tombe, int sizee, Items* tombi, int sizei) {
	std::cout << "Mainplace: " << std::endl << "1: Attack" << std::endl << "2: Equip armor or weapon" << std::endl << "3: Statistics" << std::endl << "0: Leave" << std::endl;
	int answer;
	bool answerbool=false;
	while (answerbool!=true) {
		std::cin >> answer;
		if (answer <= 3 && answer >= 0)
		{
			answerbool = true;
		}
	}
	switch (answer)
	{
	case 1:Attack(you, tombe, sizee, tombi, sizei); break;
	case 2:Equip(you); break;
	case 3:Statistics(you); break;
	case 0:std::cout << "Are you sure about that?" << std::endl << "1: Yes!" << std::endl << "2: No" << std::endl; std::cin >> answer; if (answer == 1) { you.setRNHitpoints(0); }; break;
	}
	answerbool = false;
	if (you.getRNHitpoints() <= 0) {
		answerbool = true;
	}
	return answerbool;
}

void reset(Player& you) {
	you.setRNHitpoints(you.getHitpoints());
}

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::srand((unsigned int)std::time(nullptr));
	std::cout << "Welcome to my game!" << std::endl << "Start?" << std::endl << std::endl << "1:Start!" << std::endl << "2:Nope!" << std::endl;
	int answer=0;
	while (answer != 1)
	{
		std::cin >> answer;
		if (answer == 2)
		{
			return 0;
		}
	}
	std::string playername;
	std::cout << "Enter your name: ";
	std::cin >> playername;
	std::cout << "Choose an ability:"  << std::endl << "	1: Normal player" << std::endl << "	2: Tank player" << std::endl << "	3: DMG dealer player" << std::endl << "	4: 'Double' hit" << std::endl << "	5: Vampire" << std::endl << "	6: Double edged sword" << std::endl << "	7: Dodge build" << std::endl << "	8: Panic attack" << std::endl << "	0: Chicken out of game" << std::endl << std::endl;
	bool answerout=false;
	while (answerout!=true)
	{
		std::cin >> answer;
		if (answer == 0)
		{
			return 0;
		}
		if (answer <= 8 && answer >= 0)
		{
			answerout = true;
		}
	}
	Player You(playername, answer);

	std::string stringread; //nev
	double read1=0; //HP
	double read2=0; //DMG
	double read3=0; //DEF
	int elementread=0; //element
	double read4=0; //potential
	int sizee = 0;
	Enemy* Enemytomb = nullptr;

	std::ifstream Enemytxt("Enemy.txt");
	if (!Enemytxt) {
		std::cout << "Error: Enemy.txt could not be opened" << std::endl;
		return -1;
	}
	while (!Enemytxt.eof()) {
		Enemytxt >> stringread >> read1 >> read2 >> read3 >> elementread >> read4;
		Enemy EnemyMaker(stringread, read1, read2, read3, elementread, read4);
		Enemy* temp = new Enemy[sizee + 1];
		for (int i = 0; i < sizee; i++)
		{
			temp[i] = Enemytomb[i];
		}
		temp[sizee] = EnemyMaker;
		delete[]Enemytomb;
		Enemytomb = temp;
		sizee++;

	}
	Enemytxt.close();

	int read5;
	int sizei = 0;
	Items* Itemstomb = nullptr;

	std::ifstream Itemstxt("Items.txt");
	if (!Itemstxt) {
		std::cout << "Error: Items.txt could not be opened" << std::endl;
		return - 1;
	}
	while (!Itemstxt.eof()) {
		Itemstxt >> stringread >> elementread >> read2 >> read3 >> read5;
		Items ItemMaker(stringread, elementread, read2, read3, read5);
		//ItemMaker.print();
		Items* temp1 = new Items[sizei + 1];
		for (int i = 0; i < sizei; i++)
		{
			temp1[i] = Itemstomb[i];
		}
		temp1[sizei] = ItemMaker;
		delete[]Itemstomb;
		Itemstomb = temp1;
		sizei++;
	}
	Itemstxt.close();
	bool end=false;
	if (sizee == 0)
	{
		std::cout << "Nincs eleg Enemy" << std::endl;
		return -1;
	}
	if (sizei == 0)
	{
		std::cout << "Nincs eleg Item" << std::endl;
		return -1;
	}
	while (end != true) {
		end = mainplace(You, Enemytomb, sizee, Itemstomb, sizei);
		if (end == false)
		{
			reset(You);
		}
	}
	delete[]Enemytomb;
	delete[]Itemstomb;
	return 0;

}