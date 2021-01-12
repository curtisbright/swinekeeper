# this script tries to build the kde version of truffle-swine keeper 
# execute it with ./build_linux as current directory 

make library_release

cd ../mineui_kde
CPPFLAGS=-I../.. ./configure
make 
cd ../build_linux  




