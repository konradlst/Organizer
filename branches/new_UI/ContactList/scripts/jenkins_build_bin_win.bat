set MINGWDIR=%QTDIR%\..\..\..\..\mingw
set PATH=%PATH%;%QTDIR%\bin
set PATH=%MINGWDIR%\bin;%PATH%
set PATH=%PATH%;c:\Windows\System32
set targetBinFolder=C:\project\Organizer\realize
set FileSignerTarget=Exchange
mkdir 	%targetBinFolder%

rem		Compilation
for /f "eol=# delims=- tokens=1,2" %%i in (ProjectsToDeploy.txt) do (
	call :build %%i %%j
)

rem  	Copy dll
xcopy /Y		%QTDIR%\bin\mingwm10.dll %targetBinFolder%
xcopy /Y		%QTDIR%\bin\libgcc_s_dw2-1.dll %targetBinFolder%
xcopy /Y		%QTDIR%\bin\QtGui4.dll %targetBinFolder%
xcopy /Y		%QTDIR%\bin\QtCore4.dll %targetBinFolder%
xcopy /Y		%QTDIR%\bin\QtXml4.dll %targetBinFolder%

exit /b


rem 	----------------------------------------------------------------
rem		Функция, собирающая проект с названием, переданным в первом аргументе. Имя бина передается во втором аргументе.
rem 	----------------------------------------------------------------
:build
set 		projectToBuild=%1
set 		binName=%2
rem --------------------------------------------------------------------
rem		Compiling %projectToBuild%
rem --------------------------------------------------------------------
set				buildDir=%projectToBuild%-build-release-temporary-directory
mkdir			%buildDir%
cd 				%buildDir%
qmake.exe 		%WORKSPACE%\MO\%projectToBuild%\%projectToBuild%.pro -r -spec win32-g++ "CONFIG+=release" "BUILD = %SVN_REVISION_2%"
mingw32-make.exe -f Makefile.Release

xcopy /Y		release\%binName%.exe %targetBinFolder%
cd ..
rmdir /S/Q		%buildDir%
exit /b
rem 	----------------------------------------------------------------
