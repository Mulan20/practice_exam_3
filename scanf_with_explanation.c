/*
 * FT_SCANF
 *
 * A simplified implementation of scanf.
 * Supported format specifiers:
 *   %d → integer
 *   %s → string (stops at whitespace)
 *   %c → single character
 */

#include <stdio.h>      // FILE, stdin, fgetc, ungetc, ferror
#include <stdarg.h>     // va_list, va_start, va_arg, va_end
#include <ctype.h>      // isspace, isdigit

/* ------------------------------------------------------------ */
/* Skip whitespace characters in the input stream               */
/* ------------------------------------------------------------ */
int match_space(FILE *f)
{
    int ch = fgetc(f);              // Read one character from the file

    if (ch == EOF && ferror(f))     // If EOF and a file error occurred
        return -1;                  // Signal error

    while (ch != EOF)               // Loop until EOF
    {
        if (!isspace(ch))           // If character is NOT whitespace
        {
            ungetc(ch, f);          // Put it back into the stream
            break;                  // Stop skipping
        }
        ch = fgetc(f);              // Read next character
    }

    if (ferror(f))                  // Check for file error
        return -1;

    return 1;                       // Success
}

/* ------------------------------------------------------------ */
/* Match a literal character from the input                     */
/* ------------------------------------------------------------ */
int match_char(FILE *f, char c)
{
    int ch = fgetc(f);              // Read one character

    if (ch == c)                    // If it matches expected character
        return 1;                   // Success

    if (ch != EOF)                  // If it does not match
        ungetc(ch, f);              // Put character back

    return -1;                      // Failure
}

/* ------------------------------------------------------------ */
/* Handle %c conversion                                         */
/* Reads exactly one character (no whitespace skipping)         */
/* ------------------------------------------------------------ */
int scan_char(FILE *f, va_list ap)
{
    int ch = fgetc(f);              // Read one character
    char *cp = va_arg(ap, char *);  // Get pointer to char argument

    if (ch == EOF)                  // If EOF
        return -1;

    *cp = (char)ch;                 // Store character
    return 1;                       // One successful conversion
}

/* ------------------------------------------------------------ */
/* Handle %d conversion (integer)                               */
/* ------------------------------------------------------------ */
int scan_int(FILE *f, va_list ap)
{
    int sign = 1;                   // Sign of the number
    int value = 0;                  // Accumulated integer value
    int ch = fgetc(f);              // Read first character
    int *ip = va_arg(ap, int *);    // Get pointer to int argument
    int count = 0;                  // Count digits read

    if (ch == EOF)                  // If EOF
        return -1;

    /* Skip leading whitespace */
    while (isspace(ch))
        ch = fgetc(f);

    /* Handle optional sign */
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    else if (ch == '+')
    {
        ch = fgetc(f);
    }

    /* First non-space must be a digit */
    if (!isdigit(ch))
    {
        ungetc(ch, f);              // Put back invalid character
        return -1;
    }

    /* Read digits */
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0'); // Build number
        count++;
        ch = fgetc(f);
    }

    if (ch != EOF)                  // Put back first non-digit
        ungetc(ch, f);

    if (count == 0)                 // No digits read
        return -1;

    *ip = value * sign;             // Store result
    return 1;
}

/* ------------------------------------------------------------ */
/* Handle %s conversion (string)                                */
/* ------------------------------------------------------------ */
int scan_string(FILE *f, va_list ap)
{
    int ch = fgetc(f);              // Read first character
    char *sp = va_arg(ap, char *);  // Get pointer to string buffer
    int i = 0;                      // String index

    /* Skip leading whitespace */
    while (ch != EOF && isspace(ch))
        ch = fgetc(f);

    if (ch == EOF)                  // If EOF after skipping spaces
        return -1;

    /* Read characters until whitespace */
    do
    {
        sp[i++] = ch;               // Store character
        ch = fgetc(f);
    } while (ch != EOF && !isspace(ch));

    sp[i] = '\0';                   // Null-terminate string

    if (ch != EOF)                  // Put back whitespace character
        ungetc(ch, f);

    if (i == 0)                     // Empty string
        return -1;

    return 1;
}

/* ------------------------------------------------------------ */
/* Dispatch conversion based on format specifier                */
/* ------------------------------------------------------------ */
int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)               // Look at current format character
    {
        case 'c':
            return scan_char(f, ap);

        case 'd':
            match_space(f);         // %d skips whitespace
            return scan_int(f, ap);

        case 's':
            match_space(f);         // %s skips whitespace
            return scan_string(f, ap);

        case '\0':
            return -1;

        default:
            return -1;              // Unsupported specifier
    }
}

/* ------------------------------------------------------------ */
/* Core scanf logic                                             */
/* ------------------------------------------------------------ */
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;                  // Number of successful conversions

    int c = fgetc(f);               // Check if input exists
    if (c == EOF)
        return EOF;
    ungetc(c, f);                   // Put character back

    while (*format)                 // Loop through format string
    {
        if (*format == '%')         // Conversion detected
        {
            format++;               // Move to specifier
            if (match_conv(f, &format, ap) != 1)
                break;              // Stop on conversion failure
            nconv++;                // Count successful conversion
        }
        else if (isspace(*format))  // Whitespace in format
        {
            if (match_space(f) == -1)
                break;
        }
        else                        // Literal character
        {
            if (match_char(f, *format) != 1)
                break;
        }
        format++;                   // Move to next format character
    }

    if (ferror(f))                  // File error
        return EOF;

    return nconv;                   // Return number of conversions
}

/* ------------------------------------------------------------ */
/* Public scanf-like wrapper                                    */
/* ------------------------------------------------------------ */
int ft_scanf(const char *format, ...)
{
    va_list ap;                     // Variable argument list
    int ret;

    va_start(ap, format);           // Initialize argument list
    ret = ft_vfscanf(stdin, format, ap); // Call core function
    va_end(ap);                     // Clean up

    return ret;
}

