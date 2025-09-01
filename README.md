# 🛠️ Custom Compiler in C++ (BL → x86-64)

This project implements a **complete compiler** for a custom toy programming language called **BL** (Basic Language).  
The compiler is written in **C++** and produces **x86-64 assembly**, which is then assembled and linked into a native executable using `nasm` and `ld`.

---

## 📖 Overview

The compiler follows the **classic compilation pipeline**:

1. **Lexical Analysis (Tokenizer)**  
   Converts raw source code into a sequence of tokens (keywords, identifiers, numbers, operators, etc.).  
   → Implemented in [`tokenization.hpp`](tokenization.hpp).

2. **Parsing (Syntax Analysis)**  
   Builds an **Abstract Syntax Tree (AST)** from the token stream according to the grammar rules.  
   → Implemented in [`parser.hpp`](parser.hpp).

3. **Code Generation**  
   Traverses the AST and generates **x86-64 assembly** instructions.  
   → Implemented in [`generation.hpp`](generation.hpp).

4. **Assembly & Linking**  
   The compiler writes assembly to `out.asm`, then runs:  
   - `nasm` → converts assembly into object code  
   - `ld` → links into an executable  
   - finally runs the program (`./out`)  

---

## 📂 File Structure

- **`main.cpp`** → Compiler driver (entry point).  
- **`tokenization.hpp`** → Lexical analysis (tokenizer).  
- **`parser.hpp`** → Syntax analysis (AST builder).  
- **`generation.hpp`** → Code generation (x86-64 assembly).  
- **`arena.hpp`** → Arena allocator for fast memory management.  

---

## 📝 The BL Language

BL is a **minimal imperative language** with:

- **Data Type**: Only 64-bit signed integers.  
- **Comments**:  
  - `//` → single line  
  - `/* ... */` → multi-line  
- **Statements** (end with `;`):  
  - Variable declaration: `let x = 42;`  
  - Assignment: `x = x + 5;`  
  - `exit(expr);` → terminate program with exit code  
  - `print HelloWorld;` → print a word (identifiers only, not strings)  

- **Expressions**:  
  - Integers, identifiers, parentheses  
  - Operators: `+ - * /` (with correct precedence)

- **Control Flow**:  
  - `if (...) { ... } elif (...) { ... } else { ... }`  
  - `while (...) { ... }`  

- **Scoping**:  
  - `{ ... }` creates block scope for variables  

---

## 🚀 Example Program

```c
// File: example.bl

let count = 10;
let total = 0;

// Sum numbers from 1 to 'count'
while (count) {
    total = total + count;
    count = count - 1;
}

// total = 55, exit code will be 5
exit(total / 11);
````

Running this will exit with code `5`.

---

## ⚙️ How to Build & Run

### 1. Clone the Repository

```bash
git clone https://github.com/subratabiswas1/custom-compiler.git
cd custom-compiler
```

### 2. Build the Compiler

```bash
g++ -std=c++20 main.cpp -o basic
```

### 3. Compile a `.bl` Program

```bash
./basic.out ../example.bl
```

This will:

* Generate `out.asm`
* Assemble & link into `out`
* Run the program (`./out`)

### 4. Check Exit Code

```bash
./out
echo $?
```

---

## ⚡ Implementation Highlights

* **Arena Allocator** → efficient AST memory management.
* **Pratt Parser** → clean handling of operator precedence.
* **Direct Assembly Output** → generates raw x86-64 instructions.
* **Scope Management** → automatic cleanup of stack variables at end of `{}`.

---

## 🔮 Future Work

* Add string literals & real `print` function.
* Support functions & user-defined procedures.
* Add error reporting with line/column info.
