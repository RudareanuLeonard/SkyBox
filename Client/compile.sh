#! /bin/bash
rm -rf client

g++ Client.* ../File/File.* -o client

if [ $? -eq 0 ]; then
	echo "Compiled successfully";
else
	echo "";
	echo "Compilation unsuccessfully";
	echo ""
fi
