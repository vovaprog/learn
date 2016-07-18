#!/bin/bash

IMAGE_NAME=$1

USAGE="USAGE: umount_image.sh image_name"
if [ -z "$IMAGE_NAME" ]
then
    echo $USAGE
    exit -1
fi

umount /var/chroot/$IMAGE_NAME
losetup -d /dev/loop0
