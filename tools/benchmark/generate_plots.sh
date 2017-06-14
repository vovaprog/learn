#!/bin/bash

PLOTDIR="./plots"

if [ -d "$PLOTDIR" ]; then
  rm -r $PLOTDIR
fi
mkdir $PLOTDIR

