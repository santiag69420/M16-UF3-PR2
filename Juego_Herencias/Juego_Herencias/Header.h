#pragma once
#include "Personaje.h"
#include <iostream>

class EnemigoFinal : public Personaje {
private:
	int fireAttack;
	int hpSpell;


public: 
	EnemigoFinal(int pHp,
		int pAttack,
		std::string pName,
		int pFireAttack,
		int pHpSpell,
		int posicionX,
		int posicionY
	);

	int getFireAttack();
	int getHpSpell();

	void setFireAttack(int pFireAttack);
	void setHpSpell(int pHpSpell);

	void printAllStats();
};
