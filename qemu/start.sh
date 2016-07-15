#!/bin/bash

qemu-system-x86_64 -enable-kvm -smp 2 -m 1024 -vga qxl -hda ./disk.qcow2
# -redir tcp:2222::22 -redir tcp:8080::80 -redir tcp:5000::5000

