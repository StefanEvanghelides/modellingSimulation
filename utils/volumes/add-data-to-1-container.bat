:: This script is ideally run only once when the volumes are created.
:: This script is based on one of the answers from the following link:
:: https://unix.stackexchange.com/questions/31414/how-can-i-pass-a-command-line-argument-into-a-shell-script
:: (accessed September 13th, 2020).
@echo off

:Getops
 if /I "%1" == "-h" goto Help
 if /I "%1" == "-v" set volume_name=%2
 if /I "%3" == "-s" set path_to_source=%4

if not %volume_name%=="" if not %path_to_source%=="" goto Continue

:Help
  echo:
  echo: Usage: add-data-to-1-container.bat -v volume_name -s path_to_source
  echo:   -v Name or volume mounted on the container
  echo:   -s Path to the source data on the host
  echo:
  exit 1

::::::::::::::::::::::::::::::::::::::::::::::::::::::;

:Continue

:: Create a dummy container, needed to execute the `docker cp` command.
:: Finally, remove the dummy container.
:: Note: we use "hello world" because it is a very lightweight container.
docker container create --name dummy -v %volume_name%:/root hello-world
docker cp %path_to_source% dummy:/root
docker rm dummy

