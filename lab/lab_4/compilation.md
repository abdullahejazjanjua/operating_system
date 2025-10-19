# Pre-processor Step:
- Expands headers and macros in the `.c` file
- Replaces `#include` directives with actual header file contents
- Performs text replacement for macros (e.g., `#define X 10`)
- Output is stored in a `.i` file 

```bash
clang -E file.c -o file.i
```
# Compiler Step:
- Converts the preprocessed `.i` file into assembly code `.s`
- Generates assembly code that represents the C code

```bash
clang -S file.i
```

# Assembler Step:
- Translates assembly code `.s` into machine code `.o`
- Leaves address placeholders for external function calls
- Doesn't complain about unknown functions due to pre-processor step providing declarations

```bash
clang -c file.i
```

# Linker Step:
- Fills in the address placeholders for external function calls
- Resolves references to external libraries and object files
- Generates the final executable file

```bash
clang file.o -o file.out
```

