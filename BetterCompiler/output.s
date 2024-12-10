.data
	t1: .word 0
	t2: .word 0
	t3: .word 0
	t4: .word 0
	t5: .word 0
	a: .word 0
	t6: .word 0
	t7: .word 0
	t8: .word 0
	t9: .word 0
	t10: .word 0
	t11: .word 0
	t12: .word 0
	t13: .word 0
	t14: .word 0
	t15: .word 0
	t16: .word 0
	b: .word 0
	t0: .word 0
	c: .word 0
.text
.globl main
main:
	li $t0, 1
	sw $t0, t1
	li $t0, 1
	sw $t0, t2
	lw $t0, t1
	lw $t1, t2
	xor $t2, $t0, $t1
	lw $t0, goto
	lw $t1, (null)
L1:
	li $t0, 5
	sw $t0, t3
	lw $a0, t3
	li $t0, 3
	sw $t0, t4
	lw $a1, t4
	jal add
	move $t0, $v0
	sw $t0, t5
	lw $t1, t5
	move $t0, $t1
	sw $t0, a
	lw $t0, a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 2
	sw $t0, t6
	li $t0, 2
	sw $t0, t7
	lw $t0, t6
	lw $t1, t7
	xor $t3, $t0, $t1
	lw $t0, goto
	lw $t1, (null)
L3:
	li $t0, 6
	sw $t0, t8
	lw $t0, t8
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 2
	sw $t0, t9
	lw $t0, t9
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 1
	sw $t0, t10
	li $t0, 1
	sw $t0, t11
	lw $t0, t10
	lw $t1, t11
	xor $t4, $t0, $t1
	lw $t0, goto
	lw $t1, (null)
L6:
	li $t0, 5
	sw $t0, t12
	lw $t0, t12
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 2
	sw $t0, t13
	li $t0, 2
	sw $t0, t14
	lw $t0, t13
	lw $t1, t14
	xor $t5, $t0, $t1
	lw $t0, goto
	lw $t1, (null)
L8:
	li $t0, 6
	sw $t0, t15
	lw $t0, t15
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 2
	sw $t0, t16
	lw $t0, t16
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall

add:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $t0, a
	lw $t1, b
	add $t6, $t0, $t1
	sw $t6, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, c
	lw $v0, c

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra
