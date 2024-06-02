Development Workflow
====================

.. contents::
   :local:

Checkout and Initialization
---------------------------

.. code-block:: console

   $ cd ~/My-Projects                       # <--- or wherever you like
   $ git clone https://github.com/jfasch/2024-06-03.git
   $ cd 2024-06-03/
   $ git submodule init
   $ git submodule update

Build
-----

Create build directory for Intel architecture (``x86_64``)

.. code-block:: console

   $ mkdir ~/My-Builds/2024-06-03-x86_64         # <--- or wherever you like
   $ cd ~/My-Builds/2024-06-03-x86_64
   $ cmake ~/My-Projects/2024-06-03
   $ make

Test
----

.. code-block:: console

   $ pwd
   /home/jfasch/My-Builds/2024-06-03      # <--- or whatever you have chosen

.. code-block:: console

   $ ./tests/all-tests 
   Running main() from /home/jfasch/My-Projects/2024-06-03/googletest/googletest/src/gtest_main.cc
   [==========] Running 2 tests from 1 test suite.
   [----------] Global test environment set-up.
   [----------] 2 tests from demo
   [ RUN      ] demo.pass
   [       OK ] demo.pass (0 ms)
   [ RUN      ] demo.fail
   /home/jfasch/My-Projects/2024-06-03/tests/suite-demo.cpp:11: Failure
   Expected equality of these values:
     'X'
       Which is: 'X' (88, 0x58)
     'U'
       Which is: 'U' (85, 0x55)
   
   [  FAILED  ] demo.fail (0 ms)
   [----------] 2 tests from demo (0 ms total)
   
   [----------] Global test environment tear-down
   [==========] 2 tests from 1 test suite ran. (0 ms total)
   [  PASSED  ] 1 test.
   [  FAILED  ] 1 test, listed below:
   [  FAILED  ] demo.fail
   
    1 FAILED TEST
