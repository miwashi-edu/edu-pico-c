# edu-pico-c

> Setup git connection

## Instructions


#### Configure git (in container)

> This is one time only

```bash
git config --global init.defaultBranch main
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
git config --global github.user "your-github-username"

ssh-keygen -t ed25519 -C "your-email@example.com" -f ~/.ssh/id_ed25519 -N ""
cat ~/.ssh/id_ed25519.pub  # Add this to GitHub SSH keys

ssh -T git@github.com  # Test SSH login

git config --global --list
```
