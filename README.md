# SimpleDBus
A simple C++ wrapper around DBus with a commercially-friendly licence, plus some abstraction code and examples around Bluez as well.

## Overview
SimpleDBus is a C++ low-level binding around DBus designed to be easy to integrate and use with commercial projects. On top of it, there is a partial implementation of BlueZ bindings to enable the control of Bluetooth peripherals.

I've also coded a (partial) implementation of the Bluez DBus bindings in order to control the Bluetooth peripherals.

If you want to use the library and need help. **Please reach out!**
You can find me at: `kevin at dewald dot me`

## Build
SimpleDBus should work on any Linux environment using DBus. To install the necessary dependencies on Debian-based systems, use the following command: `sudo apt install libdbus-1-dev`

You can find scripts for all these

### Standalone build from source

```
cd <source-root>
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
cd <source-root>
mkdir build && cd build
cmake ../examples
make -j
```

## More information
- You can find the official documentation for BlueZ in [this link](https://git.kernel.org/pub/scm/bluetooth/bluez.git/plain/doc/gatt-api.txt).

## Contributing
If you want to help, here is what's needed:
- The remaining functionality of the existing components.
- Errors are currently not being caught and surfaced up.
- More documentation.
- More examples.
- Logging
