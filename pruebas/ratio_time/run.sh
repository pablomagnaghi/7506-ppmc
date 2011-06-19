TMPDIR=/tmp/ppmc
PPMC=../../ppmc/ppmc
#FIXTURE=$(find ../../fixtures/text/0_light/* )
#FIXTURE=../../fixtures/text/1_medium/linux-1.3.100.tar
FIXTURE=../../fixtures/text/2_heavy/linux-2.4.37.tar ../../fixtures/text/2_heavy/linux-2.6.34.4.tar
mkdir $TMPDIR
for FILE in $FIXTURE; do
	echo "############################" >> report.txt
	echo >> report.txt
	TARGET=$(basename $FILE)
	SIZE=$(ls -l $FILE | cut -d" " -f 5)
	echo "file: $TARGET" >> report.txt
	TARGET=$TMPDIR/$TARGET.z
	echo >> report.txt
	cat $FILE > /dev/null
	for ORDER in 4 5; do
		echo "$FILE -> $ORDER"
		echo "order: $ORDER" >> report.txt
		/usr/bin/time -p -a -o report.txt $PPMC -c $FILE -s $TARGET -o $ORDER -b 2097152
		ZSIZE=$(ls -l $TARGET  | cut -d" " -f 5)
		RATIO=$(($ZSIZE * 1000 / $SIZE ))
		echo "size: $SIZE to $ZSIZE ratio: $RATIO" >> report.txt
		echo "------------------------" >> report.txt
	done
done



