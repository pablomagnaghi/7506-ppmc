TMPDIR=/tmp/ppmc
PPMC=../../../ppmc/ppmc
FIXTURE="run.sh ../../../ppmc/test/fixture/*cpp"
mkdir $TMPDIR
for FILE in $FIXTURE; do
	echo "############################" >> report.txt
	echo >> report.txt
	TARGET=$(basename $FILE)
	SIZE=$(ls -l $FILE | cut -d" " -f 5)
	echo "file: $TARGET" >> report.txt
	TARGET=$TMPDIR/$TARGET.z
	echo >> report.txt
	for ORDER in 1 2 ; do
		echo "order: $ORDER" >> report.txt
		/usr/bin/time -p -a -o report.txt $PPMC -c $FILE -s $TARGET -o $ORDER
		ZSIZE=$(ls -l $TARGET  | cut -d" " -f 5)
		RATIO=$(($ZSIZE * 1000 / $SIZE ))
		echo "size: $SIZE to $ZSIZE ratio: $RATIO" >> report.txt
		echo "------------------------" >> report.txt
	done
done



