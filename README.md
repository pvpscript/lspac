# Introduction
**lspac** is a helper tool for `pacman`, built using the `libalpm` library.
It's main purpose is to fetch information about packages from `pacman`
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
`lspac [OPTIONS] [<PACKAGE> ...]`

## Options
`-d, --dbpath PATH`

Set pacman dbpath.

`-f, --field-delim CHAR`

Set the field used between each selected output field (default: tab).

`-i, --inner-delim CHAR`

Set the inner values delimiter (default: space).

`-o, --output LIST`

Set the output fields list (for more information, refer to `lspac --help`).

`-p, --pkg-delim CHAR`

Set the delimiter used between each prompted package.

`-r, --root PATH`

Set the filesystem root dir.

`-s, --surround CHAR`

Set the character used to surround each output value (default: double quotes).

`-b, --bytes`

Display package size as bytes, instead of human readable.

`-P, --pairs`

Show outputs in a KEY="VALUE" fashion.

`-u, --unix`

Display dates as unix timestamp, instead of human readable.

`-w, --raw`

Remove surrounding characters (overwrites -s).

`-B, --basic`

Show basic informations about a package.
Same as `-o PROVIDES,DEPENDS,CONFLICTS,REPLACES,CHECKDEPENDS,MAKEDEPENDS`

`-R, --relations`

Show the relations of a given package.
Same as `-o DBNAME,BASENAME,VERSION,DESC,ARCH,URL,PACKAGER,SIZE,BUILDDATE,INSTALLDATE`

`-O, --output-all`

Shows every single available output value.

`-h, --help`

Shows help menu.

`-v, --version`

Displays version.


# Manual page
For extra help and information about this tool's usage, refer to the `lspac(1)` manual page.

# Reference
This project was strongly inspired by `lsblk`, a tool from
[util-linux](https://github.com/karelzak/util-linux/) that lists block devices.
By reading its code, I was able to absorb enough information in how a proper
input parsing is done, as well as the clever `enum` + `struct array` solution
for associating numerical values with strings and their respective information.
I really recommend taking a look at the code, it's very concise and very well
written; a delightful experience to the eyes and mind of every programmer.

The library used was the pacman `libalpm` which is provided with the core pacman package.
It's source code can be found [here](https://github.com/devkitPro/pacman). Note that
there's still no manual page for this library, as they claim it is still under construction,
but the header file might be able to provide enough information for some development.

Another important project that helped a lot in the development of this tool, was `pacutils`,
which, by reading [their code](https://github.com/andrewgregory/pacutils) I've got enough
insight to how the `libalpm` worked.
