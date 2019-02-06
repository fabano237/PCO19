#!/bin/sh

ARCHIVE_PATH="archive/"
BUILD_LOGS="build.log"

make distclean > /dev/null 2>&1

qmake PCO_Labo_2.pro > "$ARCHIVE_PATH$BUILD_LOGS" 2>&1
make -j9 > "$ARCHIVE_PATH$BUILD_LOGS" 2>&1
