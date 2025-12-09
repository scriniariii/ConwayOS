#include "conway.h"
#include "graphics.h"
#include "../utils/util.h"

#define WIDTH  80
#define HEIGHT 25

static int grid[HEIGHT][WIDTH];
static int nextGrid[HEIGHT][WIDTH];

static void delay(int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 100000; j++) {
            __asm__ __volatile__("cli");
        }
    }
}

// Contar vecinos vivos
static int count_neighbors(int y, int x) {
    int count = 0;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            // Saltar la celda central
            if (dx == 0 && dy == 0) continue;

            int ny = y + dy;
            int nx = x + dx;

            // Verificar límites
            if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH) {
                if (grid[ny][nx] == 1)
                    count++;
            }
        }
    }

    return count;
}

// Actualizar estado del juego
static void conway_step() {
    // Calcular siguiente generación
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = count_neighbors(y, x);

            if (grid[y][x] == 1) {
                // Célula viva: sobrevive con 2 o 3 vecinos
                nextGrid[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                // Célula muerta: nace con exactamente 3 vecinos
                nextGrid[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    // Copiar nextGrid a grid
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = nextGrid[y][x];
        }
    }
}

// Dibujar el grid en pantalla
static void conway_draw() {
    clear_screen();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == 1) {
                print("@", y, x, VGA_GREEN, VGA_BLACK);
            } else {
                print(" ", y, x, VGA_BLACK, VGA_BLACK);
            }
        }
    }
}

// Inicializar con patrón inicial (Glider)
void conway_init() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = 0;
            nextGrid[y][x] = 0;
        }
    }

    // Glider en posición inicial
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;
    
    // Blinker
    grid[10][10] = 1;
    grid[10][11] = 1;
    grid[10][12] = 1;
}

// bucle principal
void conway_run() {
    conway_init();

    while (1) {
        conway_draw();
        conway_step();
        delay(5);  
}