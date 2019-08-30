#! /bin/bash
# Check that configure was not executed
if [ ! -f libtool ]; then
    ./autogen.sh
    ./configure --with-pthreads
fi
# Check that make was not executed
#if [ ! -d ./srx/.libs ]; then
#make 
#fi
make clean
make
