# log.cpp
A tiny C++ logging library using {fmt}.


## Usage
**[log.cpp](src/log.cpp?raw=1)** and **[log.hpp](src/log.hpp?raw=1)** should be dropped
into an existing project and compiled along with it.

```cpp
#if defined(_WIN32)
   #define PATH_DELIM "\\"
#elif defined(__linux__)
   #define PATH_DELIM "/"
#endif

#include "logger.hpp"

int main(int argc, char **argv)
{
  // Set the path to log to
  std::string file_path = __FILE__ ;
  std::string src_path = file_path.substr(0, file_path.rfind(PATH_DELIM));
  std::string top_path = src_path.substr(0, src_path.rfind(PATH_DELIM));
  set_log_file((top_path + PATH_DELIM + "test.log").c_str());

  ...

  LOG_INFO("Batch option selected\n");
}  
```


> [!TIP]
> __For ANSI color usage in Windows use this reghack:__
> 
> In HKCU\Console create a DWORD named VirtualTerminalLevel 
> and set it to 0x1; then restart cmd.exe/powershell.exe

## License
This library is free software; you can redistribute it and/or modify it under
the terms of the MIT license. See [LICENSE](LICENSE) for details.
