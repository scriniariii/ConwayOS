# ConwayOS - OS for playing Conway's Game of Life

<pre><code>
ConwayOS/
│
├── src/
│   ├── boot/
│   │   ├── boot.s          # Entry point + multiboot header
│   │   └── linker.ld       # Script de linking para el kernel
│   │
│   ├── kernel/
│   │   ├── kernel.c        # Punto de entrada del kernel
│   │   ├── graphics.c      # Funciones de video
│   │   ├── graphics.h
│   │   ├── conway.c     # Conway
│   │   └── conway.h
│   │
│   ├── drivers/
│   │   ├── keyboard.c      
│   │   └── keyboard.h
│   │
│   └── util/
│       ├── memset.c
│       ├── memcpy.c
│       └── types.h
├── iso/
│   ├── boot/
│   │   ├── grub/
│   │   │   └── grub.cfg    # Menú de GRUB
│
└── Makefile
</code></pre>
