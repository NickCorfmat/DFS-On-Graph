Nicolas Corfmat<br>
CruzID: ncorfmat<br>
Assignment: pa3

```
DESCRIPTION
``` 
This program implements a Graph ADT and runs Depth First Search on the graph created from vertices defined in a user-specified input file.

```
FILES
```
+ `List.h` Header file containing the interface for the List ADT.
+ `List.c` C file containing the List ADT.
+ `Graph.h` Header file containing the interface for the Graph ADT.
+ `Graph.c` C file containing the Graph ADT.
+ `GraphTest.c` C file containing code for testing the Graph ADT functions.
+ `FindComponents.c` Contains the main() function that implements Depth First Search.
+ `Makefile` Supports the compilation of all the .c programs in the pa3 directory.
+ `README.md` Contains information regarding the files in the pa3 directory and how to run them.

```
BUILD
``` 
To build, run `make` on the terminal command line within the pa3 assignment directory followed by one of the following: `FindComponents`, and/or `GraphTest`. This creates respective executable files which can then be run.
```
CLEAN
```
Running `make clean` will remove all the executable (.o) files from the pa3 assignment directory as well as other compiler-generated files.
```
RUNNING
```
To run, type `./FindComponents` followed by a space separated **input** and **output** text file.
```
NOTES
```
+ To keep track of time steps when performing Depth First Search, `time` was made a global variable in `Graph.c`.
+ To improve functionality from pa2's `Graph.c`, the function `addArc()` now checks for duplicate arcs.
