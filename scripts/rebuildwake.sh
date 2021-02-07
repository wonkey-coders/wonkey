
. ./common.sh

echo ""
echo "***** Rebuilding wake *****"
echo ""

$wake mods -config=release wonkey libc miniz stb-image stb-image-write stb-vorbis zlib std

$wake app -clean -apptype=console -config=release -product=scripts/wake.products/wake_$host ../src/wake/wake.wx

cp wake.products/wake_$host $wake
