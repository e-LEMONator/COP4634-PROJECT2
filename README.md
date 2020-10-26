# COP4634-PROJECT2
The second project for Systems and Networks I

Authors: Levi Shaffer and Josh Lemon

Date: 10/25/2020

Info: Course COP4634

### Included files:

* mt-collatz.cpp
* CollatzSpawner.hpp
* CollatzSpawner.cpp
* CollatzCalculator.hpp
* CollatzCalculator.cpp
* MAKEFILE
* README.md
* Project 2 MT Collatz Report.pdf
* Collatz Histogram.csv

### Compiling and running:

From the command line, run `make` and then `./mt-collatz`, followed by the following arguments:

```css
mt-collatz N T [-nolock]

    N - Range of numbers for which a Collatz sequence must be computed.
    T - the number of threads the program will create and launch.
    -nolock - disable locking, allowing for race conditions.
```

To clean up files after execution, run `make clean` and it will remove all `*.o` and `*.exe` files.<br/><br/>

## Summary:  
This application calculates a Collatz number sequence with the option of running in parallel threads and then prints out the Stopping Time for each sequence.

The application takes in the following parameters:

`N - The range of numbers for which a Collatz sequence should be calculated. (2-N)`

`T - the number of threads for the process to spawn to calculate the sequence in parallel`

`[-nolock] (optional) - disables global variable locking, which allows for race conditions`

`> [filename] (optional) - redirects the stdout output to a file for the frequency listing of Stopping Times from 1-1000`

`2> [filename] (optional) - redirects the stderr output to a file with the time it takes the process (in parallal or otherwise) to calculate the collatz number sequence`

From this data, you can generate a histogram of stopping time frequency as well as record the turnaround time for the process to finish execution.

## Problems Encountered:
TODO: Problems Encountered