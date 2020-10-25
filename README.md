# COP4634-PROJECT2
The second project for Systems and Networks I

Authors: Levi Shaffer and Josh Lemon

Date: 10/25/2020

Info: Course COP4634

Included files:

* myshell.cpp
* parse.cpp
* parse.hpp
* param.cpp
* param.hpp
* execHandler.cpp
* execHandler.hpp
* MAKEFILE
* README.md

Compiling and running:
From the command line, run `make` and then `./myshell`, and then provide your shell arguments to the shell utility prompt: `$$$`

To exit the shell, from the prompt `$$$` type `exit` and the shell will stop.

To clean up files after execution, run `make clean` and it will remove all `*.o` and `*.exe` files.

Summary:  
Start with user input loop and take the user input string and send to `Parser` object. We then replace all tab, newline, and carriage return characters into space characters within the `parseString()` method and then feed that into the `strtok()` function delimited by spaces to split our arguments. Then the `tokensToParam()` method will convert those tokenized strings into acceptable types to be read into the parameter vector `parms.argumentVector` which is assigned to the `param` object.  
Inside the `main()` loop we check if we are in debug mode, and if we are, then we print the `param` object to the console using `stdout`. If we parse an `exit` argument, we then free the memory and exit the process.

We then built from the argument parser functionality of part 1 and created the `ExecutionHandler` class to utilize the `fork()` method to run multiple instances of a computational process. For the number of parallel processed specified in the second argument passed through the shell, we `fork()` the parent process to spawn *`argumentVector[1]`* number of child processes while the parent process then waits for the children to finish. We accomplish the wait process by having the parent sit in a `while()` loop and checking the status of the child processes to continue when they are exited.

The children, in the meantime, take the argument vector from the parser and pass it to the called program using the `execv()` method. This will allow a more computationally intensive application, such as prime number generation, to be solved in parallel allowing for faster completion.

The children process also handle input and output redirection, allowing for the following two cases. For input redirection, it will take an input text file and pass it to the called program, to be utilized for input however it is designed to do so. In the case of output redirection, it will take console messages and print them to a series of output files `output`*`n`* where *`n`* is the number of the child spawned processes that creates the output file.