#include "Character.h"


int Character::level = 1;
int Character::xp = 0;

std::string Character::getname()const {
	return name;
}

double Character::getHitpoints()const {
	return hitpoints;
}

double Character::getRNHitpoints()const {
	return rnHitpoints;
}

double Character::getCharacterDefence()const {
	return characterDefence;
}

double Character::getCharacterAttack()const {
	return characterAttack;
}

void Character::setHitpoints(double HP) {
	hitpoints = HP;
}

void Character::setRNHitpoints(double RHP) {
	rnHitpoints = RHP;
}

void Character::setCharacterDefence(double CDEF) {
	characterDefence = CDEF;
}

void Character::setCharacterAttack(double CATK) {
	characterAttack = CATK;
}

void Character::setlevelandxp() {
	xp++;
	if (xp == level)
	{
		xp = 0;
		level++;
		std::cout << name << " leveled up to " << level << std::endl;
	}
}

int Character::getlevel()const {
	return level;
}

Player::Player(std::string Name, int abilitynum){
	name = Name;
	hitpoints = 100;
	rnHitpoints = hitpoints;
	characterAttack = 5;
	characterDefence = 5;
	abilitynumber = abilitynum;
	inventory = nullptr;
	inventorysize = 0;
	Items starterweapon("Starter_Weapon", 6, 6, 0, 10);
	Weaponhand = starterweapon;
	Items starterarmor("Leather_Armor", 6, 0, 5, 10);
	Armorbody = starterarmor;

	if (abilitynum >= 1 && abilitynum <= 3)
	{
		battleAttack = false;
		battleDefence = false;
		beforeBattleAbilty();
	}
	else if (abilitynum >= 4 && abilitynum <= 6)
	{
		battleAttack = true;
		battleDefence = false;
	}
	else if (abilitynum >= 7 && abilitynum <= 8)
	{
		battleAttack = false;
		battleDefence = true;
	}
}

Player::~Player() {
	delete[]inventory;
}

bool Player::getbattleAttackAbility()const {
	return battleAttack;
}

bool Player::getbattleDefenceAbility()const {
	return battleDefence;
}

Items Player::getWeaponhand()const {
	return Weaponhand;
}

void Player::setWeaponhand(Items weapon) {
	Weaponhand = weapon;
}

Items Player::getArmorbody()const {
	return Armorbody;
}

void Player::setArmorbody(Items armor) {
	Armorbody = armor;
}

int Player::getInvetorysize()const {
	return inventorysize;
}

void Player::setInvetorysize(int size) {
	inventorysize = size;
}

void Player::print()const {
	std::cout << "Name: " << name << std::endl << "Level: " << level << std::endl << "Xp: " << xp << std::endl << "Hitpoints: " << rnHitpoints << "/" << hitpoints << std::endl << "ATK: " << characterAttack << std::endl << "DEF: " << characterDefence << std::endl << "Ability number: " << abilitynumber << std::endl << "Inventory size: " << inventorysize << std::endl << std::endl << "Weapon: ";
	Weaponhand.print();
	std::cout << "Armor: ";
	Armorbody.print();
	std::cout << std::endl << std::endl;
}

void Player::printinventory()const {
	if (inventorysize == 0)
	{
		return;
	}
	else {
		for (int i = 0; i < inventorysize; i++)
		{
			std::cout << std::endl << i << ":" << std::endl;
			inventory[i].print();
		}
	}
}

void Player::addinventoryitem(const Items& item) {
	Items* temp = new Items[inventorysize + 1];
	for (int i = 0; i < inventorysize; i++) {
		temp[i] = inventory[i];
	}
	temp[inventorysize] = item;
	inventorysize++;
	delete[] inventory;
	inventory = temp;
}

void Player::removeinventoryitem(int position) {
	if (inventorysize == 0) {
		return;
	}
	if (position <= -1 || position >= inventorysize - 1) {
		return;
	}
	inventorysize--;
	Items* temp = new Items[inventorysize];
	for (int i = 0, j = 0; i <= inventorysize; i++, j++) {
		if (i == position) {
			j--;
		}
		else
		{
			temp[j] = inventory[i];
		}
	}
	delete[]inventory;
	inventory = temp;
}

void Player::beforeBattleAbilty() {
	if (abilitynumber == 1)
	{
		return;
	}
	else if (abilitynumber == 2)
	{
		hitpoints = 150;
		rnHitpoints = 150;
		characterAttack = 2.5;
		characterDefence = 7.5;
		return;
	}
	else if (abilitynumber == 3)
	{
		hitpoints = 50;
		rnHitpoints = 50;
		characterAttack = 7.5;
		characterDefence = 2.5;
		return;
	}
	return;
}

