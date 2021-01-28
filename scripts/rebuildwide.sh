
. ./common.sh

echo ""
echo "***** Rebuilding wide *****"
echo ""

$wake app -clean -apptype=gui -build -config=release -product=scripts/wide.products/$host/wide ../src/wide/wide.wx

if [ "$OSTYPE" = "linux-gnu" ]
then

	rm -r -f $wide
	mkdir $wide
	cp -R ./wide.products/$host/assets $wide/assets
	cp ./wide.products/$host/wide $wide/wide

elif [ "$OSTYPE" = "linux-gnueabihf" ]
then

	rm -r -f $wide
	mkdir $wide
	cp -R ./wide.products/$host/assets $wide/assets
	cp ./wide.products/$host/wide $wide/wide

else

	rm -r -f $wide
	cp -R ./wide.products/macos/wide.app $wide

	cp ../src/wide/logo/info.plist "$wide/Contents"
	cp ../src/wide/logo/wide.icns "$wide/Contents/Resources"

fi
