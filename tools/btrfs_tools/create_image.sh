#!/bin/bash

USAGE="USAGE: create_image.sh image_name"

IMAGE_NAME=$1

if [ -z "$IMAGE_NAME" ]
then
    echo $USAGE
    exit -1
fi

FILE_NAME=./images/${IMAGE_NAME}.img

mkdir --parents ./images
truncate -s 10G $FILE_NAME
losetup /dev/loop0 $FILE_NAME
mkfs.btrfs /dev/loop0

MOUNT_FOLDER=/var/chroot/$IMAGE_NAME

mkdir --parents $MOUNT_FOLDER
mount /dev/loop0 $MOUNT_FOLDER
btrfs subvolume create $MOUNT_FOLDER/bases
btrfs subvolume create $MOUNT_FOLDER/snapshots
btrfs subvolume create $MOUNT_FOLDER/bases/${IMAGE_NAME}_debootstrap
umount $MOUNT_FOLDER

losetup -d /dev/loop0


