# Introduction
**lspac** is a helper tool for `pacman`, built using the `libalpm` library.
It's main purpose is to fetch information about local packages on Arch Linux
and print it to the `stdout` in a way that it's friendly for parsing, so
it facilitates the creation of scripts that deals with pacman package information.

# Installation
To install `lspac` simply follow the steps below:
```
git clone https://github.com/pvpscript/lspac
cd lspac
make
sudo make install
```

# Usage
`lspac [OPTIONS] [PACKAGE]`

## Options
TODO: Add options list.

# Manual page
For extra help and information about this tool's usage, refer to the `lspac(1)` manual page.

# Reference
The library used was the pacman `libalpm` which is provided with the core pacman package.
It's source code can be found [here](https://github.com/devkitPro/pacman).

Note that there's still no manual page for this library, as they claim it is still under construction,
but the header file might be able to provide enough information for some development.

Another important project that helped a lot in the development of this tool, was `pacutils`,
which, by reading [their code](https://github.com/andrewgregory/pacutils) I've got enough
insight to how the `libalpm` worked.
