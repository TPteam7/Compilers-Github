    .data

msg:    .asciiz "Loop finished.\n"  # String to print after the loop



    .text

    .globl main



main:

    li $t0, 5            # Initialize $t0 to 5

    li $t1, 10            # Set $t1 to 0 (comparison value)

LoopStart:

    blt $t0, $t1, Continue  # If $t0 < $t1, exit the loop
    
    li $v0, 4             # System call for print string

    la $a0, msg           # Load address of the string

    syscall

    sub $t0, $t0, 1         # Decrement $t0

    j LoopStart             # Jump back to reevaluate the condition



# Code to execute after the loop

Continue:

    li $v0, 4             # System call for print string

    la $a0, msg           # Load address of the string

    syscall



# End program

li $v0, 10            # Exit system call

syscall
