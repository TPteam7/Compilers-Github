.data
	t0: .word 0
	diff: .word 0
	t3: .word 0
.text
.globl main
main:
	lw $t0, a
	lw $t1, b
	subu $t2, $t0, $t1
	sw $t2, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, diff
	lw $t1, call
	move $t0, $t1
	sw $t0, t3
	li $v0, 10
	syscall

--------------------------
main:
	li $a0, 1
	li $a1, 2
	jal sub
	sw $v0, sum
	
	lw $a0, sum
	li $v0, 1
	syscall

	li $v0, 10
	syscall

sub:
	subu $t0, $a0, $a1
	move $v0, $t0
	jr $ra