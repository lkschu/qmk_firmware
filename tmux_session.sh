#!/bin/bash


SUBDIR="./keyboards/crkbd/keymaps/lkschu"

err() {
    echo "Can't go to directory: $SUBDIR"
    exit 1
}



cd  "$SUBDIR" || err

tmux -u new-window -t "qmk_firmware" -n 'VIM' 'vim keymap.c; zsh'
tmux -u new-window -t "qmk_firmware" -n 'COMP' 'cd ../../../..; ranger; zsh'

# tmux -u at -t "ziglings_org"
