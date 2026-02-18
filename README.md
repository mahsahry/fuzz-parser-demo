# fuzz-parser-demo (AFL++ + ASan)

This is a small security demo that shows how fuzzing can discover memory-safety bugs in C code, how to confirm the issue with AddressSanitizer (ASan), and how to fix it safely.

## What is the project?
- `src/parser.c` contains a small parser for inputs like `key=value`.
- `fuzz/afl_harness.c` is a fuzzing harness that feeds arbitrary bytes into the parser.
- AFL++ generates many mutated inputs and checks if the program crashes.
- ASan provides a detailed crash report (stack-buffer-overflow, file, line).

## What bug did we find?
AFL++ found an input that caused a **stack buffer overflow** inside `parse_kv()`.

The root cause was copying attacker-controlled data into a fixed-size stack buffer without enforcing a maximum length:
- buffer: `char value[32]`
- unsafe copy (before fix): copying `vlen` bytes even when `vlen > 31`

ASan reported a `stack-buffer-overflow` pointing to the copy in `parse_kv()`.

## Build (instrumented for fuzzing + sanitizers)
Install tools (Ubuntu / WSL):
```bash
sudo apt update
sudo apt install -y afl++ clang
