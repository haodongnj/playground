# virtual_time

## Introduction

This is a simple tool to replay messages from a file. It is of proof of concept prototype project.

## Build

```bash
pip install conan
conan install . -of build --build missing
cd build 
cmake ..
cmake --build .
```

## References

- [Conan](https://conan.io/)
- [DYLD_INSERT_LIBRARIES DYLIB injection in macOS / OSX ](https://theevilbit.github.io/posts/dyld_insert_libraries_dylib_injection_in_macos_osx_deep_dive)