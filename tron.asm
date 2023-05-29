#Tron game in asm
label_syscall:
    beq $v0, $0, main

    addi $t5, $0, 10
    beq $v0, $t5, syscall10
    addi $t5, $0, 12
    beq $v0, $t5, syscall12
    addi $t5, $0, 18
    beq $v0, $t5, syscall18
 
    j errorYay #should never be reached

syscall10:
    j syscall10

syscall12:
    lw $t3, 64($0)

    beq $t3, $0, endifKeypress
    ifKeypress:
        lw $v0, 80($0)

    sw $0, 64($0)

    endifKeypress:

    jr $k0

syscall18: 
    sw $a0, 128($0)
    sw $a1, 144($0)
    sw $a2, 160($0)
    addi $t1, $0, 1
    sw $t1, 176($0)

    jr $k0


errorYay:
    addi $t4, $0, 1
    j errorYay

main: 

addi $t1, $0, 1 #store 1 to monitor write 
sw $t1, 44($0)

#array address A[i][j] is $sp + 64 * i + j
addi $sp, $sp, -16384

#s0 is xcoord
#s1 is ycoord
#s2 is xdirection
#s3 is ydirection

addi $s0, $0, 0
addi $s1, $0, 0
addi $s2, $0, 1
addi $s3, $0, 0
addi $s4, $0, 256 #color of the tron
addi $s5, $0, 64


while:


    addi $v0, $0, 12
    syscall
    addi $t0, $0, 119 #code for 'w'
    
    bne $v0, $t0, endifW
    ifW:

        addi $s2, $0, 0
        addi $s3, $0, -1

    endifW:

    addi $t0, $0, 97 #code for 'a'

    bne $v0, $t0, endifA


    ifA:

        addi $s2, $0, -1
        addi $s3, $0, 0

    endifA:

    addi $t0, $0, 100 #code for 'd'

    bne $v0, $t0, endifD


    ifD:

        addi $s2, $0, 1
        addi $s3, $0, 0
    
    endifD:

    addi $t0, $0, 115 #code for 's'

    bne $v0, $t0, endifS

    ifS:

        addi $s2, $0, 0
        addi $s3, $0, 1

    endifS:

    add $s0, $s0, $s2
    add $s1, $s1, $s3

    sll $t0, $s0, 6 #multiply xcoord by 64
    add $t0, $t0, $s1 #t0 = 64 * s0 + s1
    add $t0, $t0, $sp #add the stack pointer to this
    sll $t0, $t0, 2 #multiply by 4!
    lw $t2, 0($t0) #load the array value
    addi $t1, $0, 1

    beq $t2, $t1, endgame #if that spot already visited, then end

    slt $t2, $s0, $0 #if xcoord less than zero we end (going off of map)
    beq $t2, $t1, endgame

    sge $t2, $s0, $s5 #if xcoord >= 64 we end (going off of map)
    beq $t2, $t1, endgame

    slt $t2, $s1, $0 #if ycoord less than zero we end (going off of map)
    beq $t2, $t1, endgame

    sge $t2, $s1, $s5 #if ycoord >= 64 we end (going off of map)
    beq $t2, $t1, endgame
    


    sw $t1, 0($t0)
    addi $v0, $0, 18
    add $a0, $0, $s0
    add $a1, $0, $s1
    add $a2, $0, $s4
    syscall



    j while



endgame:
    addi $sp, $sp, 16384 #return stack pointer to neutral

    addi $v0, $0, 10
    syscall