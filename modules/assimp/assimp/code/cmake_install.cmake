# Install script for directory: D:/dev/github-assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/dev/github-assimp/lib/Debug/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/dev/github-assimp/lib/Release/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/dev/github-assimp/lib/MinSizeRel/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/dev/github-assimp/lib/RelWithDebInfo/assimp-vc140-mt.lib")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.3.1" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/dev/github-assimp/bin/Debug/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/dev/github-assimp/bin/Release/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/dev/github-assimp/bin/MinSizeRel/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/dev/github-assimp/bin/RelWithDebInfo/assimp-vc140-mt.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/dev/github-assimp/code/../include/assimp/anim.h"
    "D:/dev/github-assimp/code/../include/assimp/ai_assert.h"
    "D:/dev/github-assimp/code/../include/assimp/camera.h"
    "D:/dev/github-assimp/code/../include/assimp/color4.h"
    "D:/dev/github-assimp/code/../include/assimp/color4.inl"
    "D:/dev/github-assimp/code/../include/assimp/config.h"
    "D:/dev/github-assimp/code/../include/assimp/defs.h"
    "D:/dev/github-assimp/code/../include/assimp/cfileio.h"
    "D:/dev/github-assimp/code/../include/assimp/light.h"
    "D:/dev/github-assimp/code/../include/assimp/material.h"
    "D:/dev/github-assimp/code/../include/assimp/material.inl"
    "D:/dev/github-assimp/code/../include/assimp/matrix3x3.h"
    "D:/dev/github-assimp/code/../include/assimp/matrix3x3.inl"
    "D:/dev/github-assimp/code/../include/assimp/matrix4x4.h"
    "D:/dev/github-assimp/code/../include/assimp/matrix4x4.inl"
    "D:/dev/github-assimp/code/../include/assimp/mesh.h"
    "D:/dev/github-assimp/code/../include/assimp/postprocess.h"
    "D:/dev/github-assimp/code/../include/assimp/quaternion.h"
    "D:/dev/github-assimp/code/../include/assimp/quaternion.inl"
    "D:/dev/github-assimp/code/../include/assimp/scene.h"
    "D:/dev/github-assimp/code/../include/assimp/metadata.h"
    "D:/dev/github-assimp/code/../include/assimp/texture.h"
    "D:/dev/github-assimp/code/../include/assimp/types.h"
    "D:/dev/github-assimp/code/../include/assimp/vector2.h"
    "D:/dev/github-assimp/code/../include/assimp/vector2.inl"
    "D:/dev/github-assimp/code/../include/assimp/vector3.h"
    "D:/dev/github-assimp/code/../include/assimp/vector3.inl"
    "D:/dev/github-assimp/code/../include/assimp/version.h"
    "D:/dev/github-assimp/code/../include/assimp/cimport.h"
    "D:/dev/github-assimp/code/../include/assimp/importerdesc.h"
    "D:/dev/github-assimp/code/../include/assimp/Importer.hpp"
    "D:/dev/github-assimp/code/../include/assimp/DefaultLogger.hpp"
    "D:/dev/github-assimp/code/../include/assimp/ProgressHandler.hpp"
    "D:/dev/github-assimp/code/../include/assimp/IOStream.hpp"
    "D:/dev/github-assimp/code/../include/assimp/IOSystem.hpp"
    "D:/dev/github-assimp/code/../include/assimp/Logger.hpp"
    "D:/dev/github-assimp/code/../include/assimp/LogStream.hpp"
    "D:/dev/github-assimp/code/../include/assimp/NullLogger.hpp"
    "D:/dev/github-assimp/code/../include/assimp/cexport.h"
    "D:/dev/github-assimp/code/../include/assimp/Exporter.hpp"
    "D:/dev/github-assimp/code/../include/assimp/DefaultIOStream.h"
    "D:/dev/github-assimp/code/../include/assimp/DefaultIOSystem.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/dev/github-assimp/code/../include/assimp/Compiler/pushpack1.h"
    "D:/dev/github-assimp/code/../include/assimp/Compiler/poppack1.h"
    "D:/dev/github-assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/dev/github-assimp/code/Debug/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/dev/github-assimp/code/RelWithDebInfo/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

