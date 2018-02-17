#ifndef BOT_H_
#define BOT_H_

#include "State.h"
#include "../engine/Scheduler.h"

/*
    This struct represents your bot in the game of Ants
*/
struct Bot
{
    State state;
    Scheduler & sch;

    Bot(Scheduler & sch);

    void playGame();    //plays a single game of Ants

    void updateAlgorithms(); // Actualiza los algoritmos 

    void makeMoves();   //makes moves for a single turn
    void endTurn();     //indicates to the engine that it has made its moves
};

#endif //BOT_H_
