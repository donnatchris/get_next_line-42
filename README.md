##### [🇫🇷 Version française](README.fr.md) / [🇬🇧 English version](README.md)

# PROJECT GET_NEXT_LINE FOR 42
By chdonnat (Christophe Donnat from 42 Perpignan, France)

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
  
For example, if file descriptors 3, 4, and 5 are readable, it should be possible to read from each of them in turn 
without ever losing the content already read from any of the fds, and without returning the wrong line.
You should be able to call get_next_line() once with fd 3, then with fd 4, then fd 5, and then again with fd 3, again with fd 4, and so on.

## DOCUMENTATION
### static variable in C

In C, a static variable is a variable that retains its value across multiple function calls.
When a variable is declared with the static keyword inside a function, its lifetime becomes the entire duration of the program's execution,
unlike a normal local variable that is created and destroyed each time the function is called.
However, its scope remains limited to the function in which it is defined, meaning it cannot be accessed outside of that function.
This makes static variables particularly useful for maintaining state or storing information that needs to persist between function calls.

Static variables can also be declared outside of functions, at the file level.
In this case, their scope is restricted to the file in which they are declared, preventing access from other files in the program.
This is useful for encapsulation, as it limits the visibility of variables to the module that defines them.
Overall, static variables are a powerful feature for managing state and improving modularity in C programming.
