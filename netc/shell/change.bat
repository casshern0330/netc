@echo off
CLS
color 17
@title �޸ı���IP��ַ By hucw 2012-04-10

:title
echo.	==<<�޸ı���IP��ַ >>==

echo.	1 �л����ַ�����

echo.	2 �л����ַ�����

echo.	3 �л�����֧����

echo.	9 �˳�

echo.	������ѡ����Ŀ����Ų����س���

set /p XUANXIANG=

if "%XUANXIANG%"=="1" goto 1
if "%XUANXIANG%"=="2" goto 2
if "%XUANXIANG%"=="3" goto 3
if "%XUANXIANG%"=="9" goto 9

:1
echo �л����ַ�����

netsh interface ip set address name = "��������" source=dhcp
netsh interface ip set dns name="��������" source=dhcp

echo �ɹ��л����ַ�����
pause
CLS
goto title

:2
echo �л����ַ�����

nterface ip set address "��������" static 10.208.231.56 255.255.255.0 10.208.231.254 1

echo �ɹ��л����ַ�����
pause
CLS
goto title

:9
