#include "Header.h"

EnemigoFinal::EnemigoFinal(int pHp, int pAttack, std::string pName, int pFireAttack, int pHpSpell, int posicionX, int posicionY)
	: Personaje(pHp, pAttack, pName, posicionX, posicionY) {
	fireAttack = pFireAttack;
	hpSpell = pHpSpell;
}

int EnemigoFinal::getFireAttack() {
	return fireAttack;
}

int EnemigoFinal::getHpSpell() {
	return hpSpell;
}

void EnemigoFinal::setFireAttack(int pFireAttack) {
	fireAttack = pFireAttack;
}
void EnemigoFinal::setHpSpell(int pHpSpell) {
	hpSpell = pHpSpell;
}

void EnemigoFinal::printAllStats() {
	std:: cout << "El nombre del enemigo final es " << getName() << std::endl;
	std::cout << "La vida del enemigo final es " << getHp() << std::endl;
	std::cout << "El ataque normal del enemigo final es " << getAttack() <<
		std::endl;
	std::cout << "El ataque de fuego del enemigo final es " << getFireAttack()
		<< std::endl;
	std::cout << "El enemigo final tiene un hechizo de curación que cura un total de " <<
		getHpSpell() << std::endl;
}