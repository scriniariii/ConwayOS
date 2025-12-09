#include <stdio.h>
#include "graphics.h"
#include "../utils/util.h"

static void delay(int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 100000; j++) {
            __asm__ __volatile__("nop");
        }
    }
}

//entry point del kernel
void kernel_main(void) {

    clear_screen();

    opening();
    delay(100000);
    clear_screen();

    while(1) {
        __asm__ __volatile__("hlt");
    }
}
