#!/bin/sh
for FILE in test/fixture/*; do
  TARGET=$(basename $FILE)
  ./ppmc c $FILE  test/fixture/$TARGET.z
  ./ppmc x test/fixture/$TARGET.z test/fixture/$TARGET.original
  cmp $FILE test/fixture/$TARGET.original && echo -n "." || ( echo "Failed $FILE" && exit 1)
done
echo
