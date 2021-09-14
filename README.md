# SimpleDBus
A simple C++ wrapper around DBus with a commercially-friendly licence.

**IMPORTANT NOTE**
This library is currently being split into two parts:
- The `SimpleDBus` library for all DBus-related functionality.
- The `SimpleBluez` library (formerly `bluezdbus`) for all Bluez-related functionality.

The last stable release of this library with both components together is [v1.2.0](https://github.com/OpenBluetoothToolbox/SimpleDBus/releases/tag/v1.2.0).

Say posted for further updates!

## Overview
SimpleDBus is a C++ low-level binding around DBus designed to be easy to integrate and use with commercial projects. 

If you want to use the library and need help. **Please reach out!**
You can find me at: `kevin at dewald dot me`

## Build
SimpleDBus should work on any Linux environment using DBus. To install the necessary dependencies on Debian-based systems, use the following command: `sudo apt install libdbus-1-dev`

A set of helper scripts are provided to simplify the process of building the
library, but are not required.

### Standalone build from source

```
cd <path-to-simpledbus>
mkdir build && cd build
cmake ..
make -j
sudo make install # Not available yet.
```

### Build as part of another project
If you want to add SimpleDBus to your project without any external dependencies, just clone the repository and link to it on your `CMakeLists.txt` file.

```
add_subdirectory(<path-to-simpledbus> ${CMAKE_BINARY_DIR}/simpledbus)
include_directories(${SIMPLEDBUS_INCLUDES})
```

### Build examples
```
cd <path-to-simpledbus>
mkdir build && cd build
cmake ../examples
make -j
```

## Known issues
- The handling of all externally exposed components with `std::shared_ptr` is not particularly safe in case the underlying object gets deleted by BlueZ, as the end user still has the capability to send requests to that deleted object. This will be addressed in a future release, but it's important for users of SimpleDBus to keep in mind.

## License
All components within this project that have not been bundled from external creators, are licensed under the terms of the [MIT Licence](LICENCE.md).
