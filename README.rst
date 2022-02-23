SimpleDBus
==========

A simple C++ wrapper around DBus with a commercially-friendly licence.

|Latest Documentation Status|

Overview
--------

SimpleDBus is a C++ low-level binding around DBus designed to be easy to
integrate and use with commercial projects.

This library is designed to be an extremely minimalistic high-level
wrapper around DBus, with most of the focus placed on proper
packing/unpacking of DBus data structures. It's primary intended use
case is by `SimpleBluez`_.

If you want to use the library and need help. **Please reach out!** You
can find me at: ``kevin at dewald dot me``

Build
-----

SimpleDBus should work on any Linux environment using DBus. To install
the necessary dependencies on Debian-based systems, use the following
command: ``sudo apt install libdbus-1-dev``

A set of helper scripts are provided to simplify the process of building
the library, but are not required.

Standalone build from source
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

   cd <path-to-simpledbus>
   mkdir build && cd build
   cmake .. -DSIMPLEDBUS_LOG_LEVEL=[VERBOSE_3|VERBOSE_2|VERBOSE_1|VERBOSE_0|DEBUG|INFO|WARNING|ERROR|FATAL]
   make -j
   sudo make install # Not available yet.

Build as part of another project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to add SimpleDBus to your project without any external
dependencies, just clone the repository and link to it on your
``CMakeLists.txt`` file.

::

   add_subdirectory(<path-to-simpledbus> ${CMAKE_BINARY_DIR}/simpledbus)
   include_directories(${SIMPLEDBUS_INCLUDES})

Build examples
~~~~~~~~~~~~~~

::

   cd <path-to-simpledbus>
   mkdir build && cd build
   cmake ../examples
   make -j

Build tests
~~~~~~~~~~~

To build and run unit and integration tests, the following packages are
required: ``sudo apt install libgtest-dev libgmock-dev python3-dev``

Address Sanitizer
^^^^^^^^^^^^^^^^^

In order to run tests with Address Sanitizer, CMake needs to be called
with the following option: ``-DSIMPLEDBUS_SANITIZE=Address``. It is also
important to set the environment variable ``PYTHONMALLOC=malloc`` to
prevent Python's memory allocator from triggering false positives.

Thread Sanitizer
^^^^^^^^^^^^^^^^

In order to run tests with Thread Sanitizer, CMake needs to be called
with the following option: ``-DSIMPLEDBUS_SANITIZE=Thread``.

Architecture
------------

The following notes provide an overview of the architecture of some of
the higher-level classes in the library, as to facilitate their
understanding.

Interface
~~~~~~~~~

-  In order to simplify the routing of messages, all interfaces are
   assumed to have properties, thus skipping the need to have a special
   implementation of org.freedesktop.DBus.Properties.
-  All properties are stored in the holder in which they came from. This
   is not the most efficient way of handling properties, but it is the
   one that minimizes the necessary code for children of the Interface
   class.

Proxy
~~~~~

-  Messages for org.freedesktop.DBus.Properties are automatically
   handled by the Proxy class.

Security
--------

One key security feature of the library is it allows the user to specify
the URLs and tags of all internal depe

.. _SimpleBluez: https://github.com/OpenBluetoothToolbox/SimpleBluez
.. |Latest Documentation Status| image:: https://readthedocs.org/projects/simpledbus/badge?version=latest
   :target: http://simpledbus.readthedocs.org/en/latest
