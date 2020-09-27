@echo off

:: Copy data from modsim-data volume to local
call .\utils\volumes\add-data-from-1-container.bat -v modsim-data -s .\data\.

:: Copy data from modsim-plotting-results volume to local
call .\utils\volumes\add-data-from-1-container.bat -v modsim-plotting-result -s .\plotting_result\.
