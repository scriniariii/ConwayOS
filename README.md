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
│   │   ├── keyboard.c      # para agregar o matar celulas
│   │   └── keyboard.h
│   │
│   └── util/
│       ├── memset.c
│       ├── memcpy.c
│       └── types.h
│
├── build/
│   ├── kernel.o            # Se genera al compilar
│   ├── boot.o
│   ├── graphics.o
|
├── iso/
│   ├── boot/
│   │   ├── grub/
│   │   │   └── grub.cfg    # Menú de GRUB
│   │   └── kernel.bin      # Kernel final
│
├── Makefile
|-- build.sh # script para construir todo rapidamente
│
└── README.md               # Cómo compilar y ejecutar

