# CRUDE
***Create/Read/Update/Delete/Exploit***

## WARNING:
This application is vulnerable by design. VM's only!

## Purpose
This is the 2017 Curtin University Cyber Crime and Security Enhanced Programming assignment. It is a small program which manages a simple employee database. It has the following vulnerabilities, by design.

* 1) Memory leaks
 * db_handler.c:10. ```filename``` is not freed if the file io is not successful. If you repeatedly enter invalid filenames, you will eventually fill up memory.
 * main.c:12 and db_handler.c:270. ```emp``` is freed before the ```exit_program``` funtion ends. The problem is that if the user exits, the exit is called before the free.
* 2
* 3
* 4
* 5
* 6

## Compilation

Type ```make all```.

## Run

Type ```./crude```

