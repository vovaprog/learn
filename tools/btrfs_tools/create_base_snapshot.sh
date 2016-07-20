#!/bin/bash

IMAGE_NAME=$1
FILE_NAME=./images/${IMAGE_NAME}.img
SOURCE_NAME=$2
DEST_NAME=$3

USAGE="USAGE: create_base_snapshot.sh image_name source_name dest_name"
if [ -z "$IMAGE_NAME" ] || [ ! -f $FILE_NAME ] || [ -z "$SOURCE_NAME" ] || [ -z "$DEST_NAME" ]
then
    echo $USAGE
    exit -1
fi

MOUNT_FOLDER=/var/chroot/$IMAGE_NAME

btrfs subvolume snapshot $MOUNT_FOLDER/bases/$SOURCE_NAME $MOUNT_FOLDER/bases/$DEST_NAME

