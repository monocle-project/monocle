This project is no longer actively maintained
=============================================

The network is no longer functional (no active bootstrapping nodes) and no one seems to be using it anyway, but if you are and wish to take over the development of this project feel free to fork it.

Monocle integration/staging tree
================================

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2015 Monocle Developers

What is Monocle?
----------------

Monocle is a merge mineable N-factor Scrypt coin

 - 2 minute block targets
 - subsidy decreases by ~3% every 10080 blocks
 - ~8.4 million total coins
 - 25 coins per block
 - 12 block retarget using BRNDF with a 180 block lookback

For more information, as well as an immediately useable, binary version of
the Monocle client sofware, see https://github.com/erkmos/monocle/releases.

License
-------

Monocle is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

The master branch is tested but is not guaranteed to be stable, please build
against release tags for production environments.

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Monocle
development team members simply pulls it.

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/erkmos/monocle/tags) are created
regularly to indicate new official, stable release versions of Monocle.

Testing
-------

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test monocle.pro
    make -f Makefile.test
    ./monocle-qt_test

