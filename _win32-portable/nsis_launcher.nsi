SetCompressor /SOLID lzma

!define LAUNCHER_OUTPUT "..\_build\eps-launcher.exe"
!define LAUNCHER_ICON "..\EPSDesktop\resources\app-icon.ico"
!define EXECUTABLE_PATH ".\app"
!define EXECUTABLE_NAME "eps-desktop.exe"

OutFile "${LAUNCHER_OUTPUT}"
Icon "${LAUNCHER_ICON}"
SilentInstall silent

Section "MainSection" SEC01
  SetOutPath "${EXECUTABLE_PATH}"
  ExecWait '"${EXECUTABLE_NAME}"'
SectionEnd

