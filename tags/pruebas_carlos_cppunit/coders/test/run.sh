cd test

../run encode unary 2 9 > out_unary_encode.txt
cmp unary_encode.txt out_unary_encode.txt || ( echo "Fail unary encode" && exit 1 )

../run encode gamma 12 19  > out_gamma_encode.txt
cmp gamma_encode.txt out_gamma_encode.txt || ( echo "Fail gamma encode" && exit 1 )

../run encode delta 12 19  > out_delta_encode.txt
cmp delta_encode.txt out_delta_encode.txt || ( echo "Fail delta encode" && exit 1 )

../run decode unary 1 12  > out_unary_decode.txt
cmp unary_decode.txt out_unary_decode.txt || ( echo "Fail unary decode" && exit 1 )
cd ..
