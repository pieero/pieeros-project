;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "Akoostic Player Installer"
  OutFile "AkoosticPlayer-Installer.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES32\Akoostic Player"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\AkoosticPlayer" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "extras\lgpl-2.1.txt"
  ;!insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "French"
  !insertmacro MUI_DEFAULT MUI_ICON "Resources\akoosticplayer.ico"

;--------------------------------
;Installer Sections

Section ;"Dummy Section" SecDummy

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  File ..\AkoosticPlayer-build-desktop\release\AkoosticPlayer.exe
  File extras\mingwm10.dll
  File extras\libgcc_s_dw2-1.dll
  File extras\phonon4.dll
  File extras\QtCore4.dll
  File extras\QtGui4.dll

  SetOutPath "$INSTDIR\phonon_backend"

  File extras\phonon_backend\phonon_ds94.dll
  
  CreateDirectory "$SMPROGRAMS\Akoostic Player"
  CreateShortCut "$SMPROGRAMS\Akoostic Player\Akoostic Player.lnk" "$INSTDIR\AkoosticPlayer.exe"
  CreateShortCut "$SMPROGRAMS\Akoostic Player\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  ;Store installation folder
  WriteRegStr HKCU "Software\AkoosticPlayer" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  ;LangString DESC_SecDummy ${LANG_ENGLISH} "A test section."
  ;LangString DESC_SecDummy ${LANG_FRENCH} "Une section de test."

  ;Assign language strings to sections
  ;!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  ;  !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} $(DESC_SecDummy)
  ;!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...
  Delete $INSTDIR\AkoosticPlayer.exe
  Delete $INSTDIR\mingwm10.dll
  Delete $INSTDIR\libgcc_s_dw2-1.dll
  Delete $INSTDIR\phonon4.dll
  Delete $INSTDIR\QtCore4.dll
  Delete $INSTDIR\QtGui4.dll

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\Modern UI Test"
  
  Delete "$SMPROGRAMS\Akoostic Player\Akoostic Player.lnk"
  Delete "$SMPROGRAMS\Akoostic Player\Uninstall.lnk"
  RMDir "$SMPROGRAMS\Akoostic Player"



SectionEnd