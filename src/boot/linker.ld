ENTRY(_start)

SECTIONS
{
    /* cargar en 1MB direccion estandar para kernels */
    . = 1M;

    /* el header multiboot DEBE ir primero por alguna razon*/
    .multiboot.data : ALIGN(4K)
    {
        *(.multiboot.data)
    }

    .multiboot.text : ALIGN(4K)
    {
        *(.multiboot.text)
    }

    .text : ALIGN(4K)
    {
        *(.text)
    }

    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }

    .data : ALIGN(4K)
    {
        *(.data)
    }

    .bss : ALIGN(4K)
    {
        *(.bootstrap_stack)
        *(COMMON)
        *(.bss)
    }
}
