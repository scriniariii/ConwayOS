#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_YELLOW = 14,
    VGA_WHITE = 15,
};

// Crear atributo de color VGA
static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | (bg << 4);
}

// Crear entrada VGA (caracter + color)
static inline unsigned short vga_entry(unsigned char c, unsigned char color) {
    return (unsigned short)c | ((unsigned short)color << 8);
}

// Calcular longitud de string
int strlen(const char* str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

// Limpiar pantalla
void clear_screen(void) {
    volatile unsigned short* video = (volatile unsigned short*) VGA_MEMORY;
    unsigned char color = vga_entry_color(VGA_BLACK, VGA_BLACK);
    unsigned short blank = vga_entry(' ', color);

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video[i] = blank;
    }
}

// Escribir string con MÁXIMA protección contra desbordamiento
void print(const char* str, int row, int col, enum vga_color fg, enum vga_color bg) {
    // VALIDACIÓN CRÍTICA: verificar límites ANTES de hacer nada
    if (!str) return;  // String nulo
    if (row < 0 || row >= VGA_HEIGHT) return;  // Fila inválida
    if (col < 0 || col >= VGA_WIDTH) return;   // Columna inválida
    
    volatile unsigned short* video = (volatile unsigned short*) VGA_MEMORY;
    unsigned char color = vga_entry_color(fg, bg);
    
    int len = strlen(str);
    int pos = row * VGA_WIDTH + col;
    
    // Escribir solo lo que cabe
    for (int i = 0; i < len; i++) {
        // Verificar que no nos salgamos de la pantalla
        if ((col + i) >= VGA_WIDTH) break;
        if ((pos + i) >= (VGA_WIDTH * VGA_HEIGHT)) break;
        
        video[pos + i] = vga_entry(str[i], color);
    }
}

// Función opening COMPLETAMENTE REESCRITA y SEGURA
void opening() {
    clear_screen();
    
    // TODAS las coordenadas ahora son SEGURAS
    // Formato: print(texto, fila, columna, color_texto, color_fondo)
    // Filas: 0-24, Columnas: 0-79
    
    print("======================================", 2, 20, VGA_LIGHT_CYAN, VGA_BLACK);
    print("          ConwayOS v1.0              ", 3, 20, VGA_LIGHT_CYAN, VGA_BLACK);
    print("     Conway's Game of Life OS       ", 4, 20, VGA_WHITE, VGA_BLACK);
    print("======================================", 5, 20, VGA_LIGHT_CYAN, VGA_BLACK);
    
    print("Controls:", 8, 30, VGA_YELLOW, VGA_BLACK);
    print("SPACE : Toggle cell", 10, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("ENTER : Play/Pause", 11, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("C     : Clear grid", 12, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("R     : Random", 13, 25, VGA_LIGHT_GREY, VGA_BLACK);
    
    print("Patterns:", 15, 30, VGA_YELLOW, VGA_BLACK);
    print("G : Glider", 17, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("B : Blinker", 18, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("T : Toad", 19, 25, VGA_LIGHT_GREY, VGA_BLACK);
    
    print("Press any key to start...", 22, 27, VGA_GREEN, VGA_BLACK);
}