@echo off

set LAUNCHER_SOURCE="native_launcher.cpp"
set LAUNCHER_RC="native_launcher.rc"
set LAUNCHER_OUTPUT_APP="..\_build\eps-launcher.exe"
set LAUNCHER_OUTPUT_RES="..\_build\eps-launcher.res"

del %LAUNCHER_OUTPUT_APP% > nul
del %LAUNCHER_OUTPUT_RES% > nul


chcp 1252
windres -O coff %LAUNCHER_RC% -o %LAUNCHER_OUTPUT_RES%

REM Note: Instead of "-mwindows" or "-mconsole", it is possible to add "-subsystem,windows" or "-subsystem,console" to linker flags.
REM "-static" is added for winpthread and other needed libs if any
g++ -Wall -Wextra -Wno-unused-parameter -pedantic -pipe -Os -fomit-frame-pointer -static-libgcc -static-libstdc++ -static -mwindows -lwinpthread -Wl,--gc-sections -ffunction-sections -fdata-sections -o %LAUNCHER_OUTPUT_APP% %LAUNCHER_OUTPUT_RES% %LAUNCHER_SOURCE%

strip %LAUNCHER_OUTPUT_APP%
strip -R.comment %LAUNCHER_OUTPUT_APP%


echo.
echo.
echo.
pause

