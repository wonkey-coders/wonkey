
. ./common.sh

echo ""
echo "***** Updating modules *****"
echo ""

$wake mods -config=release

$wake mods -config=debug