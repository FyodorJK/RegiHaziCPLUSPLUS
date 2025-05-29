#include "Items.h"

Items::Items(std::string Itemname, int Itemelement, double Itemattack, double Itemdefence, int durability) {
	itemName = Itemname;
	itemElement = Itemelement;
	itemAttack = Itemattack;
	itemDefence = Itemdefence;
	Durability = durability;
}

Items::Items() {
	itemName = "Iron Sword";
	itemElement = 6;
	itemAttack = 6;
	itemDefence = 0;
	Durability = 10;
}

std::string Items::getitemName()const {
	return itemName;
}

int Items::getItemelement()const {
	return itemElement;
}

double Items::getItemAttack()const {
	return itemAttack;
}

double Items::getItemDefence()const {
	return itemDefence;
}

int Items::getDurability()const {
	return Durability;
}

void Items::setItemAttack(double Attack) {
	itemAttack = Attack;
}

void Items::setItemDefence(double Defence) {
	itemDefence = Defence;
}

std::string Items::Elementprinti(int element)const {
	switch (element) {
	case 0: return "Fire"; break;
	case 1: return "Earth"; break;
	case 2: return "Light"; break;
	case 3: return "Darkness"; break;
	case 4: return "Water"; break;
	case 5: return "Wind"; break;
	}
	return "Non";
}

void Items::print()const {
	std::cout << "Item name: " << itemName << std::endl << "Item element: " << Elementprinti(itemElement) << std::endl << "Item attack: " << itemAttack << std::endl << "Item defence: " << itemDefence << std::endl << "Item durability: " << Durability << std::endl << std::endl;
}

Items& Items::operator--(int durabiliy) {
	Durability--;
	return *this;

}
const Items& Items::operator=(const Items& theother) { 
	if (this != &theother) {
		itemName = theother.itemName;
		itemElement = theother.itemElement;
		itemAttack = theother.itemAttack;
		itemDefence = theother.itemDefence;
		Durability = theother.Durability;
	}
	return *this;
}