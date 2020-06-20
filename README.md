# SimpleDBus
A simple C++ wrapper around DBus with a commercial-friendly licence, plus some abstraction code and examples around Bluez as well.

## Overview
SimpleDBus is a C++ low-level binding around DBus designed to be easy to integrate and use even with commercial projects. On top of it, I've also coded a (partial) implementation of the Bluez bindings in order to control the Bluetooth peripherals from it.

## Installation
- Copy the `simpledbus` folder into your project.
- If you're going to use the BlueZ abstraction, you also need to copy the `bluezdbus` folder into your project as well.
- You need to link against `libdbus-1`. (The package is called `libdbus-1-dev` on Ubuntu.)

## Usage
- The current examples is all I have for now. :-P
- If you want to use the library and need help. **Please reach out!**

## Contributing
If you want to help, here is what's needed:
- The remaining functionality of the existing components.
- More documentation.
- More examples.
