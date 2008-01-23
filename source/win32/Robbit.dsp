# Microsoft Developer Studio Project File - Name="Robot_Class" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Robot_Class - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Robbit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Robbit.mak" CFG="Robot_Class - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Robot_Class - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Robot_Class - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Robot_Class - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib cv.lib highgui.lib cxcore.lib cvaux.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Robot_Class - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib cv.lib highgui.lib cxcore.lib cvaux.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Robot_Class - Win32 Release"
# Name "Robot_Class - Win32 Debug"
# Begin Source File

SOURCE=.\BotHit.h
# End Source File
# Begin Source File

SOURCE=.\Definitions.h
# End Source File
# Begin Source File

SOURCE=.\DetectObstacleCollision.h
# End Source File
# Begin Source File

SOURCE=.\Display.h
# End Source File
# Begin Source File

SOURCE=.\DistancePointLine.h
# End Source File
# Begin Source File

SOURCE=.\DrawFloor.h
# End Source File
# Begin Source File

SOURCE=.\DrawObstacle.h
# End Source File
# Begin Source File

SOURCE=.\DrawRightClickMenu.h
# End Source File
# Begin Source File

SOURCE=.\DrawString.h
# End Source File
# Begin Source File

SOURCE=.\DrawTrails.h
# End Source File
# Begin Source File

SOURCE=.\frameRenderFrame.h
# End Source File
# Begin Source File

SOURCE=.\frameUpdate.h
# End Source File
# Begin Source File

SOURCE=.\GetNextFrame.h
# End Source File
# Begin Source File

SOURCE=.\Init.h
# End Source File
# Begin Source File

SOURCE=.\KeyEventHandler.h
# End Source File
# Begin Source File

SOURCE=.\KillAnimation.h
# End Source File
# Begin Source File

SOURCE=.\MenuSelect.h
# End Source File
# Begin Source File

SOURCE=.\Motion.h
# End Source File
# Begin Source File

SOURCE=.\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\NextNo.h
# End Source File
# Begin Source File

SOURCE=.\OutputCharacter.h
# End Source File
# Begin Source File

SOURCE=.\PlayControl.h
# End Source File
# Begin Source File

SOURCE=.\PositionKhepera2.h
# End Source File
# Begin Source File

SOURCE=.\PositionKhepera3.h
# End Source File
# Begin Source File

SOURCE=.\ReadObstacle.h
# End Source File
# Begin Source File

SOURCE=.\Reshape.h
# End Source File
# Begin Source File

SOURCE=.\Robbit.cpp
# End Source File
# Begin Source File

SOURCE=.\Robot_Class.h
# End Source File
# Begin Source File

SOURCE=.\SubDisplay.h
# End Source File
# Begin Source File

SOURCE=.\SubReshape.h
# End Source File
# Begin Source File

SOURCE=.\VideoDump.h
# End Source File
# Begin Source File

SOURCE=.\WindowDump.h
# End Source File
# Begin Source File

SOURCE=.\WriteInputFile.h
# End Source File
# End Target
# End Project
