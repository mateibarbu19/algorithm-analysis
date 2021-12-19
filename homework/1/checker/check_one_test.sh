#!/bin/bash
EXEC=$1
INPUT_DIR=$2
OUTPUT_DIR=$3
REF_DIR=$4
test_no=$5
TIMEOUT_TIME=$6
VALGRIND_TIMEOUT_TIME=$7

function timeout_test() {
    test_no=$1
    input_path="$INPUT_DIR/test"$test_no".in"
    out_path="$OUTPUT_DIR/test"$test_no".out"

    # Get the input and ref files for the current test
    timeout=$TIMEOUT_TIME

    (time timeout $timeout ./$EXEC $input_path $out_path) 2> time.err
    TEST_RESULT=$?
    echo $TEST_RESULT
}

function valgrind_test() {
    test_no=$1
    input_path="$INPUT_DIR/test"$test_no".in"
    out_path="$OUTPUT_DIR/test"$test_no".out"

    # Get the input and ref files for the current test
    timeout=$VALGRIND_TIMEOUT_TIME

    (time timeout $timeout valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 -q ./$EXEC $input_path $out_path) 2> time.err
    TEST_RESULT=$?
}

function check_valgrind_test() {
    test_no=$1

    echo -n "Test: $test_no ...................... "

    valgrind_test $test_no

    if [ "$TEST_RESULT" != "0" ]; then
        echo "DETECTED MEMORY LEAKS OR VALGRIND TIMEOUT"
       	tail -n 3 time.err
        rm -f time.err
        return
    else
        echo "NO MEMORY LEAKS"
        rm -f time.err
        return
    fi
}

# Check a single test and add the result to the total score. This function
# should _always_ receive a test number as the first and only argument
function check_test() {
    test_no=$1

    #check valgrind first
    if [ $VALGRIND_TIMEOUT_TIME -ne 0 ]; then
        check_valgrind_test $1
        if [ "$TEST_RESULT" != "0" ]; then
            echo "Test: $test_no ...................... FAILED BECAUSE OF VALGRIND"
            rm -f time.err
            # return
        fi
    fi


    timeout_test $test_no
    # Run the test, also consider the timeout
    # tail -n 3 time.err
    if [ "$TEST_RESULT" != "0" ]; then
        echo "Test: $test_no ...................... TIMEOUT [$timeout s]"
        tail -n 3 time.err
        rm -f time.err
		return
	fi

	out_path="$OUTPUT_DIR/test"$test_no".out"
	ref_path="$REF_DIR/test"$test_no".ok"

	echo -n "Test: $test_no ...................... "

	# Check the result
	diff -bB -i $ref_path $out_path 2>&1 1> my_diff

	if test $? -eq 0; then
	    echo "PASS"
	else
	    echo "FAILED"
	    echo "Diff result:"
	    cat my_diff | tail -n 10
	fi
}

check_test $test_no


# Clean up
rm -f my_diff
rm -f time.err

