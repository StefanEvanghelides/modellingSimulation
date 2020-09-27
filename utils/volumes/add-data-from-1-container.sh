#!/bin/bash
# This script is ideally run only once when the volumes are created.
# This script is based on one of the answers from the following link:
# https://unix.stackexchange.com/questions/31414/how-can-i-pass-a-command-line-argument-into-a-shell-script
# (accessed March 7th, 2020).
#
# NOTE: This scripts does the opposite of the add-data-to-1-continer,
# i.e. this script copies data from the volume to the local host.
#

#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -v volume_name -s path_to_source"
   echo -e "\t-v Name or volume mounted on the container"
   echo -e "\t-s Path to the source data on the host"
   exit 1 # Exit script after printing help
}

while getopts "v:s:" opt
do
   case "$opt" in
      v ) volume_name="$OPTARG" ;;
      s ) path_to_source="$OPTARG" ;;
      ? ) helpFunction ;; # Print helpFunction in case parameter is non-existent
   esac
done

# Print helpFunction in case parameters are empty
if [ -z "$volume_name" ]
then
   echo "The -v parameter is empty";
   helpFunction
fi
if [ -z "$path_to_source" ]
then
   echo "The -s parameter is empty";
   helpFunction
fi

##############################################

# Create a dummy container, needed to execute the `docker cp` command.
# Finally, remove the dummy container.
# Note: we use "hello world" because it is a very lightweight container.
docker container create --name dummy -v $volume_name:/root hello-world
docker cp dummy:/root/. $path_to_source 
docker rm dummy

