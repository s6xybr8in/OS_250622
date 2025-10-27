# 32-bit OS Build Project

This project is an exploration into understanding the x86 computer system and operating systems by building a simple 32-bit OS from scratch.

## Tech Stack

*   **Compiler:** GCC
*   **Assembler:** NASM
*   **Emulator:** QEMU (qemu-system-x86_64)

## Project Phases

The project is divided into several phases, each building upon the last:

### Phase 1: Bootloader
- Create a basic bootloader that can be loaded by the BIOS.

### Phase 2: Protected Mode
- Read a sector from the disk and load it into memory.
- Transition the CPU from 16-bit real mode to 32-bit protected mode.

### Phase 3: C Kernel
- Develop a simple kernel in C.
- Load and execute the C kernel after entering protected mode.

### Phase 4: Interrupt Handling
- Implement interrupt handling mechanisms:
    - **PIC (Programmable Interrupt Controller):** Configure the PIC to manage hardware interrupts.
    - **IDT (Interrupt Descriptor Table):** Set up the IDT to define interrupt service routines.
    - **ISR (Interrupt Service Routine):** Write basic ISRs to handle interrupts.

### Phase 5: Keyboard Input
- Implement an ISR for keyboard interrupts to handle user input.