// cideo Memory en modo texto VGA
#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

//colores VGA 
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

//crear atributo de color VGA
static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

//crear entrada VGA
static inline unsigned short vga_entry(unsigned char c, unsigned char color) {
    return (unsigned short) c | (unsigned short) color << 8;
}

//calcular longitud de string 
int strlen(const char* str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

void clear_screen(void) {
    unsigned short* video = (unsigned short*) VGA_MEMORY;
    unsigned char color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    unsigned short blank = vga_entry(' ', color);

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video[i] = blank;
    }
}

//escribir string en pantalla 
void print(const char* str, int row, int col, enum vga_color fg, enum vga_color bg) {
    unsigned short* video = (unsigned short*) VGA_MEMORY;
    unsigned char color = vga_entry_color(fg, bg);

    int len = strlen(str);
    int pos = row * VGA_WIDTH + col;

    for (int i = 0; i < len; i++) {
        video[pos + i] = vga_entry(str[i], color);
    }
}

//entry point del kernel
void kernel_main(void) {

    clear_screen();


    print("======================================", 5, 20, VGA_LIGHT_CYAN, VGA_BLACK);
    print("               ConwayOS        ", 6, 20, VGA_YELLOW, VGA_BLACK);
    print("======================================", 7, 20, VGA_LIGHT_CYAN, VGA_BLACK);

    print("Sistema operativo iniciado correctamente", 9, 20, VGA_LIGHT_GREEN, VGA_BLACK);
    print("Kernel version: 0.1.0", 11, 20, VGA_WHITE, VGA_BLACK);

    while(1) {
        __asm__ __volatile__("hlt");
    }
}
