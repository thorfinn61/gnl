# get_next_line — 100/100 ✅

## Overview

`get_next_line` implements line-by-line file reading in C. Each call returns **exactly one line**, regardless of file size or buffer length. It emphasizes understanding of **static variables**, **dynamic memory**, partial reads with `read()`, and building strings safely.

---

## Features

###  Supported behavior

* Returns **one full line per call** (including `
  ` if present)
* Works with **any `BUFFER_SIZE > 0`**
* Correct handling of:

  * End of file (EOF)
  * Empty files
  * Files without a trailing newline
  * Read errors
* Fully norm-compliant and leak-free

###  Internal logic

* Uses a **static char*** to store leftover data between calls
* Reads data in chunks and appends it to a persistent buffer
* Extracts the next line
* Cleans leftover data for the next call

---

## Usage

### Compilation

No Makefile is provided. Compile manually with your own main:

```sh
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

### Example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int   fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Project Structure

```
get_next_line/
├── get_next_line.c
├── get_next_line.h
└── get_next_line_utils.c
```

---

## Results

| Category     | Result      |
| ------------ | ----------- |
| Moulinette   | 100/100     |
| Norminette   | Passed      |
| Memory leaks | None        |
