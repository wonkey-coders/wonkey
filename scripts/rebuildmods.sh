
. ./common.sh

echo ""
echo "***** Rebuilding modules *****"
echo ""

$wake mods -clean -target=desktop -config=release
$wake mods -clean -target=desktop -config=debug
