::Rename to tournament.bat to run

:: "-w:" set width of the gameboard 
:: "-h:" set height of the gameboard
:: "-k:" set k of the gameboard
:: "-g:" set gravity of the gameboard 0 for no gravity, 1 for gravity on

::list the filepaths for the AIs and/or names of the AIs in the same directory as tournament.jar

::example 1
::java -jar tournament.jar "%~dp0\AverageAI\AverageAI.class" ::"%~dp0\PoorAI\PoorAI.class" "%~dp0\GoodAI\GoodAI.class"

::example 2 connect 4 w/ gravity. This will be run
::java -jar tournament.jar -w:7 -h:6 -k:4 -g:1 "%~dp0\AverageAI\AverageAI.class" "%~dp0\PoorAI\PoorAI.class" "%~dp0\GoodAI\GoodAI.class"
::java -jar tournament.jar -w:7 -h:6 -k:4 -g:1 cpp:"%~dp0\cppShell.exe" cpp:"%~dp0\cppShell.exe"
::"java -jar tournament.jar -w:7 -h:6 -k:4 -g:1 "%~dp0\AverageAI\AverageAI.class" "%~dp0\DummyAI.class"
java -jar tournament.jar -w:7 -h:6 -k:4 -g:1 cpp:"%~dp0\cppShell.exe" "%~dp0\DummyAI.class"
pause 