# edu-pico-c

> Setup raspberry docker machine
>
> Memorising not priotized, when you don't have more important parts to memorise.

## Premises

### iotnet exists

```bash
docker network create --driver bridge --subnet 192.168.2.0/24 --gateway 192.168.2.1 iotnet
```

### need to remove old conatiner

```bash
docker stop rpi5-dev
docker rm rpi5-dev
```

### Configure git

> This is one time only

```bash
git config --global init.defaultBranch main
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
git config --global github.user "your-github-username"

ssh-keygen -t ed25519 -C "your-email@example.com" -f ~/.ssh/id_ed25519 -N "" #Generate SSH key
cat ~/.ssh/id_ed25519.pub #Print it on screen for copying and adding to github SSH keys.

# Test git login
ssh -T git@github.com

git config --global --list # Check global config
#git config --list # Repository config
```

## Instructions

```bash
docker run -d --name rpi5-dev \
    --network iotnet \
    --hostname rpi5-dev \
    -p 2222:22 \
    -e TZ=UTC \
    balenalib/raspberrypi5-debian:bookworm \
    /bin/bash -c "while true; do sleep 30; done"
```

## Install c development environment

```bash
docker exec -it rpi5-dev bash -c "
apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    gdb-multiarch \
    openssh-server \
    sudo \
    vim \
    nano \
    gdb \
    git \
    python3 \
    && mkdir -p /var/run/sshd"
```

## Add dev user

> Change user and password

```bash
docker exec -it rpi5-dev bash -c "
useradd -m -s /bin/bash [user] && \
echo '[user]:[password]' | chpasswd && \
usermod -aG sudo [user]"
```

## Enable SSH

> If the container stops, you need to run: `docker exec -it rpi5-dev bash -c "service ssh restart"`

```bash
docker exec -it rpi5-dev bash -c "
sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
service ssh restart"
```

## Setup zsh  (zeeshell) - optional

> It requires you logout and login again
> When you login next time you are asked about options, choose 2.

```bash
sudo apt update
sudo apt install zsh -y
chsh -s $(which zsh)
```

> Optional add [Oh My Zsh](https://ohmyz.sh) (follow instructions)
> You need to logout first to start zsh.
```bash
#optional Oh My Zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

## Login

```bash
ssh [user]@localhost -p 2222

# if WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!
# vi ~/.ssh/known_hosts
# remove key for localhost:2222

cd ~
mkdir ws

# ctrl-d to end session
```

## Generate locale

> This starts a GUI where you use space to choose sv_SE as locale.

```bash
sudo locale-gen sv_SE.UTF-8
sudo dpkg-reconfigure locales
```

## Configure vim

```bash
echo 'set nocompatible' >> ~/.vimrc
```

