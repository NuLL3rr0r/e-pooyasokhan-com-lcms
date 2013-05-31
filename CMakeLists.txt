CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.9 FATAL_ERROR )

PROJECT ( EPS )


SET ( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMakeModules" )


SET ( SUPPORTED_PLATFORM "" )
SET ( SUPPORTED_COMPILER "" )
SET ( CXX_GCC "" )
SET ( CXX_MINGW "" )
SET ( CXX_CLANG "" )
SET ( CXX_MSVC "" )
SET ( COMPILER "" )
SET ( COMPILER_NAME "" )
SET ( COMPILER_VERSION "" )
SET ( QT_GUI_TYPE "" )


MESSAGE ( STATUS "Checking if your OS (${CMAKE_SYSTEM}) is supported for building" )

IF ( UNIX )
    IF ( ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" )
        # FreeBSD
        SET ( SUPPORTED_PLATFORM "YES" )
    ELSEIF ( ${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD" )
        # OpenBSD
        SET ( SUPPORTED_PLATFORM "YES" )
    ELSEIF ( ${CMAKE_SYSTEM_NAME} MATCHES "NetBSD" )
        # NetBSD
        SET ( SUPPORTED_PLATFORM "YES" )
    ELSEIF ( ${CMAKE_SYSTEM_NAME} MATCHES "DragonFly" )
        # DragonFly BSD
        SET ( SUPPORTED_PLATFORM "YES" )
    ELSEIF ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
        # Linux
        SET ( SUPPORTED_PLATFORM "YES" )
    ELSEIF ( APPLE )
        IF ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
            # Apple Mac OS X
            SET ( SUPPORTED_PLATFORM "YES" )
            SET ( QT_GUI_TYPE MACOSX_BUNDLE )
        ELSE (  )
            # Unsupported
            SET ( SUPPORTED_PLATFORM "NO" )
        ENDIF (  )
    ENDIF (  )
ELSEIF ( WIN32 )
    IF ( CYGWIN )
        # CygWin
        SET ( SUPPORTED_PLATFORM "NO" )
    ELSE (  )
        # Microsoft Windows
        SET ( SUPPORTED_PLATFORM "YES" )
        SET ( QT_GUI_TYPE WIN32 )
    ENDIF (  )
ELSE (  )
    # Unsupported OS
    SET ( SUPPORTED_PLATFORM "NO" )
ENDIF (  )


IF ( SUPPORTED_PLATFORM )
    MESSAGE ( STATUS "Checking if your OS (${CMAKE_SYSTEM}) is supported for building -- yes" )
ELSE (  )
    MESSAGE ( STATUS "Checking if your OS (${CMAKE_SYSTEM}) is supported for building -- no" )
    MESSAGE ( FATAL_ERROR "\nUnfortunately your system doesn't meet the minimum requirements for building."
    "\nThe only supported platforms are *BSD, Linux, Windows and Mac OS X." )
ENDIF (  )


MESSAGE ( STATUS "Checking if your compiler (${CMAKE_CXX_COMPILER}) is supported for building" )


IF ( CMAKE_COMPILER_IS_GNUCXX )
    EXEC_PROGRAM ( "${CMAKE_C_COMPILER}" ARGS "-dumpversion" OUTPUT_VARIABLE GCC_VERSION_INFO )
    STRING ( REGEX REPLACE "^([0-9]+).*$"                   "\\1" GCC_MAJOR "${GCC_VERSION_INFO}" )
    STRING ( REGEX REPLACE "^[0-9]+\\.([0-9]+).*$"          "\\1" GCC_MINOR "${GCC_VERSION_INFO}" )
    STRING ( REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" GCC_PATCH "${GCC_VERSION_INFO}" )

    IF ( GCC_MAJOR MATCHES "\\.+" )
        SET ( GCC_MAJOR "" )
    ENDIF (  )
    IF ( GCC_MINOR MATCHES "\\.+" )
        SET ( GCC_MINOR "" )
    ENDIF (  )
    IF ( GCC_PATCH MATCHES "\\.+" )
        SET ( GCC_PATCH "" )
    ENDIF (  )

    SET ( CXX_GCC "YES" )

    IF ( NOT MINGW )
        SET ( COMPILER_NAME "gcc" )
    ELSE (  )
        SET ( CXX_MINGW "YES" )
        SET ( COMPILER_NAME "mingw" )
    ENDIF (  )

    SET ( COMPILER_VERSION "${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCH}" )

    SET ( COMPILER "${COMPILER_NAME}-${COMPILER_VERSION}" )
ELSE (  )
    SET ( GCC_MAJOR 0 )
    SET ( GCC_MINOR 0 )
    SET ( GCC_PATCH 0 )
    SET ( CXX_GCC "NO" )
ENDIF (  )

IF ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    EXEC_PROGRAM ( "${CMAKE_C_COMPILER}" ARGS "-v" OUTPUT_VARIABLE CLANG_VERSION_INFO )
    STRING ( REGEX REPLACE "^.*[ ]([0-9]+)\\.[0-9].*$" "\\1" CLANG_MAJOR "${CLANG_VERSION_INFO}" )
    STRING ( REGEX REPLACE "^.*[ ][0-9]+\\.([0-9]).*$" "\\1" CLANG_MINOR "${CLANG_VERSION_INFO}" )

    SET ( CXX_CLANG "YES" )
    SET ( COMPILER_NAME "clang" )
    SET ( COMPILER_VERSION "${CLANG_MAJOR}.${CLANG_MINOR}" )
    SET ( COMPILER "${COMPILER_NAME}-${COMPILER_VERSION}" )    
ELSE (  )
    SET ( CLANG_MAJOR 0 )
    SET ( CLANG_MINOR 0 )
    SET ( CXX_CLANG "NO" )
ENDIF (  )

IF ( WIN32 AND MSVC )
    EXEC_PROGRAM ( "${CMAKE_C_COMPILER}" ARGS "" OUTPUT_VARIABLE MSVC_VERSION_INFO )
    STRING ( REGEX REPLACE "^.*[ ]([0-9]+)\\.[0-9].*$" "\\1" MSVC_MAJOR "${MSVC_VERSION_INFO}" )
    STRING ( REGEX REPLACE "^.*[ ][0-9]+\\.([0-9]).*$" "\\1" MSVC_MINOR "${MSVC_VERSION_INFO}" )
    STRING ( REGEX REPLACE "^.*[ ][0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" MSVC_BUILD "${MSVC_VERSION_INFO}" )
    STRING ( REGEX REPLACE "^.*[ ][0-9]+\\.[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" MSVC_REVISION "${MSVC_VERSION_INFO}" )

    SET ( CXX_MSVC "YES" )
    SET ( COMPILER_NAME "msvc" )
    SET ( COMPILER_VERSION "${MSVC_MAJOR}.${MSVC_MINOR}.${MSVC_BUILD}.${MSVC_REVISION}" )
    SET ( COMPILER "${COMPILER_NAME}-${COMPILER_VERSION}" )    
ELSE (  )
    SET ( MSVC_MAJOR 0 )
    SET ( MSVC_MINOR 0 )
    SET ( MSVC_BUILD 0 )
    SET ( MSVC_REVISION 0 )
    SET ( CXX_MSVC "NO" )
ENDIF (  )


IF ( CXX_GCC )
    IF ( GCC_MAJOR GREATER 4 OR GCC_MAJOR EQUAL 4 )
        IF ( GCC_MINOR GREATER 6 OR  GCC_MINOR EQUAL 6 )
            SET ( SUPPORTED_COMPILER "YES" )
        ENDIF (  )
    ENDIF (  )
ELSEIF ( CXX_CLANG )
    IF ( CLANG_MAJOR GREATER 3 OR CLANG_MAJOR EQUAL 3 )
        IF ( CLANG_MINOR GREATER 2 OR  CLANG_MINOR EQUAL 2 )
            SET ( SUPPORTED_COMPILER "YES" )
        ENDIF (  )
    ENDIF (  )
ELSEIF ( CXX_MSVC )
    IF ( MSVC_MAJOR GREATER 17 OR MSVC_MAJOR EQUAL 17 )
        SET ( SUPPORTED_COMPILER "YES" )
    ENDIF (  )
ELSE (  )
    SET ( SUPPORTED_COMPILER "NO" )
ENDIF (  )


IF ( SUPPORTED_COMPILER )
    MESSAGE ( STATUS "Checking if your compiler (${CMAKE_CXX_COMPILER}) is supported for building -- yes" )
ELSE (  )
    MESSAGE ( STATUS "Checking if your compiler (${CMAKE_CXX_COMPILER}) is supported for building -- no" )
    MESSAGE ( FATAL_ERROR "\nUnfortunately your system doesn't meet the minimum requirements for building."
    "\nThe only supported compilers are gcc-4.6+, mingw-4.6+, clang-3.2+, msvc-17+." )
ENDIF (  )


INCLUDE ( CheckCXX11Features )

INCLUDE ( dependencies.cmake )

INCLUDE ( build-config.cmake )


IF ( CXX_GCC )
    IF ( GCC_MINOR GREATER 6 )
        SET ( CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}" )
    ELSE (  )
        SET ( CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}" )
    ENDIF (  )

    IF ( CMAKE_BUILD_TYPE MATCHES "GCCMinSizeRel"
            OR CMAKE_BUILD_TYPE MATCHES "GCCMaxSpeedRel"
            OR CMAKE_BUILD_TYPE MATCHES "GCCNativeMinSizeRel"
            OR CMAKE_BUILD_TYPE MATCHES "GCCNativeMaxSpeedRel" )
        SET ( GCC_CXX_FLAGS_WARN_LEVEL "-Wall -Wextra -Wno-unused-parameter" )
        SET ( GCC_CXX_FLAGS_ISO_CPP "-pedantic" )
        SET ( GCC_CXX_FLAGS_USE_PIPE "-pipe" )
        SET ( GCC_CXX_FLAGS_OPT_LEVEL_SIZE "-Os" )
        SET ( GCC_CXX_FLAGS_OPT_LEVEL_SPEED "-O2" )
        SET ( GCC_CXX_FLAGS_OPT_NATIVE "-march=native -mtune=native" )
        SET ( GCC_CXX_FLAGS_OMIT_FP "-fomit-frame-pointer" )
        SET ( GCC_CXX_FLAGS_SIZE_OPT "-ffunction-sections -fdata-sections" )
        SET ( GCC_LD_FLAGS_SIZE_OPT "-Wl,--gc-sections" )

        SET ( CMAKE_CXX_FLAGS_GCCMinSizeRel "${GCC_CXX_FLAGS_WARN_LEVEL} ${GCC_CXX_FLAGS_ISO_CPP}  ${GCC_CXX_FLAGS_USE_PIPE} ${GCC_CXX_FLAGS_OPT_LEVEL_SIZE} ${GCC_CXX_FLAGS_OMIT_FP} ${GCC_CXX_FLAGS_SIZE_OPT}" )
        SET ( CMAKE_CXX_FLAGS_GCCMaxSpeedRel "${GCC_CXX_FLAGS_WARN_LEVEL} ${GCC_CXX_FLAGS_ISO_CPP}  ${GCC_CXX_FLAGS_USE_PIPE} ${GCC_CXX_FLAGS_OPT_LEVEL_SPEED} ${GCC_CXX_FLAGS_OMIT_FP} ${GCC_CXX_FLAGS_SIZE_OPT}" )
        SET ( CMAKE_CXX_FLAGS_GCCNativeMinSizeRel "${GCC_CXX_FLAGS_WARN_LEVEL} ${GCC_CXX_FLAGS_ISO_CPP}  ${GCC_CXX_FLAGS_USE_PIPE} ${GCC_CXX_FLAGS_OPT_LEVEL_SIZE} ${GCC_CXX_FLAGS_OPT_NATIVE} ${GCC_CXX_FLAGS_OMIT_FP} ${GCC_CXX_FLAGS_SIZE_OPT}" )
        SET ( CMAKE_CXX_FLAGS_GCCNativeMaxSpeedRel "${GCC_CXX_FLAGS_WARN_LEVEL} ${GCC_CXX_FLAGS_ISO_CPP}  ${GCC_CXX_FLAGS_USE_PIPE} ${GCC_CXX_FLAGS_OPT_LEVEL_SPEED}  ${GCC_CXX_FLAGS_OPT_NATIVE} ${GCC_CXX_FLAGS_OMIT_FP} ${GCC_CXX_FLAGS_SIZE_OPT}" )

        SET ( CMAKE_C_FLAGS_GCCMinSizeRel CMAKE_CXX_FLAGS_GCCMinSizeRel )
        SET ( CMAKE_C_FLAGS_GCCMaxSpeedRel CMAKE_CXX_FLAGS_GCCMaxSpeedRel )
        SET ( CMAKE_C_FLAGS_GCCNativeMinSizeRel CMAKE_CXX_FLAGS_GCCNativeMinSizeRel )
        SET ( CMAKE_C_FLAGS_GCCNativeMaxSpeedRel CMAKE_CXX_FLAGS_GCCNativeMaxSpeedRel )

        IF ( CMAKE_BUILD_TYPE MATCHES "GCCMinSizeRel")
            SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_GCCMinSizeRel}" )
            SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_GCCMinSizeRel}" )
        ENDIF (  )

        IF ( CMAKE_BUILD_TYPE MATCHES "GCCMaxSpeedRel")
            SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_GCCMaxSpeedRel}" )
            SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_GCCMaxSpeedRel}" )
        ENDIF (  )

        IF ( CMAKE_BUILD_TYPE MATCHES "GCCNativeMinSizeRel")
            SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_GCCNativeMinSizeRel}" )
            SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_GCCNativeMinSizeRel}" )
        ENDIF (  )

        IF ( CMAKE_BUILD_TYPE MATCHES "GCCNativeMaxSpeedRel")
            SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_GCCNativeMaxSpeedRel}" )
            SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_GCCNativeMaxSpeedRel}" )
        ENDIF (  )

        SET ( CMAKE_EXE_LINKER_FLAGS "${GCC_LD_FLAGS_SIZE_OPT}" )
    ENDIF ()
