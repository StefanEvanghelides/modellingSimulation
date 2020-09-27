@echo off

:: Copy the cassandra-migration schema
call .\utils\volumes\add-data-to-1-container.bat -v cassandra-schema -s .\conf\cassandra\schema\.

:: Copy the redis configuration file.
call .\utils\volumes\add-data-to-1-container.bat -v redis-conf -s .\conf\redis\.
