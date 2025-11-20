
## Building Debug

```
conan install . --build=missing -s build_type=Debug

cmake --preset debug

cmake --build --preset debug

```

## Building Release
```

conan install . --build=missing -s build_type=Release
cmake --preset release 
cmake --build --preset release
```
