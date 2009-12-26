::CopyRight kongjianjun@gmail.com
::2007.7.1

@echo off


if "%1"=="" (
set/a a=1
) else set/a a=%1-1
set/a b=0
if "%2"=="" (
set/a c=2
) else set/a c=%2-1

echo                          *******Find Proxy********

::netsh interface ip set address name="本地连接" source=static addr=192.168.%b%.24 mask=255.255.255.0 >nul && echo *****Your IP:192.168.%b%.24 


:up
if %a% == 255 goto panduan

:goon
set/a a=%a%+1
echo Your gate:192.168.%b%.%a%
::netsh interface ip set address name="本地连接" gateway=192.168.%b%.%a% gwmetric=0

ping -n 1 220.181.37.4 |find "Reply from 220.181.37.4" >nul 2>nul && echo 大功告成！ && echo 192.168.%b%.%a% >>host.txt && nbtstat -A 192.168.%b%.%a% >>host.txt && goto win 
goto up
:panduan
set/a b=%b%+1 
if "%b%" == "%c%" goto end
set/a a=1 && netsh interface ip set address name="本地连接" source=static addr=192.168.%b%.24 mask=255.255.255.0 >nul && echo Gateway:  192.168.%b%.24  && goto goon

:win
for /l %%i in (1,1,8) do (

echo.
echo ********大功告成！
echo ********代理IP：192.168.%b%.%a%
echo. 
color cf
ping -n 1 127.1>nul
color fc
ping -n 1 127.1>nul
cls
)

echo ********大功告成！
echo ********代理IP：192.168.%b%.%a%
echo. 
color
:end
echo "Only once" > FindProxy.bat
