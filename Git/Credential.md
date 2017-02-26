## Caching github password in github

Tip: You need Git 1.7.10 or newer to use the credential helper.

If you clone GitHub repositories using SSH, then you authenticate using SSH keys instead of a username and password.

If you prefer working with the command line, you can also install a native Git shell, such as Git for Windows. With Git for Windows, running the following in the command line will store your credentials:

```
$ git config --global credential.helper wincred
```

### understanding credentials from the OSX Keychain

refer: https://help.github.com/articles/updating-credentials-from-the-osx-keychain/

You'll need to update your saved username and password in the *git-credential-osxkeychain* helper if you change your password or username on GitHub.

#### Updating your credentials via Keychain Access

1. Spotlight Search barIn Finder, search for the Keychain Access app.
2. In Keychain Access, search for github.com.
3. GitHub Password Entry in KeychainFind the "internet password" entry for github.com.
4. Edit or delete the entry accordingly.

#### Deleting your credentials via the command line

Through the command line, you can use the credential helper directly to erase the keychain entry.

To do this, type the following command:
```
$ git credential-osxkeychain erase
host=github.com
protocol=https
[Press Return]
```

If it's successful, nothing will print out. To test that it works, try and clone a repository from GitHub. If you are prompted for a password, the keychain entry was deleted.

ref: http://stackoverflow.com/questions/5343068/is-there-a-way-to-skip-password-typing-when-using-https-on-github

With Git version 1.7.9 and later

Since Git 1.7.9 (released in late January 2012), there is a neat mechanism in Git to avoid having to type your password all the time for HTTP / HTTPS, called credential helpers. (Thanks to dazonic for pointing out this new feature in the comments below.)

With Git 1.7.9 or later, you can just use one of the following credential helpers:

git config --global credential.helper cache
... which tells Git to keep your password cached in memory for (by default) 15 minutes. You can set a longer timeout with:

git config --global credential.helper "cache --timeout=3600"
(That example was suggested in the GitHub help page for Linux.) You can also store your credentials permanently if so desired, see the other answers below.

GitHub's help also suggests that if you're on Mac OS X and used Homebrew to install Git, you can use the native Mac OS X keystore with:

git config --global credential.helper osxkeychain
For Windows, there is a helper called Git Credential Manager for Windows or wincred in msysgit.

git config --global credential.helper wincred # obsolete
With Git for Windows 2.7.3+ (March 2016):

git config --global credential.helper manager
For Linux, you can use gnome-keyring(or other keyring implementation such as KWallet).
