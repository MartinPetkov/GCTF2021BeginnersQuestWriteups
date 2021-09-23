# Challenge #18: Strange Virtual Machine

Category: `rev`

## Story

>You press a button and enter through a tinted glass door. There is a vast oil painting on the wall that depicts a bold man with a scar under his left eye, under his arms rests a white chubby cat. Below the painting is the very same man, and he’s addressing you: "Well, well, well. Isn’t it the trouble maker? Huh, how did you get past the guards? Well, I have a final offer for you. I’ll let you live only on one condition: START WORKING FOR ME! BWAHAHAHAHA-" While he goes on with his monologue about conquering the world and some twisted philosophy about how he is actually the good guy and so on you start discretely fiddling with a control panel labeled "Self destruction". You need to quickly figure out the activation code while he’s distracted.<br/><br/>
>Everyone is coming up with their own programming language these days, so I came up with my own architecture. You can use it to run the attached program that will print the flag for you.

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O strange-vm.zip https://storage.googleapis.com/gctf-2021-attachments-project/c48931b8e0b86e44cc5bcc08b9e1510d05f0bb0cde039c2e96147379fcb88d2f93a9acac37bd7093a92e7fdadce862835fadc0951d76bccbc8afd055ae736099
$ unzip strange-vm.zip
Archive:  strange-vm.zip
 extracting: vm-impl.tgz
 extracting: vm.rom
$ tar -xvzf vm-impl.tgz
vm/
vm/Cargo.toml
vm/src/
vm/src/lib.rs
vm/.gitignore
vm-cli/
vm-cli/Cargo.toml
vm-cli/src/
vm-cli/src/main.rs
vm-cli/Cargo.lock
vm-cli/.gitignore
```

Let's look at the files and see what we're dealing with.

First, the [`.rom`](https://fileinfo.com/extension/rom) file. What is this? According to standard documentation it's extracted memory from a hardware read-only memory chip. Trying to fingerprint it doesn't help:

```sh
$ file vm.rom
vm.rom: data
```

For now, let's assume that since the challenge is called "Strange [**Virtual Machine (VM)**](https://en.wikipedia.org/wiki/Virtual_machine)", this `vm.rom` file is just for a VM that we're supposed to run somehow.

Let's look at the rest of the files.

`vm/` and `vm-cli/` look like source trees. [`Cargo.toml`](https://doc.rust-lang.org/cargo/reference/manifest.html) is the machine manifest file used by [`cargo`](https://doc.rust-lang.org/cargo/index.html), the [package manager](https://en.wikipedia.org/wiki/Package_manager) used by the [Rust](https://www.rust-lang.org/) programming language (confirmed by the [`.rs`](https://fileinfo.com/extension/rs) extension on the other files). `cargo` is how we build Rust programs.

### Building and running the VM

Before even looking at the code, let's try to build it and see what we get. It takes a bit of reading to find out how to install the toolchain and build Rust programs (I'm not a Rust developer normally), but it's not too bad in the end.

```sh
$ cd vm/

vm $ cargo build
   Compiling vm v0.1.0 (vm)
    Finished dev [unoptimized + debuginfo] target(s) in 1.60s

vm $ ls
Cargo.lock  Cargo.toml  src  target

vm $ ls -R target/
target/:
CACHEDIR.TAG  debug

target/debug:
build  deps  examples  incremental  libvm.d  libvm.rlib

target/debug/build:

target/debug/deps:
libvm-79a062c6c105b31e.rlib  libvm-79a062c6c105b31e.rmeta  vm-79a062c6c105b31e.d

target/debug/examples:

target/debug/incremental:
vm-368h5a3ci7fc5

target/debug/incremental/vm-368h5a3ci7fc5:
s-g2natv3np2-1c7k6yv.lock  s-g2natv3np2-1c7k6yv-qyx5b7ka4fbv

target/debug/incremental/vm-368h5a3ci7fc5/s-g2natv3np2-1c7k6yv-qyx5b7ka4fbv:
10t332n50yp9zaze.o  128juicv68egnae3.o  1pamh7ah9np2iq6b.o  1wy4tvlhlpayg8oy.o  2759oi4yqvxqwn8a.o  3jhio75kg3urw80i.o  44vsj8wamykush9h.o  4s6ery6e6bsc3c5w.o  8435jxhkqumkkyc.o  d1p1we09nzvvfir.o  f2zce50fhvydyvy.o  n5ffjduwd27nd54.o  work-products.bin
123sl02o6ffrzj1m.o  12udi094mf7sv5ah.o  1pkgoprc2ichfbo0.o  1z4zte6tbeamj4um.o  306y4ebwm6373cw4.o  3yifvic6panetyg.o   463igwcfelb06llx.o  4vwvq7iu5dt9q3i5.o  bs766hd2t76pdbi.o  dep-graph.bin      jg2k6s9dmdf3l20.o  query-cache.bin    zhoj0h5gohwljzj.o
```

Okay, so it did a bunch of stuff and generated a bunch of files in the `target/` directory. I don't see anything runnable. Probably this was just library called, given the file was called `lib.rs`.

---

Let's try `vm-cli/` - presumably that will give us a [CLI](https://en.wikipedia.org/wiki/Command-line_interface) program to run.

```sh
$ cd vm-cli/

vm-cli $ ls
Cargo.lock  Cargo.toml  src

vm-cli $ cargo build
   Compiling vm v0.1.0 (vm)
   Compiling vm-cli v0.1.0 (vm-cli)
    Finished dev [unoptimized + debuginfo] target(s) in 1.07s

vm-cli $ ls -R target/
target/:
CACHEDIR.TAG  debug

target/debug:
build  deps  examples  incremental  vm-cli  vm-cli.d
...
```

This time I'm omitting most of the rest of the output, since we found a file we can run: `./target/debug/vm-cli`. Let's try it out.

```sh
$ ./vm-cli/target/debug/vm-cli -h
Error: Os { code: 2, kind: NotFound, message: "No such file or directory" }

$ ./vm-cli/target/debug/vm-cli --help
Error: Os { code: 2, kind: NotFound, message: "No such file or directory" }

$ ./vm-cli/target/debug/vm-cli help
Error: Os { code: 2, kind: NotFound, message: "No such file or directory" }

$ ./vm-cli/target/debug/vm-cli
Missing ROM
```

Okay, no help or flags or anything, but it does expect a rom. Let's give it what it wants.

```sh
$ ./vm-cli/target/debug/vm-cli vm.rom
CTF{ThisIsAVeryLongFlagAndYo^C
```

The first few characters came out right away, but this quickly slowed down until it took a minute for the last "o" to come out. If we let this run for a few years it will probably spit out the flag, but we don't have that kind of patience.

Time to dive into the code and/or the ROM and reverse-engineer the flag.

### Analyzing the Rust VM code

TODO













