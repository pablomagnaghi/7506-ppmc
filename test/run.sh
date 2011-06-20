#!/bin/sh

QUICKSTART="../fixtures/text/0_light/FileReader.cpp ../fixtures/binary/0_light/short_binary"
FIXTURE=$(find ../fixtures/text/0_light/* ../fixtures/text/1_medium/linux-1.3.100.tar ../fixtures/binary/0_light/*)
VALGRIND="../fixtures/binary/0_light/short_binary"
AI="../fixtures/binary/1_medium/*"

for ORDER in 1 ; do
  for FILE in $QUICKSTART; do
    TARGET=$(basename $FILE)
    ./ppmc -c $FILE -s test/tmp/$TARGET.z -o $ORDER
    ./ppmc -x test/tmp/$TARGET.z -s test/tmp/$TARGET.original
    cmp $FILE test/tmp/$TARGET.original && echo -n "." ||  ( echo "Failed $FILE" && exit 1 )
  done
done

for FILE in $AI; do
  TARGET=$(basename $FILE)
  ./ppmc -c $FILE -s test/tmp/$TARGET.z
  ./ppmc -x test/tmp/$TARGET.z -s test/tmp/$TARGET.original
  cmp $FILE test/tmp/$TARGET.original && echo -n "." ||  ( echo "Failed $FILE" && exit 1 )
done


for ORDER in 1 5; do
  for FILE in $FIXTURE; do
    TARGET=$(basename $FILE)
    ./ppmc -c $FILE -s test/tmp/$TARGET.z -o $ORDER
    ./ppmc -x test/tmp/$TARGET.z -s test/tmp/$TARGET.original
    cmp $FILE test/tmp/$TARGET.original && echo -n "." ||  ( echo "Failed $FILE" && exit 1 )
  done
done

# memory leaks
valgrind ./ppmc -c $VALGRIND -o 1 -s test/tmp/short_binary.z 2>&1 \
| grep -q -e "All heap blocks were freed -- no leaks are possible" && echo -n "." || ( echo "Fallo VALGRIND con orden 1" && exit 1 )

valgrind ./ppmc -c $VALGRIND -o 2 -s test/tmp/short_binary.z 2>&1 \
| grep -q -e "All heap blocks were freed -- no leaks are possible" && echo -n "." || ( echo "Fallo VALGRIND con orden 2 " && exit 1 )

valgrind ./ppmc -c $VALGRIND -o 3 -s test/tmp/short_binary.z 2>&1 \
| grep -q -e "All heap blocks were freed -- no leaks are possible" && echo -n "." || ( echo "Fallo VALGRIND con orden 3" && exit 1 )

echo
