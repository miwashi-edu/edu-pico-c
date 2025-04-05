# edu-pico-c

> Setup git connection

## Instructions

```bash
ssh dev@localhost:2222
```

### Install github client 

```bash
sudo apt install gh
gh auth login #login to github
gh auth refresh -h github.com -s admin:public_key
```

### Install github client 

```bash
sudo apt install gh
gh auth login #login to github
gh auth refresh -h github.com -s admin:public_key
```

### Install github client 

```bash
sudo apt install gh
gh auth login #login to github
```

### Add support for public key

```bash
gh auth refresh -h github.com -s admin:public_key
```


### Configure git

> Prepare `github-username` `email used in github` `your name`

```bash
git config --global init.defaultBranch main
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
git config --global github.user "your-github-username"
git config --global --list
```

### Generate public key

```bash
ssh-keygen -t ed25519 -C "your-email@example.com" -f ~/.ssh/id_ed25519 -N ""
cat ~/.ssh/id_ed25519.pub  # Add this to GitHub SSH keys
gh ssh-key add ~/.ssh/id_ed25519.pub --title "My Dev Machine"
ssh -T git@github.com  # Test SSH login
```
