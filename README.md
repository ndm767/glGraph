# glGraph

A 2d Graphing Calculator using Modern OpenGL

## Information

- This has only been tested on Fedora 34, it should work on other OS's but I make no guarantees.  
- This uses C++17 features.
- Controls: WASD to move around, QE to zoom

## What can it do so far?

- Basic operations (+, -, *, /, ^)
- Order of operations (parentheses, etc)
- Functions: sin, cos, tan, sqrt
- Multiple lines and ability to change line color

## Known issues

- floating point errors
- functions with undefined values (e.g. divides by 0 or goes to infinity) sometimes display strange behavior
- glLineWidth may not work on some (maybe all) versions of macOS because of limited GL_LINE_WIDTH_RANGE  
- expressions inside of functions may cause crashes

## Dependencies  

- OpenGL 3.3 core
- SDL2
- GLEW
- Dear ImGui  
