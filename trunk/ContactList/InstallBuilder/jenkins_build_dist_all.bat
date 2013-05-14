set targetBinFolder=C:\project\Organizer\distrib

mkdir output
cd output

for /f "eol=# delims== tokens=1,2" %%i in (..\version_number.txt) do (
	set VERSION=%%j
)

echo version: %VERSION%

%IBDIR%\bin\builder build ..\ContactList.xml windows --verbose --setvars project.outputDirectory=%WORKSPACE%\output project.version=%VERSION%
%IBDIR%\bin\builder build ..\ContactList.xml linux --verbose --setvars project.outputDirectory=%WORKSPACE%\output project.version=%VERSION%
xcopy /Y .\* %targetBinFolder%

cd ..
rmdir /S/Q		output
exit /b