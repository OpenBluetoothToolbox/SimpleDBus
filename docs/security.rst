Security
========

One key security feature of the library is it allows the user to specify
the URLs and tags of all internal dependencies, thus allowing compilation
from internal or secure sources without the risk of those getting compromised.

Vendorization
-------------
Currently, the following libraries are included as part of SimpleDBus, with 
the following CMake options available:

* `fmtlib`_

  * ``LIBFMT_VENDORIZE``: Enable vendorization of fmtlib. *(Default: True)*

  * ``LIBFMT_GIT_REPOSITORY``: The git repository to use for fmtlib.

  * ``LIBFMT_GIT_TAG``: The git tag to use for fmtlib. *(Default: v8.1.1)*

  * ``LIBFMT_LOCAL_PATH``: The local path to use for fmtlib. *(Default: None)*

.. Links

.. _fmtlib: https://github.com/fmtlib/fmt
