# virtual_time

## Introduction

It is simple proof of concept prototype project to hijack the `clock_gettime` or `gettimeofday` function in the `libc` library. The virtual time is stored in the shared memory, and the hijacked functions will return the virtual time instead of the real system time.
This can be useful for logsim replay and debugging, e.g. DDS replay.

## Build

```bash
pip install conan
conan profile detect # this command should be run only once
conan install . --build missing
cd build 
cmake .. -DCMAKE_TOOLCHAIN_FILE=Debug/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=install
make -j4
make install
```

## Usage

Hijack the `clock_gettime` or `gettimeofday` function in the `libc` library.

```bash
cd install

# update the virtual time, 1 hour per step(1 second)
LD_PRELOAD=./lib/libvirtual_time.so ./bin/virtual_time_push

# without hijacking
./bin/system_clock_now

# with hijacking
LD_PRELOAD=./lib/libvirtual_time.so ./bin/system_clock_now

# fetch the virtual time from shared memory
LD_PRELOAD=./lib/libvirtual_time.so ./bin/virtual_time_get
```

## References

- [Conan](https://conan.io/)
- [DYLD_INSERT_LIBRARIES DYLIB injection in macOS / OSX ](https://theevilbit.github.io/posts/dyld_insert_libraries_dylib_injection_in_macos_osx_deep_dive)
