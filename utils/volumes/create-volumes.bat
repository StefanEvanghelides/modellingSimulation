@echo off

:: Create the volumes used in docker-compose
docker volume create modsim-data
docker volume create modsim-plotting-result
