
wake=""
wake_new=""
wide=""
wide_new=""

if [ "$OSTYPE" = "linux-gnu" ]
then

	host="linux"
	wake="../bin/linux/wake"
	wide="../bin/linux/wide"
	
elif [ "$OSTYPE" = "linux-gnueabihf" ]
then

	host="raspbian"
	wake="../bin/raspbian/wake"
	wide="../bin/raspbian/wide"
	
else

	host="macos"
	wake="../bin/macos/wake"
	wide="../bin/macos/wide.app"
	
fi
