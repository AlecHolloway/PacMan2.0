#include<stdio.h> 
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include "consts.h"
#include "myfunctions.h"
#include "queue.h"
#include<string.h>

struct playerStats {
    int lives;
    int score;
    bool isPoweredUp; //if true pacman is invincible 
};

static struct playerStats player;  //static global variable is seen only in the file

int main() {
    int Board[ROWS][COLUMNS] =                                    
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 7, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1, 8, 3, 3, 3, 1},
        {1, 3, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 3, 3, 3, 1, 2, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 3, 3, 1, 4, 1, 3, 1, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 1, 3, 1},
        {1, 1, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1},
        {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    int *pacmanPtr;
    int *boardPtr;
    int *pinkyPtr;
    int *blinkyPtr;
    int *inkyPtr;
    int *clydePtr;
    
    inkyPtr = getCharacter(Board, INKY);
    blinkyPtr = getCharacter(Board, BLINKY);
    pinkyPtr = getCharacter(Board, PINKY);
    clydePtr = getCharacter(Board, CLYDE);
    pacmanPtr = getCharacter(Board, PACMAN);
    boardPtr = &Board[0][0];
    
    
    player.lives = 3;
    player.score = 0;
    player.isPoweredUp = false;
   
    bool game = true;
    
    //ghost searching data
    struct queue *Frontier = (struct queue *)malloc(sizeof(struct queue));
    if (Frontier == NULL) {
        fprintf(stderr, "Memory allocation failed for Frontier\n");
        exit(EXIT_FAILURE);
    }
    initQ(Frontier);
    bool vis[ROWS][COLUMNS];
    memset(vis, false, sizeof vis);
  
    while(game == true) {
        printBoard(Board);
        int direction = getUserInput();
        if(direction == 'q') {
            //displayQueue(Frontier);
            free(Frontier);
            exit(1);
        }
        //if direction does not equal q,a,s,d,w then ask again
        while ((direction != 113) && (direction != 97) && (direction != 115) && (direction != 100) && (direction != 119)) {
            direction = getUserInput();
        }
        
        int *newLocation = getNewLocation(direction, pacmanPtr);
        if(*newLocation == WALL) {
            continue;
        }
        else if((*newLocation == PELLET) || (*newLocation == EMPTY)) {
           pacmanPtr = emptyAndMovePacMan(newLocation, pacmanPtr);
        }
        else if(*newLocation = POWERPELLET) {
           pacmanPtr = emptyAndMovePacMan(newLocation, pacmanPtr);
           handlePowerUp(player); }
        else if((*newLocation == INKY) || (*newLocation == BLINKY) || (*newLocation == PINKY) || (*newLocation == CLYDE)) {
            handleGhostEncounter();
            switch(*newLocation) {
                case(INKY):
                    inkyPtr = swapGhostPacman(newLocation, pacmanPtr);
                case(BLINKY):
                    blinkyPtr = swapGhostPacman(newLocation, pacmanPtr);
                case(PINKY):
                    pinkyPtr = swapGhostPacman(newLocation, pacmanPtr);
                case(CLYDE):
                    clydePtr = swapGhostPacman(newLocation, pacmanPtr);
                break;
            } 
        }
        //GHOST MOVEMENT STARTS HERE
        //WORKING IN A SIMPLE PARADIGM 
        enqueue(Frontier, inkyPtr);
        //explore root node
        if(Frontier->head->data == PACMAN) {
            handleGhostEncounter();
        }
        else if(Frontier->head->data == WALL) {
            continue;
        }
        else if(Frontier->head->data == CLYDE) {
            continue;
        }
        else if((Frontier->head->data == PELLET) || (Frontier->head->data == POWERPELLET)){
             
            continue;
        } 
        vis[getRow(Board, inkyPtr)][getCol(Board, inkyPtr)] = 1;  
        dequeue(Frontier);        
        enqueue(Frontier, inkyPtr - 1);
        enqueue(Frontier, inkyPtr + 20);
        enqueue(Frontier, inkyPtr + 1);
        enqueue(Frontier, inkyPtr - 20);

        //add adjacent nodes to queue in order of left, up, down, right
        //explore
         
    }
    displayQueue(Frontier);
    free(Frontier);
}

 int *getNewLocation(int direction, int *pacmanPtr) {
     int *newLocation = NULL;
     //ascii value of a
     if (direction == 97) {
        newLocation = pacmanPtr - 1;
        return newLocation;
     }
     //ascii value of s
     else if(direction == 115) {
         newLocation = pacmanPtr + 20;
         return newLocation;
     }
     //ascii value of d
     else if(direction == 100) {
         newLocation = pacmanPtr + 1;
         return newLocation;
     }
     //ascii value of w
     else if(direction == 119) {
         newLocation = pacmanPtr - 20;
         return newLocation;
     }
     else {
         printf("invalid input");
         //maybe exit function here???
     }
     return NULL;
 }


int getUserInput() {
    int c;
    c = getchar();
    return c;
}


void printBoard(int Board[][COLUMNS]) { 
    system("clear"); 
    for(int x = 0; x < ROWS; x++) {
        for(int y = 0; y < COLUMNS; y++) {
            printf("%d\t", Board[x][y]);
        }
        printf("\n");
    }
}

int *emptyAndMovePacMan(int *newLocation, int *pacmanPtr) {
    *newLocation = 4;
    *pacmanPtr = 0;
    pacmanPtr = newLocation;
    return pacmanPtr;
}

void handleGhostEncounter() {
    if(player.isPoweredUp == false) {
        exit(1);
    }
    else {
        //ghost becomes unable to move for 5 turns
        //ghost.isMobile == false
        //ghost and pacman have no interaction
        //could share the same tile
        //continue moving as normal
    }
}
void handlePowerUp() {
    if(player.isPoweredUp == false) {
        player.isPoweredUp == true;
    }
    //create thread of execution to set timer
    //when timer runs out POWERup is false
    printf("test");
}

int getCol(int Board[][COLUMNS], int* tile) {
    return ((tile - *Board) % COLUMNS);
}

int getRow(int Board[][COLUMNS], int* tile) {
    return ((tile - *Board) / COLUMNS);
}
bool isValid(bool vis[][COLUMNS], int row, int column) {
    if(row < 0 || column < 0 || row > ROWS || column > COLUMNS ) {
        return false;
    }
    if(vis[row][column] == true) {
        return false;
    }
    return true;
}
        

int *getCharacter(int Board[][COLUMNS], int character) {
     for(int x = 0; x < ROWS; x++) {
        for(int y = 0; y < COLUMNS; y++) {
            if(Board[x][y] == character) {
                return &Board[x][y];
            }
        }
    }
    return NULL;
}


int *swapGhostPacman(int *newLocation, int *pacmanPtr) {
    int *tmp = newLocation;
    *newLocation = 4; //pacman or x for imobile ghost
    pacmanPtr = newLocation;
    //ghost is imobile

}





