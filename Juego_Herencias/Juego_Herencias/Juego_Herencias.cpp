// Juego_Herencias.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Personaje.h"
#include "Header.h"

using namespace std;

const int SIZE = 10;
const char EMPTY = ' ';
const char HERO = 'H';
const char ENEMY = 'E';
const char EXIT = 'S';
const char GUARIDA = 'G';

// Función para inicializar el tablero
void initializeBoard(char board[SIZE][SIZE], Personaje& hero, EnemigoFinal& boss, Personaje enemies[], int numEnemies) {
    // Llenar el tablero con espacios vacíos
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }

    // Colocar al héroe en la posición inicial (0,0)
    hero.setPosicionX(0);
    hero.setPosicionY(0);
    board[0][0] = HERO;

    // Colocar la salida en una posición aleatoria en la última fila
    boss.setPosicionX(SIZE - 1);
    boss.setPosicionY(rand() % SIZE);
    board[SIZE - 1][boss.getPosicionY()] = GUARIDA;

    // Colocar enemigos en posiciones aleatorias
    for (int i = 0; i < numEnemies; i++) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (board[x][y] != EMPTY); // Asegurarse de que la posición esté vacía
        enemies[i].setPosicionX(x);
        enemies[i].setPosicionY(y);
        board[x][y] = ENEMY;
    }
}

// Función para mostrar el tablero
void displayBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << "-";
        }
        cout << endl;
    }
}

// Función para manejar el combate entre el héroe y un enemigo
bool combat(Personaje & hero, Personaje & enemy, bool& potionActive) {
    cout << "Combatiendo contra " << enemy.getName() << "!" << endl;
    int originalAttack = hero.getAttack();

    if (potionActive) {
        hero.setAttack(hero.getAttack() * 1.5);
    }

    while (hero.getHp() > 0 && enemy.getHp() > 0) {
        cout << hero.getName() << " ataca a " << enemy.getName() << " causando " << hero.getAttack() << " de dano." << endl;
        enemy.setHp(enemy.getHp() - hero.getAttack());
        cout << enemy.getName() << " ahora tiene " << hero.getHp() << " de vida." << endl;

        if (enemy.getHp() <= 0) {
            cout << enemy.getName() << " ha sido derrotado!" << endl;
            hero.setAttack(originalAttack); // Restaurar el ataque original después del combate
            potionActive = false; // Desactivar la poción después del combate
            return false; // El héroe puede seguir
        }

        cout << enemy.getName() << " ataca a " << hero.getName() << " causando " << enemy.getAttack() << " de dano." << endl;
        hero.setHp(hero.getHp() - enemy.getAttack());
        cout << hero.getName() << " ahora tiene " << hero.getHp() << " de vida." << endl;

        if (hero.getHp() <= 0) {
            cout << "El heroe ha sido derrotado!" << endl;
            return true; // Juego terminado
        }
    }

    return false; // El héroe puede seguir
}


// Función para manejar el combate final entre el héroe y el jefe final
bool finalCombat(Personaje& hero, EnemigoFinal& boss, bool& potionActive) {
    cout << "Combatiendo contra el " << boss.getName() << "!" << endl;
    int originalAttack = hero.getAttack();

    if (potionActive) {
        hero.setAttack(hero.getAttack() * 1.5);
    }

    while (hero.getHp() > 0 && boss.getHp() > 0) {
        cout << hero.getName() << " ataca a " << boss.getName() << " causando " << hero.getAttack() << " de dano." << endl;
        boss.setHp(boss.getHp() - hero.getAttack());

        if (boss.getHp() <= 0) {
            cout << boss.getName() << " ha sido derrotado! Has ganado el juego!" << endl;
            return true; // Fin del juego con victoria
        }

        cout << boss.getName() << " ataca a " << hero.getName() << " causando " << boss.getAttack() << " de dano." << endl;
        hero.setHp(hero.getHp() - boss.getAttack());

        if (hero.getHp() <= 0) {
            cout << "El heroe ha sido derrotado por el " << boss.getName() << ". GAME OVER!" << endl;
            return true; // Fin del juego con derrota
        }
    }

    hero.setAttack(originalAttack); // Restaurar el ataque original después del combate
    potionActive = false; // Desactivar la poción después del combate

    return false; // El héroe sigue en combate
}

