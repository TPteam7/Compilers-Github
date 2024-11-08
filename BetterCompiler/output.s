.data
	t3: .word 0
	num: .word 0
	t5: .word 0
	subtraction: .word 0
	a: .word 0
	b: .word 0
	t0: .word 0
	diff: .word 0
.text
.globl main
main:
	li $t0, 10
	li $t1, 5
	subu $t2, $t0, $t1
	sw $t2, t3
	lw $t1, t3
	move $t0, $t1
	sw $t0, num
	lw $t0, num
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	lw $a0, num
	li $a1, 1
	jal sub
	move $t0, $v0
	sw $t0, t5
	lw $t1, t5
	move $t0, $t1
	sw $t0, subtraction
	lw $t0, subtraction
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall

sub:
	sw $a0, a
	sw $a1, b
	lw $t0, b
	lw $t1, a
	subu $t2, $t0, $t1
	sw $t2, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, diff
	lw $v0, diff
	jr $ra
