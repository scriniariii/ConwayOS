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
│   │   ├── game_life.c     # Conway
│   │   └── game_life.h
│   │
│   ├── drivers/
│   │   ├── keyboard.c      
│   │   └── keyboard.h
│   │
│   └── util/
│       ├── memset.c
│       ├── memcpy.c
│       └── types.h
│
├── build/              # Se genera al compilar
│   ├── kernel.o            
│   ├── boot.o
│   ├── graphics.o
|
├── iso/
│   ├── boot/
│   │   ├── grub/
│   │   │   └── grub.cfg    # Menú de GRUB
│   │   └── kernel.bin      # Kernel final (se genera al compilar)
│
├── Makefile
│
└── README.md               # Cómo compilar y ejecutar
</code></pre>
