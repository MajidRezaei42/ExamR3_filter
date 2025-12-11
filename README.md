# Filter

A C program that reads from stdin and replaces all occurrences of a given pattern with asterisks (`*`).

## Description

This program mimics the behavior of `sed 's/pattern/****/g'`, replacing every occurrence of a specified string with asterisks of equal length.

```bash
# Example
echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc
# Output: ***defaaa***de******d***
```

## Compilation

```bash
gcc -Wall -Wextra -Werror -o filter filter.c
```

## Usage

```bash
./filter <pattern>
```

| Argument | Description |
|----------|-------------|
| `pattern` | The string to be replaced with asterisks |

## Examples

```bash
# Replace "abc" with "***"
$ echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
***defaaa***de******d***$

# Replace "ababc" with "*****"
$ echo 'ababcabababc' | ./filter ababc | cat -e
*****ab*****$

# Works like sed
$ ./filter bonjour
# Equivalent to: sed 's/bonjour/*******/g'
```

## Error Handling

| Condition | Behavior |
|-----------|----------|
| No arguments | Returns 1 |
| Empty argument | Returns 1 |
| Multiple arguments | Returns 1 |
| Read error | Prints "Error: \<message\>" to stderr, returns 1 |
| Memory allocation error | Prints "Error: \<message\>" to stderr, returns 1 |

## Algorithm

The program uses a two-phase approach:

1. **Read Phase**: Reads all input from stdin into a dynamically allocated buffer using `realloc()` to grow the buffer as needed.

2. **Filter Phase**: Scans the buffer character by character, comparing against the pattern. When a match is found, outputs asterisks; otherwise, outputs the original character.

```
Input:  "ababcabababc"
Pattern: "ababc"

Scan:   [ababc]abababc  → Match! Output: *****
        ababc[a]bababc  → No match, output: a
        ababca[b]ababc  → No match, output: b
        ababcab[ababc]  → Match! Output: *****

Result: "*****ab*****"
```

## Allowed Functions

- `read`, `write`
- `strlen`, `memmem`, `memmove`
- `malloc`, `calloc`, `realloc`, `free`
- `printf`, `fprintf`
- `stdout`, `stderr`, `perror`

## File Structure

```
.
├── filter.c    # Main source file
└── README.md   # This file
```

## Author

**arezaei** - 42 Luxembourg

## License

This project is part of the 42 school curriculum.
