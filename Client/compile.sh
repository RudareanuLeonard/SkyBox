#! /bin/bash
rm -rf client

g++ -std=c++20 Client.* ../File/File.* ../FilesManager/FilesManager.* -o client

if [ $? -eq 0 ]; then
	echo "Compiled successfully";
else
	echo "";
	echo "Compilation unsuccessfully";
	echo ""
fi
