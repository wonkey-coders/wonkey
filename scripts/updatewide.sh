
. ./common.sh

echo ""
echo "***** Updating wide *****"
echo ""

$wake app -apptype=gui -build -config=release -product=scripts/wide.products/$host/wide ../src/wide/wide.wx

$wake app -apptype=gui -build -config=release -product=scripts/launcher.products/$host/launcher ../src/launcher/launcher.wx

if [ "$OSTYPE" = "linux-gnu" ]
then

	rm -r -f $wide
	mkdir $wide
	cp -R ./wide.products/$host/assets $wide/assets
	cp ./wide.products/$host/wide $wide/wide

	rm -r -f "$launcher"
	cp ./launcher.products/$host/launcher "$launcher"

elif [ "$OSTYPE" = "linux-gnueabihf" ]
then

	rm -r -f $wide
	mkdir $wide
	cp -R ./wide.products/$host/assets $wide/assets
	cp ./wide.products/$host/wide $wide/wide

	rm -r -f "$launcher"
	cp ./launcher.products/$host/launcher "$launcher"

else

	rm -r -f $wide
	cp -R ./wide.products/macos/wide.app $wide

	cp ../src/wide/logo/info.plist "$wide/Contents"
	cp ../src/wide/logo/wide.icns "$wide/Contents/Resources"
	cp ../src/wide/logo/wxproject.icns "$wide/Contents/Resources"

	rm -r -f "$launcher"
	cp -R ./launcher.products/macos/Launcher.app "$launcher"
	
	cp ../src/launcher/info.plist "$launcher/Contents"
	cp ../src/launcher/wide.icns "$launcher/Contents/Resources"

fi
