# Compiler README

## Overview
This document provides an extensive guide to the compiler we built, including its purpose, capabilities, and how to use it effectively. The compiler supports a custom programming language with syntax inspired by C. It includes support for:

1. Arithmetic operations.
2. Control structures like conditional statements and loops.
3. Functions with variable declarations, parameters, and return values.
4. Arrays with indexed assignments.
5. TAC (Three-Address Code) generation for intermediate representation.

## Features

### 1. **Supported Syntax**
- **Variable Declarations:**
  ```c
  int x;
  int y = 10;
  ```

- **Arithmetic Operations:**
  ```c
  int sum = a + b;
  ```

- **Conditional Statements:**
  ```c
  if (x > y) {
      print(x);
  } else {
      print(y);
  }
  ```

- **Loops:**
  ```c
  while (i < 10) {
      i = i + 1;
  }
  ```

- **Functions:**
  ```c
  int add(int a, int b) {
      return a + b;
  }
  ```

- **Arrays:**
  ```c
  int array[5];
  array[0] = 1;
  ```

### 2. **Intermediate Representation**
The compiler generates TAC for all supported operations, including arithmetic, function calls, and control structures.

### 3. **Semantic Checks**
The compiler performs the following checks during semantic analysis:
- Variable declaration before use.
- Function parameter and return type compatibility.
- Array index bounds (at compile-time, if possible).
- Type mismatches.

### 4. **Error Handling**
The compiler provides clear error messages for syntax and semantic errors. Examples:
- **Undeclared variable:** `Error: Variable 'x' used before declaration.`
- **Type mismatch:** `Error: Type mismatch in assignment.`

## Example Code and Compilation

### Example Code
Here is an example of code written in your language:

```c
// Function to add two numbers
int add(int a, int b) {
    int sum = a + b;
    return sum;
}

// Main function
int main() {
    int x = 5;
    int y = 10;
    int result = add(x, y);
    print(result);
    return 0;
}
```

### Compilation Steps
1. **Parsing:** The compiler parses the code and builds an Abstract Syntax Tree (AST).
2. **Semantic Analysis:** The AST is analyzed for errors such as undeclared variables and type mismatches.
3. **TAC Generation:** The compiler translates the AST into TAC.
4. **Code Generation:** MIPS assembly code is generated for execution.

## Intermediate Representation (TAC)
The compiler converts code into TAC as an intermediate step. For example:

**Input Code:**
```c
int x = 1 + 2 * 3 - 5;
print(x);
```

**Generated TAC:**
```
t0 = 2 * 3
t1 = 1 + t0
t2 = t1 - 5
x = t2
print(x)
```

## MIPS Code Generation
The compiler generates MIPS assembly code from TAC. Example:

**TAC:**
```
t0 = 2 * 3
t1 = 1 + t0
t2 = t1 - 5
x = t2
print(x)
```

**MIPS Assembly:**
```
li $t0, 2
li $t1, 3
mul $t2, $t0, $t1
li $t3, 1
add $t4, $t3, $t2
li $t5, 5
sub $t6, $t4, $t5
sw $t6, x
lw $a0, x
li $v0, 1
syscall
```

## Compiler Design

### 1. **Lexical Analysis**
The compiler uses a lexer to tokenize the input code. Tokens include keywords, identifiers, operators, and literals.

### 2. **Parsing**
A parser processes tokens using a context-free grammar to build an Abstract Syntax Tree (AST).

### 3. **Semantic Analysis**
The AST is analyzed for:
- Variable scope.
- Type correctness.
- Array bounds.

### 4. **TAC Generation**
Each AST node is translated into TAC, a simple and efficient representation for code generation.

### 5. **Code Generation**
The final step is to translate TAC into MIPS assembly code for execution on a MIPS simulator.

## Installation and Usage

### Prerequisites
- C compiler (GCC).
- MIPS simulator (MARS).

### Build Instructions
1. Clone the repository.
   ```
   git clone https://github.com/TPteam7/Compilers-Github/tree/main/BetterCompiler
   cd BetterCompiler
   ```
2. Compile the compiler source code.
   ```
   make clean && time make all
   ```

### Running MIPS Code
1. Compile your program to generate MIPS assembly.
2. Open the MARS simulator.
   ```
   java -jar Mars4_5.jar
   ```
3. Open the generated `.s` file in MARS.
4. Run the simulation to execute the program.

## Future Improvements
- **Optimizations:** Implement optimization passes for TAC and MIPS code.
- **Advanced Features:** Add support for floating-point arithmetic, strings, and file I/O.
- **Error Recovery:** Enhance the parser to recover from syntax errors.
- **Debugging Tools:** Provide line-by-line execution tracing.

## Conclusion
This compiler serves as a robust foundation for building custom programs. It supports key features like functions, loops, and arrays while generating efficient intermediate and target code. With clear error messages and a focus on simplicity, this compiler is a practical tool for learning and developing applications in a custom language.

