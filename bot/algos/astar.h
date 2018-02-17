#ifndef ASTAR_H
#define ASTAR_H

#include "bfs.h"

/**
 * Encuentra el camino más corto entre dos localizaciones usando la distancia
 * del taxi como heurística.
 */
Path AStar(const Location & to, const Location & from);

/**
 * Encuentra el camino más corto entre dos localizaciones usando una heurística cualquiera
 * y una función para determinar los obstáculos.
 */
Path AStarCustom(const Location & to, 
    const Location & from, 
    std::function<int(const Location & l)> h, 
    std::function<BFS(const Location &, int)>);

#endif