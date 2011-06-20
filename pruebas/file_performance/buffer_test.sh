TMPDIR=/tmp/ppmc
BUFFERS="1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304"
FIXTURE="../../fixtures/text/1_medium/* ../../fixtures/text/2_heavy/*"

mkdir $TMPDIR
for FILE in $FIXTURE; do
	echo "############################" >> report.txt
	echo >> report.txt
	FTARGET=$(basename $FILE)
	SIZE=$(ls -l $FILE | cut -d" " -f 5)
	echo "file: $FTARGET" >> report.txt
	echo >> report.txt
	cat $FILE > /dev/null
	for BUFFER in $BUFFERS; do
		TARGET=$TMPDIR/buffers
		echo "$FILE -> $BUFFER"
		echo "buffer: $BUFFER" >> report.txt
		/usr/bin/time -p -a -o report.txt ./run $FILE $TARGET $BUFFER
	done
done


