#!/bin/bash

IMAGE_NAME=$1
FILE_NAME=./images/${IMAGE_NAME}.img

USAGE="USAGE: debootstrap_ubuntu1404.sh image_name"
if [ -z "$IMAGE_NAME" ] || [ ! -f $FILE_NAME ]
then
    echo $USAGE
    exit -1
fi

MOUNT_FOLDER=/var/chroot/$IMAGE_NAME/bases/${IMAGE_NAME}_debootstrap

debootstrap --variant=buildd --arch amd64 trusty $MOUNT_FOLDER http://archive.ubuntu.com/ubuntu

