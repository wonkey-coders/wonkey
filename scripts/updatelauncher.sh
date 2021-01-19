
. ./common.sh

echo ""
echo "***** Updating launcher *****"
echo ""

$wake app -apptype=gui -build -config=release -product=scripts/launcher.products/$host/launcher ../src/launcher/launcher.wx

if [ "$OSTYPE" = "linux-gnu" ]
then

	rm -r -f "$launcher"
	cp ./launcher.products/$host/launcher "$launcher"

elif [ "$OSTYPE" = "linux-gnueabihf" ]
then

	rm -r -f "$launcher"
	cp ./launcher.products/$host/launcher "$launcher"

else

	rm -r -f "$launcher"
	cp -R ./launcher.products/macos/Launcher.app "$launcher"
	
	cp ../src/launcher/info.plist "$launcher/Contents"
	cp ../src/launcher/wide_logo.icns "$launcher/Contents/Resources"

fi
