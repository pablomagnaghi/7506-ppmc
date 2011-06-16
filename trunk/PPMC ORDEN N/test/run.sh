#!/bin/sh

valgrind ./ppmc -c test/fixture/short_binary -s test/tmp/short_binary.z 2>&1 \
| grep -q -e "All heap blocks were freed -- no leaks are possible" && echo -n "." || echo "Failed VALGRIND" && exit 1

for FILE in test/fixture/*; do
  TARGET=$(basename $FILE)
  ./ppmc -c $FILE -s test/tmp/$TARGET.z
  ./ppmc -x test/tmp/$TARGET.z -s test/tmp/$TARGET.original
   cmp $FILE test/tmp/$TARGET.original && echo -n "." ||  echo "Failed $FILE" && exit 1
done
echo
