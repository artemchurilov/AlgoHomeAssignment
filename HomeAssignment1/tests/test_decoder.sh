#!/bin/bash
set -e

dd if=/dev/urandom of=test.bin bs=1024 count=10 status=none

python3 -c "import base64; print(base64.a85encode(open('test.bin','rb').read()).decode())" > py.a85

./../ascii85 -d py.a85 > decoded.bin
truncate -s -1 decoded.bin

if cmp -b test.bin decoded.bin; then
    echo "Decoding test completed successfully."
else
    echo "Decoding test failed."
    exit 1
fi