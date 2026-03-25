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
This functions is used to return a line (a string ended by \n) from any given file descriptor. After each call, it returns the line after the one returned from the previous call.<br>I don't know what else to say about it... also, static variables are cool.<br>

&nbsp;
# INSTRUCTIONS
You have to create your main function first. In this main fuction, you will have to open a file descriptor (using the open() function), and then pass the file descriptor's number identifier to the get_next_line() function call, as such:
```c
get_next_line(fd);
```
**NB:** Note that fd has to be a positive integer ranging from 0 to 1024. You won't need that much files open anyway.

&nbsp;
# RESOURCES
- My brain
- C documentation from the man pages
- https://www.youtube.com/@PortfolioCourses
- https://www.youtube.com/watch?v=-Mt2FdJjVno&list=PLPqnnyLDYcuGXkdP_yK63cA-GSwdgb7vm

&nbsp;
# DETAILED EXPLANATION

`get_next_line()` works by maintaining a `static char *stash` that persists between calls to the function, acting as a buffer that accumulates raw data read from the file descriptor. Because it is static, it is initialized to `NULL` once and retains its value after the function returns, meaning leftover data from one call is still available on the next.

&nbsp;

On each call, if the stash does not already contain a newline character, the function enters a loop that repeatedly calls `read()` to fetch `BUFFER_SIZE` bytes at a time, appending each new chunk to the stash using `append()` — which allocates a fresh joined string, then frees both the old stash and the temporary buffer to avoid memory leaks. This loop continues until either a `\n` is found in the stash, meaning a complete line is available, or `read()` returns `0` signaling end of file, in which case the loop breaks immediately without corrupting the stash.

&nbsp;

Once a complete line is ready, `create_line()` allocates a new string and copies everything from the beginning of the stash up to and including the `\n`, null-terminating it to produce the return value. Then `store_remainder()` allocates another new string containing everything after the `\n`, the old stash is freed, and the stash pointer is updated to point to this remainder so the next call to `get_next_line()` starts with the leftover data already in place rather than reading from scratch.

&nbsp;

If the loop exits because `read()` returned `0` and no `\n` was found, the entire remaining stash is returned as the final line without a `\n`. The stash is then freed and set to `NULL`, so the subsequent call returns `NULL` to signal that the file has been fully read. The function returns the line including its `\n` in all normal cases, without it only when the file doesn't end with one, and `NULL` on completion or error.

&nbsp;

The bonus version replaces the single static pointer with a static array `static char *stash[OPEN_MAX]`, giving each file descriptor its own independent stash slot at `stash[fd]`. This allows the function to read from multiple file descriptors simultaneously without any interference between them, while still counting as a single static variable.

That's it.

&nbsp;

<div style="text-align: center;">
    <img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExY2U2ajI5ZTNhdmc5M2RleTVmZjMyNzY1M2Vlc3BidnNsd21zdHBoeSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/TKL99l61UBNnnQSx4o/giphy.gif" alt="Description" width="" height="300">
</div>

<div style="text-align: center;">
  <b style="font-size: 120px;">Thank You!</b>
</div>
