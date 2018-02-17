#include "IA.h"
#include "actions/Random.h"
#include <climits>

using namespace std;

void IA::init()
{
    // Estado del juego. Singleton, accesible desde cualquier lugar.
    State &s = State::getSingleton();

    // Mapa de hormiga => acción.
    unordered_map<Location, Action *> actions;

    // TODO: Aquí es donde hay que escribir la inteligencia de las hormigas.
    // De ejemplo se deja a las hormigas moviendo al azar.
    for (auto & ant: s.myAnts) {
        actions[ant] = new Random(ant);
    }
    
    // Mover todas las hormigas que no colisionen entre ellas.
    int moved;
    do
    {
        moved = 0;
        for (auto it = actions.begin(); it != actions.end(); it++)
        {
            if (it->second && it->second->canWork())
            {
                moved++;
                it->second->work();
                delete it->second;
                it->second = nullptr;
            }
        }
    } while (moved > 0);
}

void IA::finish()
{
}
