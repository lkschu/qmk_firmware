#!/bin/bash


set -e



qmk compile --clean -kb crkbd -km lkschu -e CONVERT_TO=elite_pi -j 0

sleep 1
udisksctl mount -b "$(findfs LABEL=RPI-RP2)" --no-user-interaction

cp ~/Akten/qmk_firmware/crkbd_rev1_lkschu_elite_pi.uf2 /media/lks/RPI-RP2/
