=================================
SU<N> -- N by N complex matrices
=================================

This package implements complex N by N matrices in C++, where the size
N of the matrices is known at compile time. The name, SU<N>, comes
from the fact that they were initially developed to be used in a code
that deals with special unitary matrices, but they are in fact N by N
matrices.

Quick start guide
==================

Download the sources using git::

  git clone git://github.com/dhesse/sun.git

After that you might want to run some tests. Provided you have a
recent version of ``autoconf``, ``automake`` and ``libtool``
installed, you can generate a configure script like that::

  ./autogen.sh

The SU<N> test suite uses googletest_, which you need to download
separately. Let's assume you did so and we can find it in the
directory ``/path/to/gtest``. You can then configure the build::

  ./configure --with-gtest-srcdir=/path/to/gtest

Now all you have to do is check the test results::

  make check

The test code in the sub-directory ``testing`` will also give you some
idea about how to use the code.

.. _googletest: https://code.google.com/p/googletest/

Complex data type
==================

The SU<N> and Vec<N> classes use either ``std::complex<double>`` as
double type or a custom implementation in ``include/cplx.hpp``. The
latter is **strongly discouraged**. The STL type is way safer to use
and lightyears ahead of the primitive implementation included in this
package. We do however benefit from faster code using our
implementation, since it does not obey ISO and IEEE standards.

Copying
========

Copyright (C) 2013 Dirk Hesse

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
