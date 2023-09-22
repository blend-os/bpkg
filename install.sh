#!/bin/bash
set -e
if [ "$EUID" -eq 0 ]; then
    echo -e "\033[01m\033[31m>> e: \033[39mplease run the installer as a non-root user\033[0m"
    exit 1
fi
echo -e "\033[01m\033[36m>> i: \033[39minstalling\033[0m"
install -D -t $HOME/.bin bpkg
chmod u+x $HOME/.bin/bpkg
echo -e "export PATH=$HOME/.bin:\$PATH" >> $HOME/.bashrc
echo -e "\033[01m\033[36m>> i: \033[39minstall complete! run exec bash or close and re-open your terminal to finish install!\033[0m"
