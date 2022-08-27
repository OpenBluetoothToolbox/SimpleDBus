SimpleDBus
==========

A simple C++ wrapper around DBus with a commercially-friendly licence.

|Latest Documentation Status| |Code Coverage|

**THIS PROJECT HAS MOVED TO https://github.com/OpenBluetoothToolbox/SimpleBLE**

Overview
--------

SimpleDBus is a C++ low-level binding around libdbus conceived to be easy
to integrate with a licence friendly for use with commercial projects.

This library is designed to be an extremely minimalistic high-level
wrapper around libdbus, with most of the focus placed on proper
packing/unpacking of DBus data structures. It's primary intended
use case is by `SimpleBluez`_, a project to provide easy access to
the Bluez subsystem on Linux. SimpleDBus has also been designed to allow
first-class support for vendorization of all 3rd-party dependencies.

If you want to use SimpleDBus and need help. **Please do not hesitate to reach out!**

* Visit our `ReadTheDocs`_ page.
* Join our `Discord`_ server.
* Contact me: ``kevin at dewald dot me``

License
-------

All components within this project that have not been bundled from
external creators, are licensed under the terms of the `MIT Licence`_.

.. Links

.. _MIT Licence: LICENCE.md

.. _Discord: https://discord.gg/N9HqNEcvP3

.. _ReadTheDocs: https://simpledbus.readthedocs.io/en/latest/

.. _SimpleBluez: https://github.com/OpenBluetoothToolbox/SimpleBluez

.. |Latest Documentation Status| image:: https://readthedocs.org/projects/simpledbus/badge?version=latest
   :target: http://simpledbus.readthedocs.org/en/latest

.. |Code Coverage| image:: https://codecov.io/gh/OpenBluetoothToolbox/SimpleDBus/branch/master/graph/badge.svg?token=T0G4A78MAB
   :target: https://codecov.io/gh/OpenBluetoothToolbox/SimpleDBus
