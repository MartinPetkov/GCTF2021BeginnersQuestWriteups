# Google CTF 2021 - Beginners Quest Writeups

This repository contains writeups for my solutions to all the challenges in the [Google CTF 2021 Beginners Quest](https://capturetheflag.withgoogle.com/beginners-quest). The CTF took place on August 27-29 2021 and consisted of 18 challenges ranging in type from coding, reversing, web exploitation, pwn, data parsing, steganography, and more.

**I highly encourage you try to solve the challenges yourself before reading the solutions here**, or use them sparingly to get unstuck. This is the best way to learn, especially with topics you are new to and unfamiliar with. I certainly am not an expert in all categories and I learned a great deal from this CTF.

## Structure

There's one folder for each challenge. There you'll find:

* The "story" for that challenge, which is very loose but does at times give useful hints;
* All relevant files that you receive as a participant;
* A step-by-step writeup of how I solved the challenge;
* A solve script, where feasible;
* And finally, the flag itself.

I also try to describe the intuition and how one might approach this kind of problem, as I feel that this is the key skill that CTFs help you develop.

## Tools used

These are some of the tools used throughout the writeups:

* [`bash`](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) - A popular [Unix shell](https://en.wikipedia.org/wiki/Unix_shell) that comes with most modern Linux distros. Used in the majority of challenges, since only a few are web-only.
* [`file`](https://linux.die.net/man/1/file) - An extremely helpful utility which attempts to identify the type of a file. It's important to remember that in Linux, [file extensions](https://en.wikipedia.org/wiki/Filename_extension) have no inherent relation to the file type; that's entirely determined by data in the file and how it's parsed.
* [`tar`](https://www.gnu.org/software/tar/)/[`unzip`](https://linux.die.net/man/1/unzip) - Utilities for working with archives.
* [`curl`](https://en.wikipedia.org/wiki/CURL) - A command line utility for requesting URLs. Allows interacting with and automating challenges on the web.
* [`wget`](https://www.gnu.org/software/wget/) - Another utility for downloading files from URLs. More convenient to use in some ways.
* [`hexdump`](https://linux.die.net/man/1/hexdump) - A utility for dumping the bytes from a file in [hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal) format.
* [`xxd`](https://linux.die.net/man/1/xxd) - Another utility for parsing and dealing with hex data.
* [`wc`](https://linux.die.net/man/1/wc) - A utility that counts bytes, characters, words or lines.
* [`exiftool`](https://exiftool.org/) - A utility for reading, writing and editing metadata on files. Great for parsing metadata from images.
* [`netcat`](https://en.wikipedia.org/wiki/Netcat) - An extremely useful utility for working with network connections. Most often in CTFs this is used to connect to a remote server hosting a CTF challenge.
* [Python 3](https://www.python.org/) - A programming language. Very popular, very powerful, and extremely ergonomic and comfortable to program in. It can also be used to write scripts.
* [CyberChef](https://gchq.github.io/CyberChef/) - A "Swiss Army Knife" of data conversion. Has a huge variety of methods for converting data between different formats (binary, hex, text, etc.).

## Disclaimers

For all challenges I used Chrome as my browser and Debian Linux as my OS.

Depending on when you read this post, the servers may still be up and verifying flags, as there was no official end date. If they're down, you can still solve several challenges offline and verify with the flags in the repo.

I received a lot of help and nudges from people in the [official Discord channel](https://discord.com/channels/856899439833382935/880198649999683585). Huge thank you to everyone who helped me through and did your best not to just give the answer away!
