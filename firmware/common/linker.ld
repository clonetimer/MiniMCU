OUTPUT_ARCH(riscv)
ENTRY(_start)
MEMORY {
 ROM (rx) : ORIGIN = 0x00000000, LENGTH = 64K
 RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}
PHDRS { text PT_LOAD FLAGS(5); data PT_LOAD FLAGS(6); }
SECTIONS {
 .text : ALIGN(4) { KEEP(*(.text.start)) *(.text .text.*) *(.rodata .rodata.*) } > ROM :text
 .data : ALIGN(16) { __data_start = .; *(.data .data.*) *(.sdata .sdata.*) __data_end = .; } > RAM :data
 PROVIDE(__global_pointer$ = __data_start + 0x800);
 .bss (NOLOAD) : ALIGN(16) { __bss_start = .; *(.bss .bss.*) *(.sbss .sbss.*) *(COMMON) . = ALIGN(16); __bss_end = .; } > RAM :data
 __stack_top = ORIGIN(RAM) + LENGTH(RAM);
 ASSERT(__bss_end <= __stack_top - 4096, "RAM exhausted: reserve a 4KiB startup stack")
 /DISCARD/ : { *(.eh_frame*) *(.comment) }
}
