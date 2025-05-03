#!/bin/bash
set -e

dd if=/dev/urandom of=invalid.a85 bs=1024 count=10 status=none
tr -cd '!-u' < invalid.a85 | tr '!-u' '\0' > tmp.a85
mv tmp.a85 invalid.a85

echo "Test launched..."

if ! ./../ascii85 -d invalid.a85 > decoded.bin 2> /dev/null; then
    echo "Test comleted successfully."
else
    echo "Тест failed."
    exit 1
fi
