#!/bin/bash
set -e
echo "Please ensure you ran this script as a NORMAL USER, not as root (or with sudo)"
echo "Installing..."
install -D -t $HOME/bin bpkg
chmod u+x $HOME/bin/bpkg
echo "export PATH=$HOME/bin:$PATH" >> $HOME/.bashrc
echo "Install complete! Run exec bash or close and re-open your terminal to finish install!"

