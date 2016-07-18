#!/bin/bash

IMAGE_NAME=$1
FILE_NAME=./images/${IMAGE_NAME}.img
SNAPSHOT_NAME=$2

USAGE="USAGE: delete_snapshot.sh image_name snapshot_name.sh"
if [ -z "$IMAGE_NAME" ] || [ -z "$SNAPSHOT_NAME" ] || [ ! -f $FILE_NAME ]
then
    echo $USAGE
    exit -1
fi


USAGE="USAGE: delete_snapshot.sh image_name snapshot_name"

MOUNT_FOLDER=/var/chroot/$IMAGE_NAME

btrfs subvolume delete $MOUNT_FOLDER/snapshots/$SNAPSHOT_NAME

