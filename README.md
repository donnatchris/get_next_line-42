## AIM OF THE PROJECT
This project will not only allow you to add a very practical function to your collection but also introduce you to a surprising new element of programming in C: static variables.

Successive calls to your get_next_line() function should enable you to read the entire content of the text file referenced by the file descriptor, one line at a time.

The file get_next_line_utils.c will serve to add additional functions necessary for implementing your get_next_line().

Your function must return the line that has just been read.
If there is nothing more to read or an error occurs, it should return NULL.
Ensure that your function behaves correctly whether reading from a file or from standard input.
Important:
You must always return the line that has been read, followed by the \n that ends it, except when you have reached the end of the file and the file does not end with a \n.

The header file get_next_line.h must include, at a minimum, the prototype of the function.

## BONUS
Here are the bonuses to implement:

- Implement get_next_line() using only one static variable.
- Extend get_next_line() to handle multiple file descriptors (fd).
  
For example, if file descriptors 3, 4, and 5 are readable, it should be possible to read from each of them in turn without ever losing the content already read from any of the fds, and without returning the wrong line.
You should be able to call get_next_line() once with fd 3, then with fd 4, then fd 5, and then again with fd 3, again with fd 4, and so on.