// Función para mover al héroe
bool moveHero(char board[SIZE][SIZE], Personaje& hero, EnemigoFinal& boss, Personaje enemies[], int numEnemies, bool& potionUsed, bool& potionActive) {
    char direction;
    cout << "Ingrese direccion (w/a/s/d): ";
    cin >> direction;

    int newPosX = hero.getPosicionX();
    int newPosY = hero.getPosicionY();

    switch (direction) {
    case 'w': newPosX--; break; // Mover arriba
    case 's': newPosX++; break; // Mover abajo
    case 'a': newPosY--; break; // Mover izquierda
    case 'd': newPosY++; break; // Mover derecha
    default: cout << "Direccion no valida!" << endl; return false;
    }

    // Verificar límites del tablero
    if (newPosX < 0 || newPosX >= SIZE || newPosY < 0 || newPosY >= SIZE) {
        cout << "Movimiento fuera del tablero!" << endl;
        return false;
    }

    // Verificar colisión con enemigos
    for (int i = 0; i < numEnemies; i++) {
        if (newPosX == enemies[i].getPosicionX() && newPosY == enemies[i].getPosicionY()) {
            if (combat(hero, enemies[i], potionActive)) {
                return true; // Fin del juego si el héroe es derrotado
            }
            if (enemies[i].getHp() <= 0) {
                board[enemies[i].getPosicionX()][enemies[i].getPosicionY()] = EMPTY; // Eliminar enemigo del tablero
            }

            if (!potionUsed) {
                char usePotion;
                cout << "Deseas usar la pocion magica para restaurar tu vida y aumentar tu dano en el proximo combate? (s/n): ";
                cin >> usePotion;
                if (usePotion == 's' || usePotion == 'S') {
                    hero.setHp(100); // Restaurar toda la vida
                    potionActive = true;
                    potionUsed = true;
                    cout << "Has usado la pocion magica! Tu vida ha sido restaurada y tu daño aumentara en el proximo combate." << endl;
                }
            }
        }
    }

    // Mover al héroe
    board[hero.getPosicionX()][hero.getPosicionY()] = EMPTY;
    hero.setPosicionX(newPosX);
    hero.setPosicionY(newPosY);
    board[newPosX][newPosY] = HERO;

    // Verificar si ha llegado a la guarida
    if (newPosX == boss.getPosicionX() && newPosY == boss.getPosicionY()) {
        cout << "Has llegado a la guarida! Se inicia el combate final!" << endl;
        return true; // Inicia el combate final
    }

    return false;
}

int main() {
    srand(time(nullptr));

    char board[SIZE][SIZE];
    Personaje hero(100, 50, "Hero", 0, 0);
    EnemigoFinal boss(1000, 135, "Final Boss", 400, 75, SIZE - 1, rand() % SIZE);
    Personaje enemies[] = {
        Personaje(150, 25, "Enemigo1", rand() % SIZE, rand() % SIZE),
        Personaje(100, 45, "Enemigo2", rand() % SIZE, rand() % SIZE),
        Personaje(125, 35, "Enemigo3", rand() % SIZE, rand() % SIZE),
        Personaje(200, 20, "Enemigo4", rand() % SIZE, rand() % SIZE)
    };

    int numEnemies = sizeof(enemies) / sizeof(enemies[0]);
    bool potionUsed = false;
    bool potionActive = false;

    initializeBoard(board, hero, boss, enemies, numEnemies);

    cout << "Tablero inicial:" << endl;
    displayBoard(board);

    bool gameOver = false;
    bool finalPhase = false;
    while (!gameOver) {
        if (!finalPhase) {
            gameOver = moveHero(board, hero, boss, enemies, numEnemies, potionUsed, potionActive);
            if (gameOver) {
                finalPhase = true;
                gameOver = false; // Reiniciar gameOver para iniciar el combate final
            }
        }
        else {
            gameOver = finalCombat(hero, boss, potionActive);
        }
        displayBoard(board);
    }

    return 0;
}