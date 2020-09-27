#!/bin/bash

# This computes the relative path of the current folder
# It is needed to access the other script.
MY_DIR=$(dirname $(readlink -f $0))

# Copy data from modsim-data volume to local
$MY_DIR/add-data-from-1-container.sh -v modsim-data -s $MY_DIR/../../data/.

# Copy data from modsim-plotting-results volume to local
$MY_DIR/add-data-from-1-container.sh -v modsim-plotting-result -s $MY_DIR/../../plotting_result/.


