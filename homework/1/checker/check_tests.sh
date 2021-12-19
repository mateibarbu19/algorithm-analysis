#!/bin/bash
EXEC=$1
INPUT_DIR=$2
OUTPUT_DIR=$3
REF_DIR=$4
START_TEST=$5
END_TEST=$6

if test ! -x "$INPUT_DIR"; then
    echo Input folder missing.
    exit 1
fi

if test ! -x "$REF_DIR"; then
    echo "Reference folder missing."
    exit 1
fi

rm -rf "$OUTPUT_DIR" 2> /dev/null
mkdir "$OUTPUT_DIR" 2> /dev/null

# Check if the the exec exist
if test ! -x "$EXEC"; then
    echo "Executable file missing."
    exit 1
fi

for i in $(seq -s " " $START_TEST 1 $END_TEST); do
    if test ! -e "$INPUT_DIR/test$i.in"; then
        echo Input "$INPUT_DIR/test$i.in" missing
        exit 1
    fi
    if test ! -e "$REF_DIR/test$i.ok"; then
        echo Reference "$REF_DIR/test$i.ok" missing
        exit 1
    fi
    ./checker/check_one_test.sh $EXEC $INPUT_DIR $OUTPUT_DIR $REF_DIR $i 2 0
done

# Clean up
rm -f my_diff
rm -f time.err