ENDIF (  )


MESSAGE ( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )
MESSAGE ( STATUS "Compiler flags: ${CMAKE_CXX_FLAGS}" )
MESSAGE ( STATUS "Linker flags: ${CMAKE_EXE_LINKER_FLAGS}" )

INCLUDE_DIRECTORIES(.)

IF ( WIN32 AND MINGW )
    IF ( BUILD_EPS_ADMIN OR BUILD_EPS_TEACHER OR BUILD_EPS_STUDENT )
        SET ( QT5_GCC_LIB "libgcc_s_sjlj-1.dll" )
        SET ( QT5_STDCPP_LIB "libstdc++-6.dll" )
        SET ( QT5_WINPTHREAD_LIB "libwinpthread-1.dll" )
        SET ( QT5_ICU_DT_LIB "icudt49.dll" )
        SET ( QT5_ICU_IN_LIB "icuin49.dll" )
        SET ( QT5_ICU_UC_LIB "icuuc49.dll" )
        SET ( QT5_EGL_LIB_DEB "libEGLd.dll" )
        SET ( QT5_EGL_LIB_REL "libEGL.dll" )
        SET ( QT5_GLESV2_LIB_DEB "libGLESv2d.dll" )
        SET ( QT5_GLESV2_LIB_REL "libGLESv2.dll" )
        SET ( QT5_QMINIMAL_LIB_DEB "platforms/qminimald.dll" )
        SET ( QT5_QMINIMAL_LIB_REL "platforms/qminimal.dll" )
        SET ( QT5_QWINDOWS_LIB_DEB "platforms/qwindowsd.dll" )
        SET ( QT5_QWINDOWS_LIB_REL "platforms/qwindows.dll" )
        SET ( QT5_CORE_LIB_DEB "Qt5Cored.dll" )
        SET ( QT5_CORE_LIB_REL "Qt5Core.dll" )
        SET ( QT5_GUI_LIB_DEB "Qt5Guid.dll" )
        SET ( QT5_GUI_LIB_REL "Qt5Gui.dll" )
        SET ( QT5_NETWORK_LIB_DEB "Qt5Networkd.dll" )
        SET ( QT5_NETWORK_LIB_REL "Qt5Network.dll" )
        SET ( QT5_QML_LIB_DEB "Qt5Qmld.dll" )
        SET ( QT5_QML_LIB_REL "Qt5Qml.dll" )
        SET ( QT5_QUICK_LIB_DEB "Qt5Quickd.dll" )
        SET ( QT5_QUICK_LIB_REL "Qt5Quick.dll" )
        SET ( QT5_V8_LIB_DEB "Qt5V8d.dll" )
        SET ( QT5_V8_LIB_REL "Qt5V8.dll" )
        SET ( QT5_WIDGETS_LIB_DEB "Qt5Widgetsd.dll" )
        SET ( QT5_WIDGETS_LIB_REL "Qt5Widgets.dll" )

        FIND_PACKAGE( Qt5Core REQUIRED )

        GET_TARGET_PROPERTY( QMAKE_EXECUTABLE Qt5::qmake LOCATION )            
        FUNCTION ( QUERY_QMAKE VAR RESULT )
            EXEC_PROGRAM( ${QMAKE_EXECUTABLE} ARGS "-query ${VAR}"
                            RETURN_VALUE RETURN_CODE OUTPUT_VARIABLE OUT_VAR )
            IF ( NOT RETURN_CODE )
                FILE ( TO_CMAKE_PATH "${OUT_VAR}" OUT_VAR )
                SET ( ${RESULT} ${OUT_VAR} PARENT_SCOPE )
            ENDIF (  )
        ENDFUNCTION ( QUERY_QMAKE VAR RESULT )

        QUERY_QMAKE(QT_INSTALL_BINS QT5_LIBRARY_PATH)
        QUERY_QMAKE(QT_INSTALL_PLUGINS QT5_PLUGINS_PATH)

        IF ( CMAKE_BUILD_TYPE MATCHES "Release"
                OR CMAKE_BUILD_TYPE MATCHES "GCCMinSizeRel"
                OR CMAKE_BUILD_TYPE MATCHES "GCCMaxSpeedRel"
                OR CMAKE_BUILD_TYPE MATCHES "GCCNativeMinSizeRel"
                OR CMAKE_BUILD_TYPE MATCHES "GCCNativeMaxSpeedRel" )
            GET_FILENAME_COMPONENT( BOOST_FILESYSTEM_LIBRARY_PATH "${Boost_FILESYSTEM_LIBRARY_RELEASE}" NAME )
            GET_FILENAME_COMPONENT( BOOST_SYSTEM_LIBRARY_PATH "${Boost_SYSTEM_LIBRARY_RELEASE}" NAME )
            GET_FILENAME_COMPONENT( BOOST_THREAD_LIBRARY_PATH "${Boost_THREAD_LIBRARY_RELEASE}" NAME )

            SET ( QT5_EGL_LIB ${QT5_EGL_LIB_REL} )
            SET ( QT5_GLESV2_LIB ${QT5_GLESV2_LIB_REL} )
            SET ( QT5_QMINIMAL_LIB ${QT5_QMINIMAL_LIB_REL} )
            SET ( QT5_QWINDOWS_LIB ${QT5_QWINDOWS_LIB_REL} )
            SET ( QT5_CORE_LIB ${QT5_CORE_LIB_REL} )
            SET ( QT5_GUI_LIB ${QT5_GUI_LIB_REL} )
            SET ( QT5_NETWORK_LIB ${QT5_NETWORK_LIB_REL} )
            SET ( QT5_QML_LIB ${QT5_QML_LIB_REL} )
            SET ( QT5_QUICK_LIB ${QT5_QUICK_LIB_REL} )
            SET ( QT5_V8_LIB ${QT5_V8_LIB_REL} )
            SET ( QT5_WIDGETS_LIB ${QT5_WIDGETS_LIB_REL} )
        ELSE (  )
            GET_FILENAME_COMPONENT( BOOST_FILESYSTEM_LIBRARY_PATH "${Boost_FILESYSTEM_LIBRARY_DEBUG}" NAME )
            GET_FILENAME_COMPONENT( BOOST_SYSTEM_LIBRARY_PATH "${Boost_SYSTEM_LIBRARY_DEBUG}" NAME )
            GET_FILENAME_COMPONENT( BOOST_THREAD_LIBRARY_PATH "${Boost_THREAD_LIBRARY_DEBUG}" NAME )

            GET_TARGET_PROPERTY( QT_CORE_LIBRARY_PATH Qt5::Core LOCATION_Debug )
            GET_TARGET_PROPERTY( QT_GUI_LIBRARY_PATH Qt5::Gui LOCATION_Debug )

            SET ( QT5_EGL_LIB ${QT5_EGL_LIB_DEB} )
            SET ( QT5_GLESV2_LIB ${QT5_GLESV2_LIB_DEB} )
            SET ( QT5_QMINIMAL_LIB ${QT5_QMINIMAL_LIB_DEB} )
            SET ( QT5_QWINDOWS_LIB ${QT5_QWINDOWS_LIB_DEB} )
            SET ( QT5_CORE_LIB ${QT5_CORE_LIB_DEB} )
            SET ( QT5_GUI_LIB ${QT5_GUI_LIB_DEB} )
            SET ( QT5_NETWORK_LIB ${QT5_NETWORK_LIB_DEB} )
            SET ( QT5_QML_LIB ${QT5_QML_LIB_DEB} )
            SET ( QT5_QUICK_LIB ${QT5_QUICK_LIB_DEB} )
            SET ( QT5_V8_LIB ${QT5_V8_LIB_DEB} )
            SET ( QT5_WIDGETS_LIB ${QT5_WIDGETS_LIB_DEB} )
        ENDIF (  )

        SET ( BOOST_FILESYSTEM_LIBRARY_PATH "${Boost_LIBRARY_DIRS}/${BOOST_FILESYSTEM_LIBRARY_PATH}" )
        SET ( BOOST_SYSTEM_LIBRARY_PATH "${Boost_LIBRARY_DIRS}/${BOOST_SYSTEM_LIBRARY_PATH}" )
        SET ( BOOST_THREAD_LIBRARY_PATH "${Boost_LIBRARY_DIRS}/${BOOST_THREAD_LIBRARY_PATH}" )
    ENDIF (  )
ENDIF (  )


SUBDIRS( MyLib EPSServer EPSAdmin EPSTeacher EPSStudent )

INCLUDE ( source-files.cmake )


