# glGraph

A 2d Graphing Calculator using Modern OpenGL

## Demo
https://user-images.githubusercontent.com/5031736/122145371-1c5d8400-ce23-11eb-9e6e-e537469c06df.mp4

## Information

- This has only been tested on Fedora 34, it should work on other OS's but I make no guarantees.  
- This uses C++17 features.
- Controls: WASD to move around, QE to zoom

## What can it do so far?

- Basic operations (+, -, *, /, ^)
- Order of operations (parentheses, etc)
- Functions: sin, cos, tan, sqrt
- Switch between radians and degrees
- Multiple lines, ability to change line color, and ability to remove lines

## Known issues

- floating point precision errors
- functions with undefined values (e.g. divides by 0 or goes to infinity) sometimes display strange behavior
- glLineWidth may not work on some (maybe all) versions of macOS because of limited GL_LINE_WIDTH_RANGE  
- program will crash if inputted equation is invalid

## Dependencies  

- OpenGL 3.3 core
- SDL2
- GLEW
- Dear ImGui  
