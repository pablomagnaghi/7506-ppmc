TMPDIR=/tmp/ppmc
PPMC=../../ppmc/ppmc
ORDERS="3 4 5"
#FIXTURE=$(find ../../fixtures/text/0_light/* )
#FIXTURE=../../fixtures/text/1_medium/linux-1.3.100.tar
#FIXTURE="../../fixtures/text/2_heavy/linux-2.4.37.tar ../../fixtures/text/2_heavy/linux-2.6.34.4.tar"
#FIXTURE="../../fixtures/mixed/*"
FIXTURE="../../fixtures/binary/1_medium/*"
mkdir $TMPDIR
for FILE in $FIXTURE; do
	echo "############################" >> report.txt
	echo >> report.txt
	FTARGET=$(basename $FILE)
	SIZE=$(ls -l $FILE | cut -d" " -f 5)
	echo "file: $FTARGET" >> report.txt
	echo >> report.txt
	cat $FILE > /dev/null
	for ORDER in $ORDERS; do
		TARGET=$TMPDIR/$FTARGET.$ORDER.z
		echo "$FILE -> $ORDER"
		echo "order: $ORDER" >> report.txt
		/usr/bin/time -p -a -o report.txt $PPMC -c $FILE -s $TARGET -o $ORDER -b 2097152
		ZSIZE=$(ls -l $TARGET  | cut -d" " -f 5)
		RATIO=$(($ZSIZE * 1000 / $SIZE ))
		echo "size: $SIZE to $ZSIZE ratio: $RATIO" >> report.txt
		echo "------------------------" >> report.txt
	done
done


