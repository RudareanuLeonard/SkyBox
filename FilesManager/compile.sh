#!/bin/bash

rm -f filesmanager
g++ -std=c++20 FilesManager.* ../File/File.*     -o filesmanager

if [ $? -eq 0 ]; then
	echo "Compiled successfully";
else
	echo "";
	echo "Compilation unsuccessfully";
	echo ""
fi
