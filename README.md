# Ioquake3 with QTCore

The project is divided into two parts.

### Part 1 located in the quake.creator file:
 - Compiles ioquake3, ioq3ded and render libraries

### Part 2 located in the quake.pro file:
 - Contains and compiles 3 subprojects:
 - cgame  (client side)
 - qagame (server side)
 - ui     (interface)

All files are compiling into directory: build/debug
From there the quake executable can be launched

### !!!      DO NOT IMPORT PROJECT        !!!
### !!! JUST OPEN .PRO AND .CREATOR FILES !!!

# Project tasks

 - [ ] Port project to C++
   - [ ] C++ `main ioquake`
   - [ ] C++ `lib renderer`
   - [X] C++ `lib qagame`
   - [X] C++ `lib cgame`
   - [ ] C++ `lib ui`
- [ ] Implement QTCore into project
