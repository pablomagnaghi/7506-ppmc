touch *hpp *cpp
aclocal -I /usr/local/share/aclocal
autoconf
automake -a
touch NEWS README AUTHORS ChangeLog # To make automake happy
./configure
make check
