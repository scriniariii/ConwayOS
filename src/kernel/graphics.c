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

// crear atributo de color VGA
static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | (bg << 4);
}

// xrear entrada VGA (caracter + color)
static inline unsigned short vga_entry(unsigned char c, unsigned char color) {
    return (unsigned short)c | ((unsigned short)color << 8);
}

// calcular longitud de string
int strlen(const char* str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

// limpiar pantalla
void clear_screen(void) {
    volatile unsigned short* video = (volatile unsigned short*) VGA_MEMORY;
    unsigned char color = vga_entry_color(VGA_BLACK, VGA_BLACK);
    unsigned short blank = vga_entry(' ', color);

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video[i] = blank;
    }
}

// scribir string
void print(const char* str, int row, int col, enum vga_color fg, enum vga_color bg) {
    // verificar límites antes de hacer nada
    if (!str) return;  // String nulo
    if (row < 0 || row >= VGA_HEIGHT) return;  // fila invalida
    if (col < 0 || col >= VGA_WIDTH) return;   // columna invalida
    
    volatile unsigned short* video = (volatile unsigned short*) VGA_MEMORY;
    unsigned char color = vga_entry_color(fg, bg);
    
    int len = strlen(str);
    int pos = row * VGA_WIDTH + col;
    
    // escribir solo lo que entra
    for (int i = 0; i < len; i++) {
        // Verificar que no nos salgamos de la pantalla
        if ((col + i) >= VGA_WIDTH) break;
        if ((pos + i) >= (VGA_WIDTH * VGA_HEIGHT)) break;
        
        video[pos + i] = vga_entry(str[i], color);
    }
}

void opening() {
    clear_screen();
    
    // Formato: print(texto, fila, columna, color_texto, color_fondo)
    // Filas: 0-24, Columnas: 0-79

    print("  /$$$$$$                                                         ", 2, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print(" /$$__  $$                                                       ", 3, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("| $$  \\__/  /$$$$$$  /$$$$$$$  /$$  /$$  /$$  /$$$$$$  /$$   /$$|", 4, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("|| $$       /$$__  $$| $$__  $$| $$ | $$ | $$ |____  $$| $$  | $$|", 5, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("| $$      | $$  \\ $$| $$  \\ $$| $$ | $$ | $$  /$$$$$$$| $$  | $$|", 6, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("| $$    $$| $$  | $$| $$  | $$| $$ | $$ | $$ /$$__  $$| $$  | $$|", 7, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("|  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$/$$$$/|  $$$$$$$|  $$$$$$$|", 8, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print(" \\______/  \\______/ |__/  |__/ \\_____/\\___/  \\_______/ \\____  $$ ", 9, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("                                                       /$$  | $$                    ", 10, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("                                                      |  $$$$$$/                    ", 11, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    print("                                                       \\______/                     ", 12, 3, VGA_LIGHT_CYAN, VGA_BLACK);
    
    print("Conway's Game of Life OS (ConwayOS)       ", 14, 20, VGA_WHITE, VGA_BLACK);

    print("Controls:", 15, 30, VGA_YELLOW, VGA_BLACK);
    print("SPACE : Toggle cell", 16, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("ENTER : Play/Pause", 17, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("  C   : Clear grid", 18, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("  R   : Random", 19, 25, VGA_LIGHT_GREY, VGA_BLACK);
    print("LEFT CTRL TO LEAVE", 20, 25, VGA_RED, VGA_BLACK);
    
    print("Press any key to start...", 22, 25, VGA_GREEN, VGA_BLACK);
}
