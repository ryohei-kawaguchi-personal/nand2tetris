@echo off
setlocal enabledelayedexpansion

for /L %%n in (1, 1, 15) do (
rem    echo     Nand^(a=a[%%n], b=b[%%n], out=nout%%n^);
    set /a plus1=%%n + 1 
rem    echo     Or^(a=out%%n, b=in[!plus1!], out=out!plus1!^);
    echo    FullAdder^(a=a[%%n], b=b[%%n], c=carry%%n, carry=carry!plus1!, sum=out[%%n]^);
)