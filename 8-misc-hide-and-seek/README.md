# Challenge #8 - Hide and Seek

Category: `misc`

## Story

>You arrive at the location through the coordinates that you got from the assassin, a luxurious yacht. A fat, bald man lies on a puma couch. He sips on a dry martini, smokes the biggest cigar you've ever seen and when he smiles, a golden tooth is revealed. You can’t help but smile back at him, although you think the place seems shady. "Welcome to my yacht, Johnson, finally you show us your face. Have you killed the AGENT now? Good! You’re here to collect your reward I presume? I’ll have my guy finalize the transaction but before you leave I need a small favor from you." It seems that he is mistaking you for the assassin but you don’t mind.<br/><br/>
>The man hands you a pendrive which you reluctantly connect to your laptop. He says he got it from a partner, and the partner claims that he hid valuable information in that PNG there. The problem is, it looks empty. See if you can find anything.

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O hide-and-seek.zip https://storage.googleapis.com/gctf-2021-attachments-project/bf0b845d9cc07ec1ee2c97189fe4577b7571a2343e919baa911d88b0f654c035c13f0e8770085ce775b9619d1ebbf357f31327ab7463125bd35f1847b2d225f0
$ unzip hide-and-seek.zip
Archive:  hide-and-seek.zip
 extracting: hideandseek.png
```

We only have one image. It doesn't look like anything:

![Hide and Seek image](hideandseek.png)

So the flag must be hidden in the image somehow.

There's nothing of note from exiftool:

```sh
$ exiftool hideandseek.png
ExifTool Version Number         : 12.30
File Name                       : hideandseek.png
Directory                       : .
File Size                       : 14 KiB
File Modification Date/Time     : 1979:12:31 00:00:00-05:00
File Access Date/Time           : 2021:09:20 12:17:33-04:00
File Inode Change Date/Time     : 2021:08:29 19:19:18-04:00
File Permissions                : -rw-r--r--
File Type                       : PNG
File Type Extension             : png
MIME Type                       : image/png
Image Width                     : 1000
Image Height                    : 1000
Bit Depth                       : 8
Color Type                      : RGB
Compression                     : Deflate/Inflate
Filter                          : Adaptive
Interlace                       : Noninterlaced
Image Size                      : 1000x1000
Megapixels                      : 1.0
```

I tried [aperisolve](https://aperisolve.fr/), and it didn't immediately find the flag (unsurprisingly). However, it has a "strings" section and there's something odd there:

```sh
$ strings hideandseek.png
IHDR
IDATx
eDIHQ
IDAT`
eDIH1
IDAT
eDIHRA
IDAT
eDIHG,
IDAT`
eDIHe
IDAT
eDIH0
IDAT
eDIHRA
IDAT`
eDIHp
IDAT
eDIHZO
IDAT
eDIHF[
IDAT`
eDIHl
IDAT
eDIHv}
IDAT
eDIHd
IDAT`
eDIHU
IDAT
eDIHt
IDAT
eDIHu
IDAT`
eDIHbg
IDAT
eDIH3{
NAME
IDAT
eDIHd
IDAT`
eDIHQ
IDAT
eDIHT
IDAT
eDIHk
IDAT`
eDIHd
IDAT
eDIHp
IDAT
eDIHc
IDAT`
eDIH1
IDAT
eDIHB\
IDAT
eDIHy
IDAT`
eDIHbg
IDAT
eDIH2
IDAT
eDIH5
IDAT`
eDIHv}
IDAT
eDIHd
IDAT
eDIHW1bw_
IDAT`
eDIH5
IDAT
eDIHji
IDAT
eDIHZO
IDAT`
eDIHW1bw_
IDAT
eDIHRA
IDAT
eDIHQ
IDAT`
eDIHS6
IDAT
eDIHU
IDAT
eDIH5
IDAT`
eDIHH
IDAT
eDIHP
IDAT
eDIH3{
IDAT`
eDIH0
IDAT
eDIH=
IDAT
IEND
```

What is all this? We see a whole bunch of `IDAT` and `eDIH`, and both `{` and `}`. Googling "idat png" leads to the [PNG Chunks Specification](http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html).

```
A valid PNG image must contain an IHDR chunk, one or more IDAT chunks, and an IEND chunk
```

We see that here. But that page does not mention "eDIH". It's likely another type of chunk, so let's find out how to read those chunks directly.

## Reading chunks

Now, `strings` isn't parsing this file as an image, it's just looking for string-like byte sequences. Let's instead find a tool that does parse PNGs and can operate on chunks.

A bit of Googling leads us to [this](https://unix.stackexchange.com/questions/42314/png-viewer-that-can-display-text-chunks-metadata), which suggests using [`pngcheck`](http://www.libpng.org/pub/png/apps/pngcheck.html). Let's try it:

```sh
$ pngcheck -c -v -t hideandseek.png
File: hideandseek.png (14366 bytes)
  chunk IHDR at offset 0x0000c, length 13
    1000 x 1000 image, 24-bit RGB, non-interlaced
  chunk IDAT at offset 0x00025, length 273
    zlib: deflated, 32K window, superfast compression
  chunk eDIH at offset 0x00142, length 1:  illegal (unless recently approved) unknown, public chunk
ERRORS DETECTED in hideandseek.png
```

What's this now? An "unknown, public chunk"?

The very bottom of the chunks spec, "4.4. Additional chunk types", talks about public chunks. Basically, custom chunk types can be specified but they won't be added to the official spec or be expected to be supported until they are proven to be "of use to others" and "do not violate the design philosophy of PNG".

Well it doesn't really matter to us if the new "eDIH" chunks are officially supported or not. We just need to read the values in them.

## Extracting the flag

Unfortunately I wasn't aware of a tool to do this and spent a long time searching. A lot of Googling around eventually led me to [`exiv2`](https://exiv2.org/getting-started.html#util), which seemed promising.

Let's see what it produces:

```sh
$ exiv2 -pS hideandseek.png
STRUCTURE OF PNG FILE: hideandseek.png
 address | chunk |  length | data                           | checksum
       8 | IHDR  |      13 | ............                   | 0xc2c143b3
      33 | IDAT  |     273 | x...........Om...(..0`.......0 | 0x6024aa37
     318 | eDIH  |       1 | Q                              | 0xd801d26a
     331 | IDAT  |     273 | `.......0`.......0`.......0`.. | 0xd186b6a8
     616 | eDIH  |       1 | 1                              | 0x95b3b332
     629 | IDAT  |     273 | .....0`.......0`.......0`..... | 0xd29c66d6
     914 | eDIH  |       1 | R                              | 0x410883d0
     927 | IDAT  |     273 | ..0`.......0`.......0`.......0 | 0x54798dc1
...
```

Okay, this seems promising. Let's parse out just the "data" column for each eDIH chunk:

```sh
$ exiv2 -pS hideandseek.png | grep 'eDIH' | awk '{print $7}' | perl -pe 'chomp'
Q1RGe0RpZFlvdUtub3dQTkdpc1Byb25vdW5jZWRQSU5HP30=
```

This unfortunately doesn't work as the flag, wrapped in `CTF{}`. However, the `=` at the end suggests it might be a base64-encoded value. Let's try it.

```sh
$ echo 'Q1RGe0RpZFlvdUtub3dQTkdpc1Byb25vdW5jZWRQSU5HP30=' | base64 -d
```

This happily gives us the flag.

```
CTF{DidYouKnowPNGisPronouncedPING?}
```
