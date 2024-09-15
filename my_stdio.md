# Custom I/O Functions Documentation (`my_stdio.c`)

## Overview

This document provides detailed information about a set of custom I/O functions implemented in `my_stdio.c`. These functions enable formatted output to standard input/output streams and include built-in input validation, error handling, and protection against buffer overflows to ensure robust and secure operation.

## Functions

### `printe(const char *error)`

**Purpose:**  
Outputs an error message to the standard error stream (`stderr`).

**Parameters:**
- `error`: A string containing the error message. If `NULL`, a default error message is printed.

**Behavior:**
- The function prints the error message followed by a newline.
- If `error` is `NULL`, a default message indicating a null pointer is printed.

### `prints(const char *str)`

**Purpose:**  
Outputs a string to the standard output stream (`stdout`).

**Parameters:**
- `str`: The string to be printed. If `NULL`, an error message is displayed.

**Behavior:**
- Prints the provided string to the output stream.
- If `str` is `NULL`, `printe` is called with an appropriate error message indicating that a null string was encountered.

### `printc(char ch)`

**Purpose:**  
Outputs a single character to the standard output stream.

**Parameters:**
- `ch`: The character to be printed. If `ch` is outside the range (0-127), an error message is displayed.

**Behavior:**
- Prints the character to `stdout`.
- If `ch` is not a valid ASCII character, `printe` is invoked with an error message indicating an invalid character.

### `printk(const char *fmt, ...)`

**Purpose:**  
Outputs a formatted string to the standard output stream.

**Parameters:**
- `fmt`: A format string containing text and format specifiers. If `NULL`, an error message is displayed.
- `...`: Additional arguments to be formatted based on the format specifiers in `fmt`.

**Behavior:**
- The function parses the format string and prints the formatted output. 
- Supported format specifiers include:
  - `%c`: Prints a single character.
  - `%s`: Prints a string.
  - `%d`: Prints an integer.
- If `fmt` is `NULL`, `printe` is called to handle the null format string error.
- If an unsupported format specifier is encountered, the function calls `printe` to report the issue.

## Example Usage

Below is an example demonstrating how to use the custom I/O functions defined in `my_stdio.c`:

```c
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);  // Disable output buffering for clarity in testing.

    printk("%s %d %c\n", "Hello, world", 44, 'c');
    printe("Null Exception");

    return 0;
}
```

In this example:
- `printk` is used to print a formatted string with a string (`%s`), an integer (`%d`), and a character (`%c`).
- `printe` is used to output an error message to `stderr`.

## Security Considerations

The custom I/O functions in `my_stdio.c` are designed with security in mind:
- **Input validation**: Each function checks the validity of input arguments (e.g., null pointers or invalid characters).
- **Buffer overflow protection**: The functions avoid buffer overflows by using fixed-size buffers and limiting the size of formatted strings.
- **Error handling**: Robust error handling is implemented for scenarios such as `NULL` inputs, invalid format specifiers, and out-of-range characters.

## Limitations

- The format handling in `printk` is limited to basic specifiers (`%c`, `%s`, `%d`). More complex specifiers, such as floating-point numbers or field width adjustments, are not supported.
- These functions, while secure and simple, do not offer the full functionality of standard library functions like `printf` or `fprintf`.
