# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.X.X] - 2021-XX-XX
### Added
- Added function to request a list of all available adapters.
- Adapters now provide their address and their OS identifier.
- Adapters now provide another callback that notifies whenever a device is updated.
- Devices can now be queried for their list of services and characteristics.

### Fixed
- Made project compilation settings private.

## [1.1.1] - 2021-02-20
### Added
- Implemented move and copy constructors for `SimpleDBus::Message`.

### Changed
- Pointers to DBus connection and error objects within `SimpleDBus::Connection` were made private.
- All library targets are now compiled with maximum optimization options.
- Changed code formatting settings.

### Fixed
- `SimpleDBus::Holder` array representation would only print the last element of the array.
- `InterfacesRemoved` signal would unnecessarily delete an object.


## [1.1.0] - 2021-02-08
### Added
- BluezService can now pick a specific adapter.
- Basic logging capabilities.
- Added `Alias` and `RSSI` fields to BluezDevice. *(Thank you xloem!)*
- BluezAdapter, BluezDevice and BluezGattService now properly handle removal events from DBus.

### Changed
- The bytearray Holder representation gets its own specific print functionality.
- Adapter1, Device1 and GattCharacteristic1 DBus objects now run some basic validations before issuing commands to BlueZ.
- GattCharacteristic1.ValueChanged callback parameters are now passed by value.
- Modified the project directory structure.
- Updated the project documentation.
- Minor modification to the Logger format structure to ease readability.

### Fixed
- Message copy-assignments would cause memory leaks of the underlying DBus message object.
- Check if a message iterator has additional contents before attempting to fetch them.
- Message iterator initialization would not work with older DBus headers. *(Thank you xloem!)*
- Recursion deadlock when attempting to print logs. *(Thank you xloem!)*
- Proper cleanup of internal string buffer of the logging module. *(Thank you xloem!)*
- Holder objects not clearing their state during copy-assignment. *(Thank you xloem!)*


## [1.0.0] - 2020-06-19
- First implementation!