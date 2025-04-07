# edu-pico-c

> Setup git connection

## Instructions

```bash
ssh dev@localhost -p 2222
```

### Generate public key

```bash
ssh-keygen -t ed25519 -C "your-email@example.com" -f ~/.ssh/id_ed25519 -N ""
cat ~/.ssh/id_ed25519.pub  # Add this to GitHub SSH keys
```

### Install github client 

```bash
sudo apt install gh
gh auth login #login to github # paste code in https://github.com/login/device
gh auth refresh -h github.com -s admin:public_key # paste code in https://github.com/login/device
```

### Add support for public key

```bash
gh ssh-key add ~/.ssh/id_ed25519.pub --title "My Dev Machine"
ssh -T git@github.com  # Test SSH login
```


### Configure git

> Prepare `github-username` `email used in github` `your name`

```bash
git config --global init.defaultBranch main
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
git config --global github.user "your-github-username"
git config --global --add safe.directory /opt/pico-sdk
git config --global --list
```

### Create a project with github as upstream (Optional)

```bash
cd ~/ws
mkdir pico-firmware
cd pico-firmware
git init
echo "# pico-firmware" > README.md
git add .
git commit -m "Initial commit"
gh repo create pico-firmware --public --source=. --remote=origin --push
```
