# Preguntas frecuentes

### ¿Dónde debería empezar a escribir el bot?

Justo en la línea 15 de IA.cc:
https://github.com/ezequiel-umu/CC18FrameworkIA/blob/master/bot/IA.cc#L15

### ¿Cómo puedo _ver_ la comida, mis hormigas, las colinas, etc...?

Si tenéis una localización, podéis comprobar la información de la casilla usando lo siguiente:

```cpp
State & state = State::getSingleton();
Location l;

...

// La hormiga en una casilla
// Si vale -1 no hay hormiga
// Si vale 0 hay una hormiga de tu equipo
// Si vale > 0 hay una hormiga enemga
state.getGrid(l).ant 

// La colina en una casilla
// Misma lógica que con las hormigas (-1 es no hay colina, 0 es colina propia...)
state.getGrid(l).hillPlayer

// Si la casilla es agua
state.getGrid(l).isWater

// Más información en engine/Square.h

```

Si no tenéis una localización, y lo que queréis es iterar por todas las comidas, hormigas, colinas...

```cpp
State & state = State::getSingleton();

...

// Iterar por cada comida
for (auto food : state.food)
{
  // food es cada comida
}

// Iterar por cada hormiga aliada
for (auto ant : state.myAnts)
{
  // ant es cada hormiga
}

// Iterar por cada colina aliada
for (auto ant : state.enemyHills)
{
  // ant es cada hormiga
}
```

### ¿Dónde puedo hacer más preguntas?

https://github.com/ezequiel-umu/CC18FrameworkIA/issues


## Pasos para subir la primera versión del bot

1. Clonar el repositorio
```
git clone https://github.com/ezequiel-umu/CC18FrameworkIA
```
2. Crear una copia en .tar.gz
```
cd CC18FrameworkIA/bot
make zip
```
3. Subir `bot.tar.gz` a la web.