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

Play the Snake Game: load the binary file tron.bin into the memory and input keyboard commands for the desired movement direction (the acceped inputs are 'w', 'a', 's', 'd'.

## Design Decisions:
