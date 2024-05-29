#pragma once
#include "Personaje.h"
#include <iostream>

Personaje::Personaje(int pHp, int pAttack, std::string pName, int pPosicionX, int pPosicionY) {
	hp = pHp;
	attack = pAttack;
	name = pName;
	posicionX = pPosicionX;
	posicionY = pPosicionY;
}

int Personaje::getHp() {
	return hp;
}

std::string Personaje::getName() {
	return name;
}

int Personaje::getAttack() {
	return attack;
}

int Personaje::getPosicionX() {
	return posicionX;
}

int Personaje::getPosicionY() {
	return posicionY;
}

void Personaje::setHp(int php) {
	hp = php;
}

void Personaje::setName(std::string pname) { 
	name = pname;
}



void Personaje::setAttack(int pattack) {
	attack = pattack;
}

void Personaje::setPosicionX(int pposicionX){
	posicionX = pposicionX;
}

void Personaje::setPosicionY(int pposicionY)
{
	posicionY = pposicionY;
}



void Personaje::printStatus() {
	std::cout << "El nombre del personaje es " << getName() << " y tiene una vida de " << getHp() << std::endl;
}
