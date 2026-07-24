#!/bin/bash

C_RESET='\033[0m'
C_BOLD='\033[1m'
C_RED='\033[1;31m'
C_GREEN='\033[1;32m'
C_YELLOW='\033[1;33m'
C_BLUE='\033[1;34m'
C_CYAN='\033[1;36m'

export C_RESET C_BOLD C_RED C_GREEN C_YELLOW C_BLUE C_CYAN

TARGET_CONFIG=${1:-all}

compile_mod() {
    local mod=$1
    local cfg=$2
    local log_file=/tmp/wake_build_${mod}_${cfg}.log
    echo -e "  ${C_CYAN}->${C_RESET} Compilando [${C_YELLOW}${cfg}${C_RESET}]: ${C_BOLD}${mod}${C_RESET}..."
    if ! wake mods -config=${cfg} ${mod} > ${log_file} 2>&1; then
        echo -e "  ${C_RED}[✗ ERROR] Falló ${mod} en modo ${cfg}${C_RESET}"
        touch /tmp/layer_has_errors.flag
    else
        rm -f ${log_file}
    fi
    return 0
}
export -f compile_mod

build_layer_tree() {
    local cfg=$1
    echo -e "${C_BLUE}==================================================${C_RESET}"
    echo -e " ${C_BOLD}ACTUALIZACIÓN (UPDATE)${C_RESET} EN MODO: ${C_YELLOW}${cfg}${C_RESET} (xargs -P 8)"
    echo -e "${C_BLUE}==================================================${C_RESET}"

    # --- CAPA 0 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 0 (${C_BOLD}1${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "wonkey" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 0 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 0 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 1 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 1 (${C_BOLD}17${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "android emscripten freetype hoedown iap jni libc litehtml mojo3d-vr raspberry stb-image-write stb-truetype tinyregex tinyxml2 win32 zlib" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 1 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 1 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 2 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 2 (${C_BOLD}13${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "chipmunk glfw miniaudio miniz openal opengl raylib sdl2 sokol sqlite stb-image stb-vorbis assimp" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 2 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 2 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 3 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 3 (${C_BOLD}5${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "glad theoraplayer gles20 sdl2-mixer std" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 3 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 3 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 4 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 4 (${C_BOLD}7${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "admob bullet httprequest mojo ncurses reflection thread" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 4 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 4 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 5 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 5 (${C_BOLD}5${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "mojox pyro-framework simplevideo timelinefx mojo3d" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 5 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 5 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 6 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 6 (${C_BOLD}3${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "pyro-gui pyro-scenegraph mojo3d-loaders" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 6 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 6 completada con éxito. [✓]${C_RESET}"

    # --- CAPA 7 ---
    rm -f /tmp/layer_has_errors.flag
    echo -e "${C_CYAN}--> Compilando Capa 7 (${C_BOLD}1${C_RESET}${C_CYAN} módulos)...${C_RESET}"
    echo "pyro-tiled" | tr ' ' '\n' | xargs -P 8 -I {} bash -c 'compile_mod "{}" "'${cfg}'"'
    if [ -f /tmp/layer_has_errors.flag ]; then
        rm -f /tmp/layer_has_errors.flag
        echo ''
        echo -e "${C_RED}==================================================${C_RESET}"
        echo -e " ${C_RED}[!] ERROR DETECTADO EN CAPA 7 [${cfg}]${C_RESET}"
        echo -e " ${C_YELLOW}Se procesaron todos los módulos de esta capa, pero${C_RESET}"
        echo -e " ${C_YELLOW}se detiene el avance a capas superiores.${C_RESET}"
        echo -e "${C_RED}==================================================${C_RESET}"
        exit 1
    fi
    echo -e "${C_GREEN}--> Capa 7 completada con éxito. [✓]${C_RESET}"

}

case "${TARGET_CONFIG}" in
    debug)
        build_layer_tree "debug"
        ;;
    release)
        build_layer_tree "release"
        ;;
    all)
        build_layer_tree "debug"
        build_layer_tree "release"
        ;;
    *)
        echo -e "${C_RED}[ERROR] Configuración desconocida: ${TARGET_CONFIG}${C_RESET}"
        echo -e "Uso: $0 [debug | release | all]"
        exit 1
        ;;
esac

echo -e "${C_GREEN}==================================================${C_RESET}"
echo -e " ${C_BOLD}${C_GREEN}¡PROCESO FINALIZADO CON ÉXITO! [✓]${C_RESET} "
echo -e "${C_GREEN}==================================================${C_RESET}"
