<img src="assets/capture01.gif" width="400" alt="Render of europe map, lands are green, water blue and mountains whites">

# OpenGL Heightmap C++

Inspired from https://learnopengl.com/Guest-Articles/2021/Tessellation/Height-map

## Dependencies

 - SDL2
 - OpenGL, Glu
 - GLew
 - Glm

 Install using MSYS22

 ```
 pacman -S mingw-w64-x86_64-toolchain
 pacman -S mingw-w64-ucrt-x86_64-SDL2
 pacman -S mingw-w64-ucrt-x86_64-glew
 pacman -S mingw-w64-ucrt-x86_64-glm
 ```

## Run

Commands line to run it:
```
# Build with cmake
cmake --build c:/Users/Florian/Documents/picmid-dev/cpp_projects/test-cpp/build --config Debug --target all -j 10 --
# Run
build/PlanetViewer.exe
```
