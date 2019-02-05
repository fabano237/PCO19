#!/bin/sh

LOG_RUN_PATH="run.log"
ARCHIVE_PATH="./archive/"

echo "======== Run no $1: $2 =========" | tee -a $ARCHIVE_PATH$LOG_RUN_PATH
case $1 in
[0-1])
./PCO_Labo_2 | tee -a $ARCHIVE_PATH$LOG_RUN_PATH
;;
[2-3])
./PCO_Labo_2 | tee -a $ARCHIVE_PATH$LOG_RUN_PATH
;;
esac
