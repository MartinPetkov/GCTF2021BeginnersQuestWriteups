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

First, the [`.rom`](https://fileinfo.com/extension/rom) file. What is this? According to the link from a quick Google search, it's extracted memory from a hardware **r**ead-**o**nly **m**emory chip. Trying to fingerprint it doesn't help:

```sh
$ file vm.rom
vm.rom: data
$ strings vm.rom
$
```

For now, let's assume that since the challenge is called "Strange [**Virtual Machine (VM)**](https://en.wikipedia.org/wiki/Virtual_machine)", this `vm.rom` file is just for a VM that we're supposed to run somehow.

`vm/` and `vm-cli/` look like source trees. [`Cargo.toml`](https://doc.rust-lang.org/cargo/reference/manifest.html) is the machine manifest file used by [`cargo`](https://doc.rust-lang.org/cargo/index.html), the [package manager](https://en.wikipedia.org/wiki/Package_manager) used by the [Rust](https://www.rust-lang.org/) programming language (confirmed by the [`.rs`](https://fileinfo.com/extension/rs) extension on the other files). `cargo` is how we build Rust programs.

### Building and running the VM

Before even looking at the code, let's try to build it and run it. It takes a bit of reading to find out how to install the toolchain and build Rust programs (I'm not a Rust developer normally), but it's not too bad in the end.

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

Okay, so it did a bunch of stuff and generated a bunch of files in the `target/` directory. I don't see anything runnable. Probably this was just library code, given the file is called `lib.rs`.

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

Okay, no help or flags or anything, but it does expect a ROM. Let's give it what it wants.

```sh
$ ./vm-cli/target/debug/vm-cli vm.rom
CTF{ThisIsAVeryLongFlagAndYou^C
```

The first few characters came out right away, but this quickly slowed down until it took a minute for the last letter to come out. If we let this run for a few years it will probably spit out the flag, but we don't have that kind of patience.

Time to dive into the code and/or the ROM and reverse-engineer the flag.

### Analyzing the Rust VM code

Let's start with [lib.rs](vm/src/lib.rs).

First, there's this:

```rust
pub type Register = char;
pub const REG_RV: Register = 0 as Register;
pub const REG_ARG0: Register = 1 as Register;
pub const REG_ARG1: Register = 2 as Register;
pub const REG_FLAG: Register = 0xFF as Register;
```

It defines some [registers](https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm). Good to know, and suspicious that one of them is `REG_FLAG`.

```rust
// Instructions
#[derive(Copy, Clone, Debug)]
pub enum Instruction {
    Nop,
    MovConst { ... },
    MovReg { ... },
    MathOp { ... },
    PushReg(Register),
    PopReg(Register),
    PushConst(u32),
    JmpConst(u32),
    PopPc,
    Test { ... },
    JmpCond(u32),
    Call(u32),
    Strlen,
    CharAt,
    Print,
    Exit,
}
```

As the comment suggests, these are the instructions supported by the VM.

I'm not too good at reading Rust code, but nothing seemed of particular note in the rest of this file. It implements displaying the instructions and parsing the bytes from the ROM as `Instruction`s. The [Into trait](http://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/std/convert/trait.Into.html) was totally new to me, but it also is uninteresting, it just defines how one type converts into another.

---

Now let's look at [main.rs](vm-cli/src/main.rs).

Immediately, this catches my eye:

```rust
const INPUT_DATA: [u32; 63] = [
    66, 82, 66, 117, 75, 91, 86, 87, 31, 51, 222, 187, 112, 236, 9, 98, 34, 69, 0, 198, 150, 29,
    96, 10, 69, 26, 253, 225, 164, 8, 110, 67, 102, 108, 103, 162, 209, 1, 173, 130, 186, 5, 123,
    109, 187, 215, 86, 232, 23, 215, 184, 79, 171, 232, 128, 67, 138, 153, 251, 92, 4, 94, 93,
];
```

Could this be the flag?

```sh
$ python -c 'print("".join([chr(i) for i in [66, 82, 66, 117, 75, 91]]))'
BRBuK[
```

Alas, not quite, at least not as-is. Let's remember it for later though.

---

```rust
struct Vm {
    f: std::fs::File,
    registers: [u32; 256],
    stack: [u32; 64 * 1024],
    flag: bool,
    sp: usize,
}
```

So the VM has a file (the `vm.rom`), 256 registers, 64 KB of stack space, a `flag` bool, and a stack pointer (`sp`).

---

```rust
impl Vm {
    ....

    fn step(&mut self) -> std::io::Result<()> {
        let instruction = Instruction::read(&mut self.f)?;
        //println!("Display: {}", instruction);

        /*
        let pos = self.f.stream_position()?;
        println!(
            "{:04X} | sp={:04} | flg={} | {:?}",
            pos, self.sp, self.flag, instruction,
        );
        for (idx, v) in self.registers.iter().enumerate() {
            if *v > 0 {
                println!("{:?} -> {}", idx, v);
            }
        }
        */
        ...
    }
    ...
}
```

This is useful. Comments left behind in the source show us how to debug the VM by printing out each instruction and enumerating the registers.

If you uncomment this and try running the `vm.rom` file, the output is massive and there are no immediately obvious patterns. One thing that is useful though is printing out the instructions without running them; this can be done by uncommenting part of this and returning early (before the next section). See the file [rom_instructions.txt](rom_instructions.txt) for an instruction dump.

Moving on.

---

```rust
use Instruction::*;
match instruction {
    Nop => {}
    MovConst { reg, v } => self.registers[reg as usize] = v,
    MovReg { reg, reg2 } => self.registers[reg as usize] = self.registers[reg2 as usize],
    MathOp {
        reg_out,
        reg,
        op,
        reg2,
    } => {
        let r1 = self.registers[reg as usize];
        let r2 = self.registers[reg2 as usize];
        self.registers[reg_out as usize] = match op {
            3 => r1 + r2,
            4 => r1 - r2,
            5 => r1 * r2,
            6 => r1 / r2,
            _ => unimplemented!(),
        };
    }
    PushReg(reg) => {
        self.stack[self.sp] = self.registers[reg as usize];
        self.sp += 1;
    }
    PopReg(reg) => {
        self.registers[reg as usize] = self.stack[self.sp - 1];
        self.sp -= 1;
    }
    PushConst(c) => {
        self.stack[self.sp] = c;
        self.sp += 1
    }
    JmpConst(c) => {
        self.f.seek(std::io::SeekFrom::Start(c as u64))?;
    }
    PopPc => {
        self.f
            .seek(std::io::SeekFrom::Start(self.stack[self.sp - 1] as u64))?;
        self.sp -= 1;
    }
    Test { reg, op, reg2 } => {
        self.flag = match op {
            0 => self.registers[reg as usize] < self.registers[reg2 as usize],
            1 => self.registers[reg as usize] <= self.registers[reg2 as usize],
            _ => unimplemented!(),
        }
    }
    JmpCond(c) => {
        if !self.flag {
            self.f.seek(std::io::SeekFrom::Start(c as u64))?;
        }
    }
    Call(v) => {
        self.stack[self.sp] = self.f.stream_position().unwrap() as u32;
        self.sp += 1;
        self.f.seek(std::io::SeekFrom::Start(v as u64))?;
    }

    Strlen => {
        self.registers[REG_RV as usize] = INPUT_DATA.len() as u32;
    }
    CharAt => {
        let arg2 = self.registers[REG_ARG1 as usize];
        self.registers[REG_RV as usize] = INPUT_DATA
            .iter()
            .nth(arg2 as usize)
            .map(|v| *v as u32)
            .unwrap_or(0_u32);
        //println!("CharAt: {}", self.registers[as usize]);
    }
    Print => {
        let stdout = std::io::stdout();
        let mut lock = stdout.lock();
        lock.write_all(&[self.registers[REG_ARG0 as usize] as u8])?;
        lock.flush()?;
    }
    Exit => {
        std::process::exit(0);
    }
};
```

This is kind of a lot, but all it really is, is the implementations for each instruction. Only a few things stand out:

* `MathOp` only supports addition, subtraction, multiplication and division.
* `JmpConst`, `PopPc`, `JmpCond` and `Call` actually seek within the file. That means that program execution can jump around the ROM and doesn't simply read it start to end.
* `CharAt` is reading some element of `INPUT_DATA` into a register but not much else.
* `Print` prints a different register (`REG_ARG0`) on the screen, but cast to [`u8`](https://doc.rust-lang.org/std/primitive.u8.html) (8-bit primitive in Rust).

I can't see any modification of `INPUT_DATA` here, so it must be happening in the ROM. It's likely calling `CharAt`, doing something to it, then calling `Print` and that's what we see on the screen.

### Reversing the flag

At this point, the natural thing would be to start analyzing the ROM instructions and figuring out what they do. There are no binary analysis tools for a custom VM, so you would have to do that by squinting at the instructions and trying to make sense of them.

But I couldn't shake the feeling that `INPUT_DATA` is the flag. It just make sense, and it's also very long, as we would expect.

Let's compare the [ordinal values](https://en.wikipedia.org/wiki/Ordinal_data_type#:~:text=In%20computer%20programming%2C%20an%20ordinal,B'%20the%20second%2C%20etc.) of the letters we know about (from runnning the ROM for a minute or two) with the corresponding values in `INPUT_DATA`.



| Flag | Ord | INPUT_DATA | Ord - INPUT_DATA |
| -----|-----|------------|------------------|
| C | 67 | 66 | 1 |
| T | 84 | 82 | 2 |
| F | 70 | 66 | 4 |
| { | 123 | 117 | 6 |
| T | 84 | 75 | 9 |
| h | 104 | 91 | 13 |
| i | 105 | 86 | 19 |
| s | 115 | 87 | 28 |
| I | 73 | 31 | 42 |
| s | 115 | 51 | 64 |
| A | 65 | 222 | -157 |
| V | 86 | 187 | -101 |
| e | 101 | 112 | -11 |
| r | 114 | 236 | -122 |
| y | 121 | 9 | 112 |
| L | 76 | 98 | -22 |
| o | 111 | 34 | 77 |
| n | 110 | 69 | 41 |
| g | 103 | 0 | 103 |
| F | 70 | 198 | -128 |
| l | 108 | 150 | -42 |
| a | 97 | 29 | 68 |
| g | 103 | 96 | 7 |
| A | 65 | 10 | 55 |
| n | 110 | 69 | 41 |
| d | 100 | 26 | 74 |
| Y | 89 | 253 | -164 |
| o | 111 | 225 | -114 |
| u | 117 | 164 | -47 |

I mapped out the differences then tried to find a pattern. Initially I thought the difference was the [Fibonnaci Sequence](https://en.wikipedia.org/wiki/Fibonacci_number), but that almost immediately fell apart. Or, it ALMOST did. See below.

| Flag | Ord | INPUT_DATA | Ord - INPUT_DATA | Difference Pattern |
| -----|-----|------------|------------------|--------------------|
| C | 67 | 66 | 1 | N/A |
| T | 84 | 82 | 2 | N/A |
| F | 70 | 66 | 4 | (2 + 1) + 1 |
| { | 123 | 117 | 6 | (4 + 2) + 0 |
| T | 84 | 75 | 9 | (6 + 4) - 1 |
| h | 104 | 91 | 13 | (9 + 6) - 2 |
| i | 105 | 86 | 19 | (13 + 9) - 3 |
| s | 115 | 87 | 28 | (19 + 13) - 4 |
| I | 73 | 31 | 42 | (28 + 19) - 5 |
| s | 115 | 51 | 64 | (42 + 28) - 6 |
| A | 65 | 222 | -157 | (64 + 42) - 7 = 99? |
| V | 86 | 187 | -101 | ? |
| e | 101 | 112 | -11 | ? |
| r | 114 | 236 | -122 | ? |

So what happened at the letter "A"? The pattern held up until that point, then went silly.

Well the negative number should be a clue. Remember how earlier we noted that the `Print` instruction casts to a `u8`? Well, it casts to `u8` from a [`usize`](https://doc.rust-lang.org/std/primitive.usize.html), which can be 32 bits or 64 bits but certainly more than 8 bits. What is likely happening here then is that the value in the registers is increasing as expected, but its overflowing during the 8-bit cast (222 + 99 > 256). Therefore, likely the pattern keeps holding, but to get the real value we need to modulo by 256.

### Re-implementing vm.rom

With all this in mind, to implement the pattern would look roughly like this:

* Initialize `INPUT_DATA` with the known numbers.
* Initialize the first 2 "diffs" as 1 and 2.
* Initialize a "delta" value as 1.
* For each number in `INPUT_DATA`
  * Calculate the diff as the sum of the last two diffs and the current delta value (except the first two).
  * Decrease the delta by 1.
  * Derive the flag character as (the number in `INPUT_DATA` + the diff) modulo 256.

This is implemented in [solve.py](solve.py).

```python
data  = [
  66, 82, 66, 117, 75, 91, 86, 87, 31, 51, 222, 187, 112, 236, 9, 98, 34, 69, 0, 198, 150, 29,
  96, 10, 69, 26, 253, 225, 164, 8, 110, 67, 102, 108, 103, 162, 209, 1, 173, 130, 186, 5, 123,
  109, 187, 215, 86, 232, 23, 215, 184, 79, 171, 232, 128, 67, 138, 153, 251, 92, 4, 94, 93,
]

diffs = [1, 2]
delta = 1

flag = 'CT'

for i, d in enumerate(data[2:]):
  diff = diffs[-1] + diffs[-2] + delta
  delta -=1
  flag += chr((d + diff) % 256)
  diffs.append(diff)

print(flag)
```

Running this gives us the flag.

```
CTF{ThisIsAVeryLongFlagAndYouMightRunOutOfJuiceWhileDecodingIt}
```
