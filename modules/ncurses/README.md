# ncurses

A [curses](http://www.tldp.org/HOWTO/html_single/NCURSES-Programming-HOWTO/) library wrapper for Wonkey that supports Windows, Linux, and macOS

On Windows [PDCurses](https://github.com/wmcbrine/PDCurses) is used.

On Linux, Raspbian/RaspberryOS and macOS [Ncurses](https://en.wikipedia.org/wiki/Ncurses) is used.


## Instructions
* On Linux you will need to install 'ncurses-dev' (sudo apt install ncurses-dev)
* On Raspbian/RaspberryOS you will need to install 'libncurses5-dev' and the wide-char version 'libncursesw5-dev' (sudo apt-get install libncurses5-dev libncursesw5-dev)
* On macOS you will need to install 'ncurses' (using Homebrew or Cakebrew)
* Recompile module "ncurses"
* Compile tests inside the ‘tests’ folder
* Run tests via your ‘products’ folder and not via Wide
