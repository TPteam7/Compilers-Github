.data

	arr: .space 20

	t4: .word 0

.text

.globl main

main:

	la $t0, arr

	li $t1, 3

	li $t2, 17

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	sw $t2, 0($t3)

	li $t1, 3

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	lw $t4, 0($t3)



	
	move $a0, $t4

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall
