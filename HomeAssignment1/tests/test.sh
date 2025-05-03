set -e

dd if=/dev/urandom of=test.bin bs=1024 count=10 status=none

python3 -c "import base64; print(base64.a85encode(open('test.bin','rb').read()).decode())" > py.a85

./../ascii85 test.bin > our.a85

if cmp -b py.a85 our.a85; then
    echo "Test completed right."
else
    echo "Test failed."
    exit 1
fi
