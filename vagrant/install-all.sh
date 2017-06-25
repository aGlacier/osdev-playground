#!/bin/bash -x
set -e

MKDIR='mkdir -p'
PACMAN_S="sudo pacman -S --needed --noconfirm"

sudo pacman -Sy
$MKDIR ~/tmp
cd ~/tmp

# Install the basic useful apps
$PACMAN_S vim htop xterm \
          icewm ttf-dejavu terminus-font dmenu mc gdb cgdb net-tools tmux \
          ctags the_silver_searcher bash-completion meld git tig

cd /vagrant/conf/home/vagrant/toolchain
sudo pacman -U --noconfirm *.xz
cd ..


# Install all other packages
#$PACMAN_S tigervnc lightdm lightdm-gtk-greeter

$PACMAN_S qemu qemu-arch-extra xorriso mtools

# Copy source code
cd ~/
if [ ! -d osdev-playground ] ; then
    git clone https://github.com/aGlacier/osdev-playground.git osdev-playground
fi

sudo timedatectl set-ntp true
#$SUDO systemctl enable lightdm.service
