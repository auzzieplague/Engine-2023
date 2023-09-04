@echo off
setlocal

:: Create build directory if not exists
if not exist build mkdir build

:: Navigate to build directory
cd build

:: Run CMake to generate build files
cmake ..

:: Build the project using MSBuild (for Visual Studio)
MSBuild TinkerEngine.sln /p:Configuration=Release

:: Copy the library to C:\src\lib
xcopy /y Release\TinkerEngine.lib C:\src\lib\

:: Copy header files to C:\src\headers
xcopy /y ..\core\*.h C:\src\headers\
xcopy /y ..\engine\*.h C:\src\headers\

:: Finish
echo.
echo Deployment completed.

endlocal
