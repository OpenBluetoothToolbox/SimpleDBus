# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.X.X] - 2020-XX-XX
### Added
- BlueZ service can now pick a specific adapter.

### Changed
- The bytearray Holder representation gets its own specific print functionality.

### Fixed
- Message copy-assignments would cause memory leaks of the underlying DBus message object.
- Check if a message iterator has additional contents before attempting to fetch them.

## [1.0.0] - 2020-06-19
- First implementation!