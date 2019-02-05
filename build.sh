#!/bin/sh

LOG_COMPILE_PATH="build.log"
ARCHIVE_PATH="../archive/"

make distclean
qmake PCO_Labo_1.pro
make
