#!/bin/bash
VL="valgrind --tool=memcheck --leak-check=yes"
DSCR_CAT="TEST VALGRIND CAT "
COUNT=0
COUNT_SUCCESS=0
COUNT_FAIL=0
PTH="../tests"
FILE1="$PTH/hs.txt"
FILE2="$PTH/all_ascii.txt"
PATHC="../cat/s21_cat"

COUNT="$((COUNT+1))"
$VL $PATHC > /dev/null 2>&1
if [ $? -eq 0 ] ;then
  echo "$DSCR_CAT$COUNT: flag: $FLAG $FILE1 $(tput setaf 2)SUCCESS"
  COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$? $DSCR_CAT$COUNT: flag: $FLAG $FILE1 $(tput setaf 1)FAILURE"
    $VL $PATHC $FLAG $FILE2
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7

FLAGS=( "" "-x" "-b" "--number-nonblank" "-e" "-E" "-n" "--number" "-s" "--squeeze-blank" "-t" "-T" )
for FLAG in "${FLAGS[@]}"
do
COUNT="$((COUNT+1))"
$VL $PATHC $FLAG $FILE1 > /dev/null 2>&1
if [ $? -eq 0 ] ;then
  echo "$DSCR_CAT$COUNT: flag: $FLAG $FILE1 $(tput setaf 2)SUCCESS"
  COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$? $DSCR_CAT$COUNT: flag: $FLAG $FILE1 $(tput setaf 1)FAILURE"
    $VL $PATHC $FLAG $FILE2
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7

COUNT="$((COUNT+1))"
$VL $PATHC $FLAG $FILE1 $FILE2> /dev/null 2>&1
if [ $? -eq 0 ] ;then
  echo "$DSCR_CAT$COUNT: flag: $FLAG $FILE1 $FILE2 $(tput setaf 2)SUCCESS"
  COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$? $DSCR_CAT$COUNT: flag: $FLAG $FILE1 $FILE2 $(tput setaf 1)FAILURE"
    $VL $PATHC $FLAG $FILE2
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7
done

echo "TOTAL TESTS: $COUNT"
echo "TOTAL $(tput setaf 2)SUCCESS: $COUNT_SUCCESS"
tput setaf 7
echo "TOTAL FAILURE $(tput setaf 1)FAILURE $COUNT_FAIL"
tput setaf 7