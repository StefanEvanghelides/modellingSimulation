@echo off

:: Copy data from modsim-data volume to local
call .\utils\volumes\add-data-from-1-container.bat -v modsim-data -s .\data\.
