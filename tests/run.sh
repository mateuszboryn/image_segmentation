#!/bin/bash

DATA_DIR=data
RESULTS_DIR=results
EXEC_FILE=../build/st

echo "======================================================"
echo "Cleaning and creating directories..."
echo "======================================================"
rm -rf "$RESULTS_DIR"
mkdir -p "$RESULTS_DIR"

for FILE in `ls "$DATA_DIR"`
do
	echo "    Creating directory $RESULTS_DIR/$FILE"
	mkdir "$RESULTS_DIR/$FILE"
done

echo "======================================================"
echo "Running tests..."
echo "======================================================"

ERROR=0
for FILE in `ls "$DATA_DIR"`
do
	echo "    Running test for file $RESULTS_DIR/$FILE"
	COMMAND="$EXEC_FILE -i \"$FILE\" -o \"$RESULTS_DIR/$FILE\""
	echo "    Command: $COMMAND"
	$COMMAND
	if [ "$?" != 0 ]; then
		ERROR=1
		break
	fi
done

if [ "$ERROR" = 0 ]; then
	echo "======================================================"
	echo "Running tests finished."
	echo "======================================================"
else
	echo "======================================================"
	echo "There were errors."
	echo "======================================================"
fi
