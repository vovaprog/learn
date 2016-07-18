#!/bin/bash

IMAGE_NAME=$1
FILE_NAME=./images/${IMAGE_NAME}.img

USAGE="USAGE: mount_image.sh image_name"
if [ -z "$IMAGE_NAME" ] || [ ! -f $FILE_NAME ]
then
    echo $USAGE
    exit -1
fi

MOUNT_FOLDER=/var/chroot/$IMAGE_NAME

mkdir --parents $MOUNT_FOLDER

losetup /dev/loop0 $FILE_NAME
mount /dev/loop0 $MOUNT_FOLDER

