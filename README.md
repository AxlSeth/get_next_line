*This project has been created as part of the 42 curriculum by seramaro*

<div style="text-align: center;">
    <img src="https://i.postimg.cc/YCMgPSjJ/line.png" alt="Description" width="" height="300">
    <br>
    <b style="font-size: 100px;">Get Next Line</b>
    <p style="font-size: 20px;">Reading a line from a file descriptor is way too tedious.</p>
</div>

&nbsp;

&nbsp;
# DESCRIPTION
`get_next_line(int fd)` reads from a file descriptor and returns the next line on each call.

- A **line** is the bytes up to and **including** the first `\n` found (if present).
- If EOF is reached and there is remaining data **without** a trailing `\n`, that remaining data is returned as the last line.
- When there is nothing left to read (or on error), the function returns `NULL`.

This repository includes:
- **Mandatory** version: uses a single static stash (`static char *stash`) → intended for **one fd at a time**.
- **Bonus** version: uses one stash per fd (`static char *stash[1024]`) → supports **multiple fds** interleaved.

&nbsp;
# BUFFER_SIZE
The function reads in chunks of `BUFFER_SIZE` bytes.

- If `BUFFER_SIZE` is not defined at compile time, it defaults to **7** (`#define BUFFER_SIZE 07`).
- You can override it when compiling with `-D BUFFER_SIZE=<value>`.

&nbsp;
# INSTRUCTIONS
You have to create your `main()` function first. In this `main()`, you will:
1) open a file descriptor (using `open()`),
2) call `get_next_line(fd)` until it returns `NULL`,
3) `free()` every returned line.

Example (mandatory version):
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int   fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Compile (example):
```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line.c get_next_line_utils.c main.c
```

Bonus version (example):
```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

**NB:** In the *bonus* version, `fd` must be in the range `0..1023` (the code uses `static char *stash[1024]`).

&nbsp;
# NOTES (based on this implementation)
- Mandatory: because it uses a single `static char *stash`, switching between different fds without finishing the first one will mix state.
- On EOF, the last line is returned even if it doesn’t end with `\n`.
- On `read()` returning `-1` (error), this implementation returns `NULL`.
- Returned strings are heap-allocated → you must `free()` them.

&nbsp;
# RESOURCES
- C documentation from the man pages (`read(2)`, `open(2)`, `close(2)`)
- https://www.youtube.com/@PortfolioCourses
- https://www.youtube.com/watch?v=-Mt2FdJjVno&list=PLPqnnyLDYcuGXkdP_yK63cA-GSwdgb7vm

&nbsp;
# DETAILED EXPLANATION
This implementation keeps unread data in a **static stash** between calls.

## Mandatory (`get_next_line.c`)
- Uses `static char *stash;`.
- First call creates an initial buffer with `create_buffer(fd)`.
- Then it keeps reading chunks (`create_buffer(fd)` → `read(fd, ..., BUFFER_SIZE)`) and appending them to the stash with `append()` until the stash contains a `\n` or `read()` hits EOF.
- Once a full line is available, it allocates a `line` of size `line_size(stash)` and copies that part with `ft_memmove()`.
- The remainder after the extracted line becomes the new stash (allocated, copied, old stash freed).

## Bonus (`get_next_line_bonus.c`)
The bonus version replaces the single static pointer with a static array `static char *stash[1024]`, giving each file descriptor its own independent stash at `stash[fd]`. This allows you to call `get_next_line()` on different fds without mixing their states.

That's it.

&nbsp;

<div style="text-align: center;">
    <img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExY2U2ajI5ZTNhdmc5M2RleTVmZjMyNzY1M2Vlc3BidnNsd21zdHBoeSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/TKL99l61UBNnnQSx4o/giphy.gif" alt="Description" width="" height="300">
</div>

<div style="text-align: center;">
  <b style="font-size: 120px;">Thank You!</b>
</div