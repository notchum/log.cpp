# log.cpp
A tiny C++ logging library using [{fmt}](https://github.com/fmtlib/fmt)


## Usage
**[log.cpp](src/log.cpp?raw=1)** and **[log.hpp](src/log.hpp?raw=1)** should be dropped
into an existing project and compiled along with it. Provided are 5 function-like macros for logging:

```c
LOG_DEBUG(format, ...)
LOG_INFO(format, ...)
LOG_WARN(format, ...)
LOG_ERROR(format, ...)
LOG_FATAL(format, ...)
```

Along with a method for logging to file:
```cpp
#if defined(_WIN32)
   #define PATH_DELIM "\\"
#elif defined(__linux__)
   #define PATH_DELIM "/"
#endif

#include "log.hpp"

int main(int argc, char **argv) {
  // Set the path to log to
  std::string file_path = __FILE__ ;
  std::string src_path = file_path.substr(0, file_path.rfind(PATH_DELIM));
  std::string top_path = src_path.substr(0, src_path.rfind(PATH_DELIM));
  set_log_file((top_path + PATH_DELIM + "test.log").c_str());

  ...

  LOG_INFO("Successfully logging to test.log!\n");
}  
```

An example `CMakeLists.txt` with this repo and [{fmt}](https://github.com/fmtlib/fmt) both cloned to `lib/` in your project:
```cmake
  ...

  # configure {fmt}
  add_subdirectory(lib/fmt)
  
  # specify additional locations of header files
  include_directories(
    lib/log.cpp/src
  )
  
  # external libraries 
  set(lib
    lib/log.cpp/src/log.cpp lib/log.cpp/src/log.hpp
  )
  
  # source files
  set(src
    src/main.cpp
    ${lib}
  )
  
  # name of the .exe file, window flag and the list of things to compile
  add_executable(${PROJECT_NAME} ${src})
  
  # also tell CMake to link with the libraries from find_package
  # otherwise it'll think that you wanted to find those just for fun and won't link them
  target_link_libraries(
    ${PROJECT_NAME}
    fmt::fmt
  )
```


## Notes
> [!NOTE]
> __For ANSI color usage in Windows use this reghack:__
> 
> In HKCU\Console create a DWORD named VirtualTerminalLevel 
> and set it to 0x1; then restart cmd.exe/powershell.exe


## License
This library is free software; you can redistribute it and/or modify it under
the terms of the MIT license. See [LICENSE](LICENSE) for details.
