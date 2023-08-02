
# Overview

This is a small project to develop some basic data structures in C. Currently, the following data structures are implemented:
- Array list (array_list.*)

# Organisation

The source code structure is shown below

```
Application
│-- main.c
│-- <module_name>.c
│-- <module_name>.h
│-- <module_name>_p.h
│-- README.md
│-- Makefile

```

| File                | Description |
| ---                 | --- |
| main.c              | The driver function which contains some examples and tests |
| <module_name>.c     | The module implementation |
| <module_name>.h     | The public header file |
| <module_name>_p.h   | The private header file |
| Makefile            | The makefile for building the code |
| README.md           | This readme file |


# Compilation
A Makefile is provided for compilation:
- For normal compilation: ``$ make``
- For debugging: ``$ make dbg``

The code has been tested using GCC version 11.3/Ubuntu 22.04

# Usage
Module usage information is provided in the public header files (``<module_name>.h``). 

Implementation details and notes are provided in the module implementation (``<module_name>.c``)

The compiled driver application can be executed using ``$ ./datastructs``. No input arguments are required. This runs the examples and tests in main.c

