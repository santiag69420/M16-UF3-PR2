#pragma once
#include <iostream>
class Personaje {
private:
	int hp;
	std::string name;
	int attack;
	int posicionX;
	int posicionY;

public:
	Personaje(int pHp, int pAttack, std::string pName, int pPosicionX, int pPosicionY);
	

	int getHp();
	int getAttack();
	std::string getName();
	int getPosicionX();
	int getPosicionY();

	void setHp(int php);
	void setAttack(int pattack);
	void setName(std::string pname);
	void setPosicionX(int pposicionX);
	void setPosicionY(int pposicionY);
	

	void printStatus();
};


