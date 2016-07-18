#!/bin/bash

IMAGE_NAME=$1
FILE_NAME=./images/${IMAGE_NAME}.img

USAGE="USAGE: create_build_environment.sh image_name"
if [ -z "$IMAGE_NAME" ] || [ ! -f $FILE_NAME ]
then
    echo $USAGE
    exit -1
fi


MOUNT_FOLDER=/var/chroot/$IMAGE_NAME

bash ./mount_image.sh $IMAGE_NAME

btrfs subvolume snapshot $MOUNT_FOLDER/bases/${IMAGE_NAME}_configured $MOUNT_FOLDER/snapshots/build_root

