# Challenge #4 - Electronics Research Lab

Category: `harware`

## Story

>"Welcome back AGENT. It seems like you've got a marvelous lead that perhaps gives a clue about where you should head to next. Visit the lab, and talk to that Dr. Klostermann, or is it Cloysterman?, he will know how to decrypt the device.. you would think". ... Dr Klostermann: "Welcome to the technical department AGENT, I’m Dr. Klostermann, and this is my assistant, Konstantin. Let’s not waste any time, is that the device that you’re holding in your hand? Konstantin, start the basic procedure."<br/><br/>
>Welcome back AGENT. It seems like you got a lead that perhaps gives a clue about where the next journey on your quest goes. Visit the lab, and talk to Dr. Klostermann, he will know how to decrypt the device Note: If you solved the challenge before but could not submit the flag, please try again, we had the wrong flag in our database.

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O electronics-research-lab.zip https://storage.googleapis.com/gctf-2021-attachments-project/eafc850054672b6e5242ffb8b2f3110760a20cabcca90a69c00c4f4c91912c2e43c5ea8e68ad529692da3aac7763f6301888b843c7ee5e94699e22c8ea94db5c
$ unzip ./electronics-research-lab.zip
Archive:  ./electronics-research-lab.zip
 extracting: chal.c
 extracting: pico.uf2
```

What could this be? It's a hardware challenge, so maybe something to do with [Arduino](https://www.arduino.cc/) or [Raspberry Pi](https://www.raspberrypi.org/). Let's Google around.

Googling "pico hardware" quickly leads us to discover that the [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/specifications/) is a thing. Progress made! That means that maybe we can run the chal.c file in a a Pico.

What is a uf2 file? Well, googling it leads to [Microsoft UF2](https://github.com/microsoft/uf2):

>UF2 is a file format, developed by Microsoft for [PXT](https://github.com/Microsoft/pxt) (also known as [Microsoft MakeCode](https://makecode.com/)), that is particularly suitable for flashing microcontrollers over MSC (Mass Storage Class; aka removable flash drive).<br/><br/>
>For a more friendly explanation, check out [this blog post](https://makecode.com/blog/one-chip-to-flash-them-all). Also, take a look at the list of [implementations](https://github.com/microsoft/uf2#implementations) at the bottom of this document.

Great! More progress. Let's see if we can run the uf2 file somehow

### Trying to run the uf2 file

I don't happen to have a physical Pico on hand so I'll have to look for an online implementation. Following the implementations link, I see bootloaders and editors.

I'm not familiar with how bootloaders work, but from reading through a few of the ones linked at random, they seem to be used for actually programming a physical board.

What about the editors? Well unfortunately trying all 4 just gives me variations on "Sorry, we could not recognize this file".

There's also the [library](https://www.npmjs.com/package/uf2). Maybe this could be made to work, but it appears to work on a block level, meaning I need to figure out how to parse and "run" each block without actually running on hardware. I felt like there must be an easier way.

### Understanding the program

Okay, so maybe we don't need to run the uf2 file after all. Let's try another way.

What is the `chal.c` file actually doing?

```c
int main(void)
{
	for (int i = 0; i < 8; i++) {
		gpio_init(i);
		gpio_set_dir(i, GPIO_OUT);
	}
	gpio_put_all(0);

	for (;;) {
		gpio_set_mask(67);
		gpio_clr_mask(0);
		sleep_us(100);
		gpio_set_mask(20);
		gpio_clr_mask(3);
		sleep_us(100);
		gpio_set_mask(2);
		gpio_clr_mask(16);
		sleep_us(100);
		...
		<more of the same>

		gpio_put_all(0);
		sleep_ms(500);
	}

	return 0;
}
```

Let's try to understand each of these functions:

* [`gpio_init`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#ga8aa4741d93dc40bc728dbd3e41813ad1) initializes the [GPIO pins](https://projects.raspberrypi.org/en/projects/physical-computing/1).
* [`gpio_set_dir`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#ga6a40edf0d86f6b3f0dcb51a768cf4681) sets the GPIO "direction". I wasn't familiar with this term but since the argument is `GPIO_OUT`, I assume this means drive the signal out, not in.
* [`gpio_put_all`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#ga7aa41e10d04a8d99d9a8c4d7ba5007b8) drives all pins, in this case to 0.
* [`gpio_set_mask`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#gaf3aa12aa4543965e24f52cfa9b529904) drives high every GPIO in the mask, as a bitmask. I interpret that to mean that `67`, which is `01000011` in binary, drives pins 1, 6 and 7.
* [`gpio_clr_mask`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#ga6aca495d644a6ae66050a99ef44defbe) drives low every GPIO in the bitmask. Same as `gpio_set_mask`, but setting pins low, not high.
* `sleep_us`/`sleep_ms` probably just sleeps for the specified microseconds or milliseconds.

Okay, now we're getting somewhere! This program is driving groups of pins.

One highly suspicious thing here is the pattern. There is always one `gpio_set_mask`, one `gpio_clr_mask`, and one `sleep`. Here I had the intuition that each of these groups is trying to communicate a character to us in bit form. At the top, only 8 GPIOs are initialized, and all of the arguments are <= 2^8.

Let's try to confirm this intuition. We know that in this CTF, flags always start with `CTF{`, and nothing in this challenge has indicated otherwise. Let's try to decode the first 3 blocks (applying the masks in order):

```
                    // pins               =  00000000
gpio_set_mask(67);  // bin(67) = 01000011 -> 01000011
gpio_clr_mask(0);   // bin(0)  = 00000000 -> 01000011 = 67 -> chr(67) = 'C'
sleep
gpio_set_mask(20);  // bin(20) = 00010100 -> 01010111
gpio_clr_mask(3);   // bin(3)  = 00000011 -> 01010100 = 84 -> chr(84) = 'T'
sleep
gpio_set_mask(2);   // bin(2)  = 00000010 -> 01010110
gpio_clr_mask(16);  // bin(16) = 00010000 -> 01000110 = 70 -> chr(70) = 'F'
sleep
```

It's working! Now we just have to do it for the rest of the operations.

### Emulating the program

We don't want to do this all by hand, there are way too many lines. And we're computer people. Let's write a program.

My go-to for CTFs is Python, as it's ergonomic and very easy to write quick and simple scripts in.

If you look closely at the operations, you may realize that `gpio_set_mask` is just a bitwise OR and `gpio_clr_mask` is just a bitwise NAND. Python supports [bitwise operations](https://www.geeksforgeeks.org/python-bitwise-operators/), so let's use a plain int for the "pins".

As usual I went for the simplest solution. I copied the pin-setting lines to a Python program, used a global variable for the pins, and defined functions with the same names which modify the pins. Sleep just outputs the character. It looks like this:

```python3
gpios = 0

def gpio_set_mask(mask):
  global gpios
  gpios = gpios ^ mask

def gpio_clr_mask(mask):
  global gpios
  gpios = gpios & (~mask)

def sleep_us(n):
  global gpios
  print(chr(gpios), end="")
  
# The C code from chal.c
gpio_set_mask(67);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(20);
gpio_clr_mask(3);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(16);
sleep_us(100);
...
```

See the full file in [pico.py](pico.py).

Running this happily produces the flag:

```
CTF{be65dfa2355e5309808a7720a615bca8c82a13d7}
```