double Player::battleAttackAbility(double& DMG) {
	if (abilitynumber == 4)
	{
		DMG = DMG * 1.5;
	}
	else if (abilitynumber == 5)
	{
		rnHitpoints = rnHitpoints + (DMG * 0.3);
		DMG = DMG * 0.7;
	}
	else if (abilitynumber == 6)
	{
		rnHitpoints = rnHitpoints - (DMG * 0.25);
		DMG = DMG * 3;
	}
	return DMG;
}

double Player::battleDefenceAbility(double& dmg, int chance) {
	if (abilitynumber == 7)
	{
		if(chance <= 40 && chance >= 0)
		{
			std::cout << "Successful dodge" << std::endl;
			dmg = 0;
		}
	}
	if (abilitynumber == 8)
	{
		double difference;
		difference = hitpoints - rnHitpoints;
		Weaponhand.setItemAttack(Weaponhand.getItemAttack() + difference);
	}
	return dmg;
}

Items Player::loot(Items* tomb, int randval, int chance) {
	Items loot = tomb[randval];
	loot.setItemAttack(loot.getItemAttack()+((loot.getItemAttack()*0.25)*chance));
	loot.setItemDefence(loot.getItemDefence() + (loot.getItemDefence() * 0.25 * chance));
	return loot;
}

double Player::ElementpercentP(const Enemy& enemy)const {
	Items armor=Armorbody;
	int element = armor.getItemelement();
	if (element==enemy.getEnemyElement()) {
		return 1;
	}
	else if (enemy.getEnemyElement() + 1 == element) {
		return 1.5;
	}
	else if (enemy.getEnemyElement() - 1 == element) {
		return 0.5;
	}
	else if (enemy.getEnemyElement() - 1 == -1 && element == 5) {
		return 0.5;
	}
	else if (enemy.getEnemyElement() + 1 == 6 && element == 0) {
		return 1.5;
	}
	return 1;
}

Items Player::getInventoryitem(int i)const {
		return inventory[i];
}

void Player::durabilityminus(int item){
	if (item == 1) {
		Weaponhand--;
	}
	else
	{
		Armorbody--;
	}
}

Enemy::Enemy() {
	name = " ";
	hitpoints = 1;
	rnHitpoints = 1;
	characterAttack = 1;
	characterDefence = 1;
	EnemyElement = 0;
	EnemyPotential = 0;
}

Enemy::Enemy(std::string Name, double Hitpoints, double Characterattack, double Characterdefence, int element, double Potential) {
	name = Name;
	hitpoints = Hitpoints;
	rnHitpoints = Hitpoints;
	characterAttack = Characterattack;
	characterDefence = Characterdefence;
	EnemyElement = element;
	EnemyPotential = Potential;
}

int Enemy::getEnemyElement()const {
	return EnemyElement;
}

double Enemy::getEnemyPotential()const {
	return EnemyPotential;
}

double Enemy::ElementpercentE(const Items& weapon)const {
	if (EnemyElement == weapon.getItemelement()) {
		return 1;
	}
	else if (weapon.getItemelement() == 6) {
		return 1;
	}
	else if (EnemyElement == weapon.getItemelement() + 1) {
		return 1.5;
	}
	else if (EnemyElement == weapon.getItemelement() - 1) {
		return 0.5;
	}
	else if (weapon.getItemelement() - 1 == -1 && EnemyElement == 5) {
		return 0.5;
	}
	else if (weapon.getItemelement() + 1 == 6 && EnemyElement == 0) {
		return 1.5;
	}
	return 1;
}

std::string Enemy::Elementprinte(int element)const {
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

void Enemy::print()const {
	std::cout << "Name: " << name << std::endl << "Hitpoints: " << rnHitpoints << "/" << hitpoints << std::endl << "ATK: " << characterAttack << std::endl << "DEF: " << characterDefence << std::endl << "Enemy element: " << Elementprinte(EnemyElement) << std::endl << std::endl;
}

void Enemy::setrandomstats(int hp, int atk, int def) {
	hitpoints = hitpoints + hp;
	rnHitpoints = hitpoints;
	characterAttack = characterAttack + atk;
	characterDefence = characterDefence + def;
}

const Enemy& Enemy::operator=(const Enemy& theother) {
	if (this != &theother) {
		name = theother.name;
		hitpoints = theother.hitpoints;
		rnHitpoints = theother.rnHitpoints;
		characterAttack = theother.characterAttack;
		characterDefence = theother.characterDefence;
		EnemyElement = theother.EnemyElement;
		EnemyPotential = theother.EnemyPotential;
	}
	return *this;
}