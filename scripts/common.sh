
wake=""
wake_new=""
wide=""
wide_new=""
launcher=""
launcher_new=""

if [ "$OSTYPE" = "linux-gnu" ]
then

	host="linux"
	wake="../bin/linux/wake"
	wide="../bin/linux/wide"
	launcher="../Wonkey (linux)"
	
elif [ "$OSTYPE" = "linux-gnueabihf" ]
then

	host="raspbian"
	wake="../bin/raspbian/wake"
	wide="../bin/raspbian/wide"
	launcher="../Wonkey (raspbian)"
	
else

	host="macos"
	wake="../bin/macos/wake"
	wide="../bin/macos/wide.app"
	launcher="../Wonkey (macos).app"
fi
