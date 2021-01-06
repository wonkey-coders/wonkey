Upgrading SDL source:

* include/config_*.h : need to be copied/merged - this is where SDL features are enabled.

* include/begin_code.h : #define DECLSPEC to empty at top to statically link without msvc generating .lib and .exp files due to dllimport/dllexport symbols. Seems to be no #define SDL_STATIC_BUILD here?

* src/core/SDL_android.h/SDL_android.c : Android_JNI_GetAssetManager() added.
