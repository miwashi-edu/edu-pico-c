# edu-pico-c

## 🧠 Teaching Tip

> **In this tutorial, we're using Pico SDK version `2.1.1`**
>

## Premises

### iotnet exists

```bash
docker network inspect iotnet >/dev/null 2>&1 || \
docker network create --driver bridge --subnet 192.168.2.0/24 --gateway 192.168.2.1 iotnet
```

### need to remove old conatiner

```bash
docker stop rpi5-dev
docker rm rpi5-dev
```

## Instructions


### Create Pico Development Container

```bash
mkdir -p ~/pico-share
docker run -d --name rpi5-dev \
    --network iotnet \
    --hostname rpi5-dev \
    -p 2222:22 \
    -v ${HOME}/pico-share:/home/dev/share \
    -e TZ=UTC \
    -e PICO_SDK_PATH=/opt/pico-sdk \
    balenalib/raspberrypi5-debian:bookworm \
    /bin/bash -c "while true; do sleep 30; done"
```

### Install c development environment

```bash
docker exec -it rpi5-dev bash -c "
apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
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

### Add dev user

```bash
docker exec -it rpi5-dev bash -c "
useradd -m -s /bin/bash dev && \
echo 'dev:dev' | chpasswd && \
usermod -aG sudo dev"

docker exec -it rpi5-dev bash -c "
echo 'export PICO_SDK_PATH=/opt/pico-sdk' >> /home/dev/.bashrc && \
echo 'export PICO_SDK_PATH=/opt/pico-sdk' >> /home/dev/.zshrc && \
chown -R dev:dev /home/dev"
```

### Enable SSH

> If the container stops, you need to run: `docker exec -it rpi5-dev bash -c "service ssh restart"`

```bash
docker exec -it rpi5-dev bash -c "
sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
service ssh restart"
```

### Setup zsh  (zeeshell) - optional

> It requires you logout and login again
> When you login next time you are asked about options, choose 2.

```bash
docker exec -it rpi5-dev bash -c "
apt-get update && apt-get install -y zsh && \
chsh -s \$(which zsh) dev"
```

### Install pico-sdk

```bash
docker exec -it rpi5-dev bash -c "
rm -rf /opt/pico-sdk && \
git clone https://github.com/raspberrypi/pico-sdk.git /opt/pico-sdk && \
cd /opt/pico-sdk && \
git checkout 2.1.1 && \
git submodule update --init --recursive && \
rm -f /etc/profile.d/pico-sdk.sh && \
echo 'export PICO_SDK_PATH=/opt/pico-sdk' > /etc/profile.d/pico-sdk.sh"
```

### Install picotool

```bash
docker exec -it rpi5-dev bash -c "
apt-get update && apt-get install -y libusb-1.0-0-dev git cmake build-essential && \
rm -rf /opt/picotool && \
git clone https://github.com/raspberrypi/picotool.git /opt/picotool && \
cd /opt/picotool && \
mkdir build && cd build && \
cmake .. && make && make install"
```

### Generate locale

```bash
docker exec -it rpi5-dev bash -c "
apt-get install -y locales && \
echo 'sv_SE.UTF-8 UTF-8' >> /etc/locale.gen && \
locale-gen sv_SE.UTF-8 && \
update-locale LANG=sv_SE.UTF-8"
```

### Configure vim

```bash
docker exec rpi5-dev bash -c "echo 'set nocompatible' >> \$(eval echo ~dev)/.vimrc"
```

#### Change Username (optional)

```bash
docker exec -it rpi5-dev bash -c "
usermod -l [USER] dev && \
usermod -d /home/[USER] -m [USER] && \
groupmod -n [USER] dev && \
echo '[USER]:[PASSWORD]' | chpasswd"
```

### Login

> If you get `WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!` then  
> vi ~/.ssh/known_hosts  
> remove key for localhost:2222
> (or with sed) `sed -i.bak '/\[localhost\]:2222/d' ~/.ssh/known_hosts`

```bash
ssh dev@localhost -p 2222 # Password is dev if you didn't change user

# if WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!
# vi ~/.ssh/known_hosts
# remove key for localhost:2222
# sed -i.bak '/\[localhost\]:2222/d' ~/.ssh/known_hosts

cd ~
mkdir ws

# ctrl-d to end session
```

#### Oh My Zsh (optional - in container)

> Optional add [Oh My Zsh](https://ohmyz.sh) (follow instructions)
> You need to logout first to start zsh.
```bash
#optional Oh My Zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```
