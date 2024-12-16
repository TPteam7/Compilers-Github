.data

	start_time: .word 0

	end_time: .word 0

	message: .asciiz "Execution time: "

	newline: .asciiz "

" 

	length: .word 0

	array: .space 20

	i: .word 0

	t28: .word 0

	fact: .word 0

	t30: .word 0

	t32: .word 0

	t33: .word 0

	printVar: .word 0

	t35: .word 0

	t37: .word 0

	t39: .word 0

	t40: .word 0

	mod: .word 0

	t42: .word 0

	t44: .word 0

	t45: .word 0

	nested: .word 0

	a: .word 0

	b: .word 0

	t0: .word 0

	sum: .word 0

	t2: .word 0

	temp: .word 0

	t4: .word 0

	doubleSum: .word 0

	t6: .word 0

	t7: .word 0

	c: .word 0

	t10: .word 0

	n: .word 0

	result: .word 0

	current: .word 0

	t13: .word 0

	t15: .word 0

	dividend: .word 0

	divisor: .word 0

	t16: .word 0

	test1: .word 0

	test2: .word 0

	t20: .word 0

	t21: .word 0

	t22: .word 0

	t24: .word 0

.text

.globl main

main:

	li $v0, 30

	syscall

	sw $v0, start_time

	li $t0, 5

	sw $t0, length

	la $t0, array

	li $t1, 0

	sw $t1, i

WhileStart3:

	lw $t1, i

	li $t2, 5

	slt $t3, $t1, $t2

	beq $t3, $zero, Continue3

	lw $a0, i

	jal factorial

	move $t1, $v0

	sw $t1, t28

	lw $t2, t28

	move $t1, $t2

	sw $t1, fact

	lw $t1, i

	lw $t2, fact

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	sw $t2, 0($t3)

	lw $t1, i

	li $t2, 1

	add $t3, $t1, $t2

	sw $t3, t30

	lw $t2, t30

	move $t1, $t2

	sw $t1, i

	j WhileStart3

Continue3:

	li $t1, 0

	sw $t1, i

WhileStart4:

	lw $t1, i

	li $t2, 5

	slt $t3, $t1, $t2

	beq $t3, $zero, Continue4

	lw $t1, i

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	lw $t2, 0($t3)

	sw $t2, t32

	lw $a0, t32

	jal printInt

	move $t1, $v0

	sw $t1, t33

	lw $t2, t33

	move $t1, $t2

	sw $t1, printVar

	lw $t1, i

	li $t2, 1

	add $t3, $t1, $t2

	sw $t3, t35

	lw $t2, t35

	move $t1, $t2

	sw $t1, i

	j WhileStart4

Continue4:

	li $t1, 4

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	lw $t2, 0($t3)

	sw $t2, t37

	lw $a0, t37

	li $t1, 2

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	lw $t2, 0($t3)

	sw $t2, t39

	lw $a1, t39

	jal modulus

	move $t1, $v0

	sw $t1, t40

	lw $t2, t40

	move $t1, $t2

	sw $t1, mod

	lw $t1, mod

	li $v0, 1

	move $a0, $t1

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $t1, 4

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	lw $t2, 0($t3)

	sw $t2, t42

	lw $a0, t42

	li $t1, 0

	mul $t1, $t1, 4

	add $t3, $t0, $t1

	lw $t2, 0($t3)

	sw $t2, t44

	lw $a1, t44

	jal nestedIfStatements

	move $t1, $v0

	sw $t1, t45

	lw $t2, t45

	move $t1, $t2

	sw $t1, nested

	la $a0, message

	li $v0, 4

	syscall

	li $v0, 30

	syscall

	sw $v0, end_time

	lw $t2, end_time

	lw $t3, start_time

	sub $t4, $t2, $t3

	mtc1 $t4, $f0

	li $t5, 1000

	mtc1 $t5, $f1

	cvt.s.w $f0, $f0

	cvt.s.w $f1, $f1

	div.s $f2, $f0, $f1

	li $v0, 2

	mov.s $f12, $f2

	syscall

	li $v0, 10

	syscall



add:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, a

	sw $a1, b

	lw $t1, a

	lw $t2, b

	add $t3, $t1, $t2

	sw $t3, t0

	lw $t2, t0

	move $t1, $t2

	sw $t1, sum

	lw $t1, sum

	li $t2, 5

	add $t3, $t1, $t2

	sw $t3, t2

	lw $t2, t2

	move $t1, $t2

	sw $t1, temp

	lw $t1, temp

	li $t2, 2

	mul $t3, $t1, $t2

	sw $t3, t4

	lw $t2, t4

	move $t1, $t2

	sw $t1, doubleSum

	lw $t1, doubleSum

	li $t2, 50

	sgt $t3, $t1, $t2

	bne $t3, $zero, L1

	j L2

L1:

	lw $t1, doubleSum

	li $v0, 1

	move $a0, $t1

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	j L0

L2:

	li $t1, 0

	sw $t1, t6

	lw $t1, t6

	li $v0, 1

	move $a0, $t1

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	j L0

L0:

	lw $v0, doubleSum



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra



subtract:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, a

	sw $a1, b

	lw $t1, a

	lw $t2, b

	subu $t3, $t1, $t2

	sw $t3, t7

	lw $t2, t7

	move $t1, $t2

	sw $t1, c

WhileStart0:

	lw $t1, c

	li $t2, 20

	slt $t3, $t1, $t2

	beq $t3, $zero, Continue0

	lw $t1, c

	li $v0, 1

	move $a0, $t1

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	lw $t1, c

	li $t2, 2

	add $t3, $t1, $t2

	sw $t3, t10

	lw $t2, t10

	move $t1, $t2

	sw $t1, c

	j WhileStart0

Continue0:

	lw $v0, c



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra



factorial:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, n

	li $t1, 1

	sw $t1, result

	lw $t2, n

	move $t1, $t2

	sw $t1, current

WhileStart1:

	lw $t1, current

	li $t2, 1

	sgt $t3, $t1, $t2

	beq $t3, $zero, Continue1

	lw $t1, result

	lw $t2, current

	mul $t3, $t1, $t2

	sw $t3, t13

	lw $t2, t13

	move $t1, $t2

	sw $t1, result

	lw $t1, current

	li $t2, 1

	subu $t3, $t1, $t2

	sw $t3, t15

	lw $t2, t15

	move $t1, $t2

	sw $t1, current

	j WhileStart1

Continue1:

	lw $v0, result



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra



modulus:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, dividend

	sw $a1, divisor

WhileStart2:

	lw $t1, dividend

	lw $t2, divisor

	sge $t3, $t1, $t2

	beq $t3, $zero, Continue2

	lw $t1, dividend

	lw $t2, divisor

	subu $t3, $t1, $t2

	sw $t3, t16

	lw $t2, t16

	move $t1, $t2

	sw $t1, dividend

	j WhileStart2

Continue2:

	lw $v0, dividend



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra



printInt:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, a

	lw $t1, a

	li $v0, 1

	move $a0, $t1

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 1



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra



nestedIfStatements:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, test1

	sw $a1, test2

	lw $t1, test1

	lw $t2, test2

	sgt $t3, $t1, $t2

	lw $t1, test1

	li $t2, 10

	sne $t4, $t1, $t2

	and $t1, $t3, $t4

	bne $t1, $zero, L4

	j L5

L4:

	lw $t1, test1

	li $t2, 2

	div $t1, $t2

	mflo $t3

	sw $t3, t20

	lw $t2, t20

	move $t1, $t2

	sw $t1, test1

	lw $t1, test1

	lw $t2, test2

	slt $t3, $t1, $t2

	bne $t3, $zero, L7

	j L8

L7:

	lw $a0, test1

	jal printInt

	move $t1, $v0

	sw $t1, t21

	lw $t2, t21

	move $t1, $t2

	sw $t1, printVar

	j L6

L8:

	lw $t1, test1

	lw $t2, test2

	sgt $t3, $t1, $t2

	bne $t3, $zero, L9

	j L10

L9:

	lw $a0, test2

	jal printInt

	move $t1, $v0

	sw $t1, t22

	lw $t2, t22

	move $t1, $t2

	sw $t1, printVar

	j L6

L10:

	li $a0, 0

	jal printInt

	move $t1, $v0

	sw $t1, t24

	lw $t2, t24

	move $t1, $t2

	sw $t1, printVar

	j L6

L6:

	j L3

L5:

	li $t1, 0

	sw $t1, printVar

	j L3

L3:

	li $v0, 0



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra
