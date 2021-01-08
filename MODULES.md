# Wonkey modules

| Module          | Category                                          | Deps                                                         | Usage    | Conversion |
| --------------- | ------------------------------------------------- | ------------------------------------------------------------ | -------- | ---------- |
| **wonkey**      | Core language functionality                       |                                                              | wonkey   | Done       |
| libc            | Standard C library wrapper                        |                                                              | wonkey   | Done       |
| std             | Standard Wonkey library                           | libc, sdl2, jni, android, emscripten, zlib, miniz, stb-image, stb-image-write, stb-vorbis | wonkey   | Done       |
| reflection      | Wonkey reflection support                         |                                                              | wonkey   | Done       |
| admob           | Admob wrapper                                     | jni, sdl2, mojo                                              | mobile   |            |
| android         | Android                                           | libc, sdl2, jni                                              | mobile   | Done       |
| assimp          | 3d importer library wrapper                       | libc, zlib                                                   | mojo3d   | Done       |
| bullet          | 3d physics library wrapper                        | libc                                                         | mojo3d   | Done       |
| chipmunk        | 2d physics library wrapper                        | libc                                                         | mojo     | Done       |
| emscripten      | Emscripten                                        | libc, sdl2                                                   | web      | Done       |
| freetype        | Freetype font library                             |                                                              | mojo     | Done       |
| gles20          | GLES library                                      | opengl                                                       | mojo     | Done       |
| hoedown         | Markdown parser                                   |                                                              | mojox    | Done       |
| httprequest     | Http request module                               | libc, jin, sdl2, mojo                                        | web      |            |
| iap             | In App purchases                                  | jni, mojo                                                    | mobile   |            |
| jni             | Java JNI wrapper                                  | libc                                                         | mobile   | Done       |
| litehtml        | Simple HTML renderer                              | libc                                                         | mojox    | Done       |
| miniz           | Mini Zip library                                  | libc                                                         | system   | Done       |
| mojo            | Wonkey application framework                      | freetype, emscripten, std, sdl2, opengl, openal              | mojo     | Done       |
| mojo3d          | Wonkey 3d support                                 | std, mojo                                                    | mojo3d   | Done       |
| mojo3d-loaders  | Mojo3d Assimp support                             | std, assimp, mojo3d                                          | mojo3d   | Done       |
| mojo3d-vr       | VR support for Mojo3d                             | std, mojo3d                                                  | mojo3d   | Done       |
| mojox           | GUI extensions for Mojo                           | std, mojo, hoeadown, litehtml                                | mojo     | Done       |
| openal          | OpenAL library wrapper                            | libc                                                         | audio    | Done       |
| opengl          | OpenGL library wrapper                            | libc                                                         | graphics | Done       |
| sdl2            | SDL2 library wrapper                              | libc                                                         | mojo     | Done       |
| sdl2-mixer      | SDL2 mixer library                                | sdl2                                                         | audio    | Done       |
| sokol           | Minimal agnostic graphics backend library wrapper | libc                                                         | graphics |            |
| sqlite          | SQLite wrapper                                    | libc                                                         | database | Done       |
| stb-image       | Minimal image loader library                      | libc                                                         | graphics | Done       |
| stb-image-write | Minimal image saver library                       | libc                                                         | graphics | Done       |
| stb-truetype    | Minimal Truetype font library                     |                                                              | graphics | Done       |
| stb-vorbis      | Minimal Vorbis loader                             |                                                              | audio    | Done       |
| theoraplayer    | Minimal Theora player                             | openal, libc                                                 | vidéo    | Done       |
| thread          | Wonkey threads support                            | libc                                                         | system   | Done       |
| tinyregex       | Tiny regex library wrapper                        | libc                                                         | system   | Done       |
| tinyxml2        | Tiny XML library wrapper                          |                                                              | system   | Done       |
| win32           | Windows Win32 support                             | libc                                                         | system   | Done       |
| zlib            | Zlib library                                      | libc                                                         | system   | Done       |

