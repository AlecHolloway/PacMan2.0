// myfunctions.h
#include "consts.h"
#include "queue.h"
#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

 
int *movePacMan();
int getUserInput();
void printBoard(int Board[][COLUMNS]);
void clearScreen();
int *compare(int *pacmanPtr, int *newLocation);
void handleGhostEncounter();
int* updateLocations(int *pacmanPtr, int *newLocation);
void handlePowerUp();
void handleGhostEncounters();
int *moveInky(int Board[][COLUMNS], struct queue *);
int *getCharacter(int Board[][COLUMNS], int character);
int *getNewLocation(int direction, int *pacmanPtr);
int getRow(int Board[][COLUMNS], int* tile);
int getCol(int Board[][COLUMNS], int* tile);
int *emptyAndMovePacMan(int *newLocation, int *pacmanPtr);
int *swapGhostPacman(int *newLocation, int *pacmanPtr);
void addToQueue(int *ghost, struct queue *q, int *board);
int findColumn(void *base_address, void *index_address);
int findRow(void *base_address, void *index_address);
//int *moveBlinky();
//int *movePinky();
//int *moveClyde();
//void initQ(queue *);

#endif 
