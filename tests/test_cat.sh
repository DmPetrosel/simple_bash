#!/bin/bash
COUNT=0
COUNT_SUCCESS=0
COUNT_FAIL=0
PTH="../tests"
GPTH="."
file1="$PTH/hs.txt"
file2="$PTH/all_ascii.txt"
DSCR_CAT="TEST CAT "
CPTH="./s21_cat"

FLAGS=("" "-x" "-b" "--number-nonblank" "-e" "-E" "-n" "--number" "-s" "--squeeze-blank" "-t" "-T" )
for FLAG in "${FLAGS[@]}"
do
COUNT="$((COUNT+1))"
$CPTH $FLAG $file1 > s21cat_res.test
cat $FLAG $file1 > cat_res.test
if (diff s21cat_res.test cat_res.test); then 
    echo "$DSCR_CAT$COUNT: flag: $FLAG $file1 $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_CAT$COUNT: flag: $FLAG $file1 $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7
COUNT="$((COUNT+1))"
$CPTH $FLAG $file2 > s21cat_res.test
cat $FLAG $file2 > cat_res.test
if (diff s21cat_res.test cat_res.test); then 
    echo "$DSCR_CAT$COUNT: flag: $FLAG $file2 $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_CAT$COUNT: flag: $FLAG $file2 $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7

COUNT="$((COUNT+1))"
$CPTH $FLAG $file1 $file2 > s21cat_res.test
cat $FLAG $file1 $file2 > cat_res.test
if (diff s21cat_res.test cat_res.test); then 
    echo "$DSCR_CAT$COUNT: flag: $FLAG $file1 $file2 $(tput setaf 2)SUCCESS"
    COUNT_SUCCESS="$((COUNT_SUCCESS+1))"
else
    echo "$DSCR_CAT$COUNT: flag: $FLAG $file1 $file2 $(tput setaf 1)FAILURE"
    COUNT_FAIL="$((COUNT_FAIL+1))"
fi
tput setaf 7
done

echo "TOTAL TESTS: $COUNT"
echo "TOTAL $(tput setaf 2)SUCCESS: $COUNT_SUCCESS"
tput setaf 7
echo "TOTAL FAILURE $(tput setaf 1)FAILURE $COUNT_FAIL"
tput setaf 7

rm -rf cat_res.test s21cat_res.test