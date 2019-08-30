#! /bin/bash

SRCDIR=../src
OUTPUTDIR=../Debug
LIG4CPP_BUILDDIR=../contrib/log4cpp/src/.libs/
LOG4CPP_PROPERTIES_FILE=log4cpp.properties
LOG4CPP_LIB_PATTERN=liblog4cpp.so*

# 1. copy log4cpp lib to output directory
rm $OUTPUTDIR/$LOG4CPP_LIB_PATTERN 2>&1 >/dev/null
cp $LIG4CPP_BUILDDIR/$LOG4CPP_LIB_PATTERN  $OUTPUTDIR 2>&1 >/dev/null
# 2. copy log4cpp.properties file to utput directory
if [ ! -f $OUTPUTDIR/$LOG4CPP_PROPERTIES_FILE ]; then
    cp $SRCDIR/$LOG4CPP_PROPERTIES_FILE $OUTPUTDIR/$LOG4CPP_PROPERTIES_FILE 2>&1 >/dev/null
fi
