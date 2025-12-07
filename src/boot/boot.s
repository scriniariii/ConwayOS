.set ALIGN,    1<<0             # alinear módulos en límites de pagina
.set MEMINFO,  1<<1             # proporcionar mapa de memoria
.set FLAGS,    ALIGN | MEMINFO  # campo de flags
.set MAGIC,    0x1BADB002       # numero mágico
.set CHECKSUM, -(MAGIC + FLAGS) # checksum (debe sumar 0)

// DEBE estar en los primeros 8KB del archivo binario 
.section .multiboot.data, "aw"
.align 4
multiboot_header:
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

// reservar espacio para el stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
    .skip 16384  # 16 KB
stack_top:

// codigo de inici
.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:
    // configurar el stack
    movl $stack_top, %esp

    // reset EFLAGS
    pushl $0
    popf

    // llamar al kernel en C
    call kernel_main

    // si retorna, hacer halt infinito
    cli
1:  hlt
    jmp 1b

.size _start, . - _start
