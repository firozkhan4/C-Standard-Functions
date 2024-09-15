#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Error handling function
void printe(const char *error) {
    const char *error_msg = "[-] Error: ";
    const char newline = '\n';

    if (error == NULL) {
        error = "NULL pointer in printe";
    }

    write(2, error_msg, strlen(error_msg));
    write(2, error, strlen(error));
    write(2, &newline, 1);
}

// String printing function
void prints(const char *str) {
    if (str == NULL) {
        printe("NULL string");
        return;
    }

    write(1, str, strlen(str));
}

// Character printing function
void printc(char ch) {
    if (ch < 0 || ch > 127) {
        printe("Unknown character");
        return;
    }

    write(1, &ch, 1);
}

// Custom printk function
void printk(const char *fmt, ...) {
    if (fmt == NULL) {
        printe("NULL format string");
        return;
    }

    va_list args;
    va_start(args, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] != '%' && fmt[i] != '\\') {
            printc(fmt[i]);
            continue;
        }
        if (fmt[i] == '\\') {
            char c = (char)'\n';
            printc(c);
            i++;
            continue;
        }

        i++;

        switch (fmt[i]) {
            case 'c': {
                char c = (char)va_arg(args, int);
                if (c < 0 || c > 127) {
                    printe("Unknown character");
                    break;
                }
                printc(c);
                break;
            }
            case 's': {
                char *s = va_arg(args, char *);
                if (s == NULL) {
                    printe("NULL string");
                    break;
                }
                prints(s);
                break;
            }
            case 'd': {
                int val = va_arg(args, int);
                char buffer[12];
                sprintf(buffer, "%d", val);
                prints(buffer);
                break;
            }
            default:
                printe("Unknown format specifier");
                break;
        }
    }

    va_end(args);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    printk("%s %d %c\n", "Hello ,world", 44, 'c');
    printe("NULL Expection");

    return 0;
}
