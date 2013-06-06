echo off
C:\SiLabs\MCU\IDEfiles\C51\BIN\C51.exe "C:\Users\j.nielsen\Documents\SiLabs\Rykerbot\main.c" DB OE BR  
C:\SiLabs\MCU\IDEfiles\C51\BIN\C51.exe "C:\Users\j.nielsen\Documents\SiLabs\Rykerbot\UART.c" DB OE BR  
C:\SiLabs\MCU\IDEfiles\C51\BIN\C51.exe "C:\Users\j.nielsen\Documents\SiLabs\Rykerbot\PCA.c" DB OE BR  
C:\SiLabs\MCU\IDEfiles\C51\BIN\bl51.exe @"C:\Users\j.nielsen\Documents\SiLabs\Rykerbot\cyglink.txt"
C:\SiLabs\MCU\IDEfiles\C51\BIN\OH51.EXE "C:\Users\j.nielsen\Documents\SiLabs\Rykerbot\RykerBot"
del *.OBJ
del *.LST