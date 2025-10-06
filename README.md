# raySoundBoard
A simple soundboard implemented in c++ with RAYLIB and RAYGUI

v 0.01 - proof of concept edition
- copy sounds you'd like to use into the resource folder in the same directory as raySoundBoard
- write file paths directly into the .cpp file (or possibly the accompanying .h?)

todos:
- make data layer (probably .json for ease of use)
- make music player with seek, cross fade, LPF
- make releases with github actions for cross platform use
- include raylib and raygui libraries into src for enhanced portability
- work on design

**note: since there doesn't seem to be any zed functionality, it might be better to hard code 
**the sound effects buttons, since the dropdowns all get written over visually. Remove
**checkboxes entirely and simplify the implementation. 

the current implementation is made for LINUX

Dependencies (currently)
- raylib
- raygui
- gcc

once installed, you can compile using the following command:

g++ raySoundBoard.c -lraylib -lm -o raySoundBoard


