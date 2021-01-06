
@manpage Monkey2 Target SDKs

### Monkey2 Target SDKs

Monkey2 target SDKs.


@#### The Windows Desktop Target

Monkey2 can use either the mingw or msvc express 2015 compilers to build desktop apps.

To use mingw, you can use the mingw build tools available at [[http://monkeycoder.co.nz/monkey2-files]]. Simply download the mingw build tools package, run it (it's a self extracting exe), and select your monkey2 'devtools' dir for installation.

Note that the prebuilt binaries available from itch.io already include mingw in the 'devtools' dir.

To use msvc instead of mingw, you will need to install msvc express 2015 and change the following line in bin/env_windows.txt:

```
#MX2_USE_MSVC=1
```

You will need to rebuild all modules after doing this.

Downloads for msvc express can be found here: [[https://www.visualstudio.com/vs/visual-studio-express/]]


@#### The Macos Desktop Target

Monkey2 uses the command line tools included with xcode to build desktop apps for macos.


@#### The Linux Desktop Target

Monkey2 uses the 'gcc' command line tools to build desktop apps for linux.

You will also need to install all the developer libraries required by the compiler and modules. This will differ depending on the precise version of Linux you have, but to get you started:

```
sudo apt-get update && sudo apt-get upgrade

sudo apt-get install g++-multilib libopenal-dev libpulse-dev libsdl2-dev
```


@#### The Emscripten Target

Monkey2 uses the emscripten sdk compilers and tools to build wasm and asm.js apps.

For 64 bit windows, there is an experimental emscripten sdk download available from [[http://monkeycoder.co.nz/monkey2-files/]].

For all other desktop targets, you will need to install emscripten yourself. More info here: [[https://github.com/juj/emsdk/blob/master/README.md]].

You will also need the mserver ('mini server') app if you want to be able to launch emscripten apps from Ted2 or Ted2go. This can also be downloaded from [[http://monkeycoder.co.nz/monkey2-files/]].


@#### The Android Target

Monkey2 uses the android NDK (native development kit) to build android apps.

Setting up for Android development:

1) Install android studio and make sure it works, ie: you can build and run one of the simple template projects on a device or emulator. Android studio is available here: [[https://developer.android.com/studio/index.html]].

2) Install the 'NDK' (native development kit) using android studio via 'SDK Manager->SDK Tools'.

3) Install the Android 7.0 (Nougat) SDK Platform (API Level 24) using android studio via 'SDK Manager'.

4) Edit your monkey2 bin/env_windows.txt file and change the ndk-bundle 'PATH' setting so it points to the NDK. Or, you can just add the ndk-bundle directory to your system PATH.

5) Fire up Ted2 and select 'Build->Rebuild Modules->Android'. Wait...

Building an Android app:

1) Build your app in Ted2 using 'Build->Build Only' with 'Build Target->Android' selected.

2) Open the generated android studio project (at myapp.products/Android) in android studio.

Note: I recommend *disabling* the following android studio setting for mx2 dev:

File->Settings->Build, Execution, Deployment->Instant Run->Enable Instant Run

With this enabled, android studio doesn't seem to notice when external project files change.


@#### The iOS Target

Monkey2 uses the command line tools included with xcode to build ios apps.

