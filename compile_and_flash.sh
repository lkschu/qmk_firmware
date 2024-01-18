#!/bin/bash


set -e



qmk compile --clean -kb crkbd -km lkschu -e CONVERT_TO=elite_pi -j 0

udisksctl mount -b /dev/sda1 --no-user-interaction

cp ~/Akten/qmk_firmware/crkbd_rev1_lkschu_elite_pi.uf2 /media/lks/RPI-RP2/
