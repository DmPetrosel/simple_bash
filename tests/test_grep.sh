#!/bin/bash
PTH="../tests"
GPTH="."
FILE1="$PTH/hs.txt"
FILE2="$PTH/history.txt"
FILE3="$PTH/sfdafadsf.txt"
PTRN="patterns.txt"
OPTIONS=("I" "-x word" "adsafasdfasdf" "KEep -i" "I -n" "word -c" "word -o" "-f $PTH/$PTRN" "-l word" "-e I -e word -e asdfasdf" "-e irrational" "-f $PTRN -e irrational" "-h word" "-s word" "-e irrational" "-i -e irrational" "-v -e irrational" "-c -e irrational" "-l -e irrational" "-n -e irrational" "-h -e irrational" "-s -e irrational" "-f $PTRN -e irrational" "-o -e irrational" "-i word" "-v -i word" "-c -i word" "-l -i word" "-n -i word" "-h -i word" "-s -i word" "-f $PTH/$PTRN -i word" "-o -i word" "-v word" "-c -v word" "-l -v word" "-n -v word" "-h -v word" "-s -v word" "-f $PTH/$PTRN  -v word" "-o -v word" "-c word" "-l -c word" "-n -c word" "-h -c word" "-s -c word" "-f $PTH/$PTRN -c word" "-o -c word" " -l word" "-n -l word" "-h -l word" "-s -l word" "-f $PTH/$PTRN -l word" "-o -l word" "-n word" "-h -n word" "-s -n word" "-f $PTH/$PTRN -n word" "-o -n word" "-h word" "-s -h word" "-f $PTH/$PTRN -h" "-o -h word" "-s word" "-f $PTH/$PTRN -s" "-o -s word" "-f $PTH/$PTRN" "-o -f $PTH/$PTRN" "-o word")
COUNT=0
COUNT_SUCCESS=0
COUNT_FAIL=0
DSCR_GREP="TEST GREP "
for OPT in "${OPTIONS[@]}"
do
COUNT=$((COUNT+1))
$GPTH"/s21_grep" $OPT $FILE1 > s21_grep.test
grep $OPT $FILE1 > grep.test
if diff s21_grep.test grep.test; then 
    echo "$DSCR_GREP$COUNT: $OPT $FILE1: $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_GREP$COUNT: $OPT $FILE1: $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7

COUNT=$((COUNT+1))
$GPTH"/s21_grep" $OPT $FILE2 > s21_grep.test
grep $OPT $FILE2 > grep.test
if diff s21_grep.test grep.test; then 
    echo "$DSCR_GREP$COUNT: $OPT $FILE2: $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_GREP$COUNT: $OPT $FILE2: $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7

COUNT=$((COUNT+1))
$GPTH"/s21_grep" $OPT $FILE1 $FILE2 > s21_grep.test
grep $OPT $FILE1 $FILE2 > grep.test
if diff s21_grep.test grep.test; then 
    echo "$DSCR_GREP$COUNT: $OPT $FILE1 $FILE2: $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_GREP$COUNT: $OPT $FILE1 $FILE2: $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7

COUNT=$((COUNT+1))
$GPTH"/s21_grep" $OPT $FILE1 $FILE3 $FILE2 > s21_grep.test
grep $OPT $FILE1 $FILE3 $FILE2 > grep.test
if diff s21_grep.test grep.test; then 
    echo "$DSCR_GREP$COUNT: $OPT $FILE1 $FILE3 $FILE2: $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_GREP$COUNT: $OPT $FILE1 $FILE3 $FILE2: $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7
done

echo "TOTAL TESTS: $COUNT"
echo "TOTAL $(tput setaf 2)SUCCESS: $COUNT_SUCCESS"
tput setaf 7
echo "TOTAL FAILURE $(tput setaf 1)FAILURE $COUNT_FAIL"
tput setaf 7

rm -rf s21_grep.test grep.test