set targetBinFolder=C:\project\Organizer\distrib
set IBDIR=C:\InstallBuilder\bin

mkdir output
cd output

for /f "eol=# delims== tokens=1,2" %%i in (..\version_number.txt) do (
	set VERSION=%%j
)

echo version: %VERSION%

%IBDIR%\builder build ..\ContactList.xml windows --verbose --setvars project.outputDirectory=.\ project.version=%VERSION%
%IBDIR%\builder build ..\ContactList.xml linux --verbose --setvars project.outputDirectory=.\ project.version=%VERSION%

xcopy /Y .\* %targetBinFolder%

cd ..
rmdir /S/Q		output
exit /b