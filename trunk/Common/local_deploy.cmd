@echo off
set src=%1
set dst=%2
set src=%src:/=\%
set dst=%dst:/=\%
xcopy /Y %src% %dst%