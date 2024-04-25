rm -r src/*
rm -r build/*
mkdir src
mkdir build
asn1c message.asn1 -D src -no-gen-OER -no-gen-example
gcc -Isrc -o build/coder myCoder.c src/*.c -DPDU=Message -DASN_DISABLE_OER_SUPPORT
gcc -Isrc -o build/decoder myDecoder.c src/*.c -DPDU=Message -DASN_DISABLE_OER_SUPPORT
./build/coder ./build/rrc_ber_out
./build/decoder ./build/rrc_ber_out