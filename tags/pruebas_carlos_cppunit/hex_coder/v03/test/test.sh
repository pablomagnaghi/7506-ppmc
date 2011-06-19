cd test
cat test.ascii | xargs --null ../run decode > out.zip
cmp test.zip out.zip || ( echo "Fail decode" && exit 1 )

../run encode_stream test.empty > out.empty
cmp test.empty out.empty || ( echo "Fail encode stream empty" && exit 1 )

../run encode_stream test.zip > out.ascii 
cmp test.ascii out.ascii || ( echo "Fail encode stream" && exit 1 )

../run encode_buffer "abcdef" > out.buffer
cmp test.buffer out.buffer || (echo "Fail encode buffer" && exit 1)

cd ..
