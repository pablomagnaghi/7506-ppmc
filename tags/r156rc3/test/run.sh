#!/bin/sh
for FILE in test/fixture/*; do
  TARGET=$(basename $FILE)
  ./ppmc c $FILE  test/tmp/$TARGET.z
  ./ppmc x test/tmp/$TARGET.z test/tmp/$TARGET.original
   cmp $FILE test/tmp/$TARGET.original && echo -n "." || ( echo "Failed $FILE" && exit 1)
done
echo
