# SnakeGame
Author: Ioana Cristescu, Andrew Brady

## Description
In this project we build our own computer in Logisim and program the Snake Game. <br />
We write an assembler that turns a file containing MIPS assembly into a file that contains binary encoded machine code. Then we load the machine code that we generate in the previous step into a simulated processor written in Logisim. <br />
Controller circuits for the keyboard and monitor that house and manipluate device registers associated with the keyboard and monitor are also added to the computer. Finally, we write a device drivers in asssembly to access the keyboard and monitor registers to read characters from the keyboard and display pixels on the terminal that represent the Snake Game.

## Direction for compiling:
To compile the program use the Makefile provided, type: Makefile <br /> <br />

To run executable: ./assemble [input.asm] [output.bin] <br />
&emsp;- ./assemble tron.asm tron.bin <br /> <br />

Download Logisim: https://sourceforge.net/projects/circuit/    <br /> <br />

Play the Snake Game: load the binary file tron.bin into the memory and input keyboard commands for the desired movement direction (the acceped inputs are 'w', 'a', 's', 'd'.

## Design Decisions:
### Project1
Project1 file plays the role of an assembler. Given an assembly file input.asm, it writes the assembled coresponding into output.bin. The assembly instructions handled are: add, addi, sub, mult, div, mflo, mfhi, sll, srl, lw, sw, slt, beq, bne, j, jal, jr, jalr, syscall, sgt, sge, sle, seq, sne, mov, li, bge, bgt, ble, blt, abs.

### Regfile
Regfile is a circuit in Logisim that facilitates reading from and writing to individual registers. A register file stores the contents of all the registers in a CPU, and allows you to read the value of two registers (per clock cycle) and write to one register (per clock cycle). It contains 31 real registers numbered 1-31 and one simulated register 0, which is hardcoded to always output 0 and is not a real register that can be written to.

### ALU
ALU is a circuit in Logisim that takes two 32 bit inputs, and outputs the result of some arithmetic computation on those inputs (addition, subtraction, multiplication, division, shift, comparison, equality, movefromhi, movefromlo).

### Control
Control is a circuit in Logisim that output a signal or selection wires to the register file/ALU that controls how data will “flow” and which registers, if any, will get written to.

### Memory
Memory is a circuit in Logism that allocates a random-access memory (RAM) that can be both read from and written to. It behaves like a large register file, except with only one data output instead of two. We use 16 bits for the address size, since we don't use more than 2^16 bytes of total stack memory. <br />
For lw instructions, the appropriate value in memory is accessed. For sw instructions, the appropriate value in memory is written to, like it would in a register file.

### InstructionHandling
InstructionHandling is a circuit in Logisim that serves as read-only memory (ROM) that stores the instructions output of the assembler.

###  CPU
CPU is a circuit in Logisim that interprets, processes and executes instructions, from the hardware and software programs running on the device. The CPU performs arithmetic, logic, and other operations to transform data input into more usable information output.

### KeyboardController
KeyboardController is a circuit in Logisim that handles the input received from the keyboard.

### RGBController
RGBController is a circuit in Logisim that handles the pixels that show up on the monitor based on a given keyboard input. 

### Snake Game

