# Challenge #17 - Golf

Category: `misc`

## Story

>You are walking through a corridor, but hey, what was that?! Changing room, you enter and find a uniform, you put it on, wow, you’re hot in uniform! You peek outside, and notice a sign on the wall that says "Master office, 100m". You close the door and plan your next steps. You're pretty close to completing your mission, but if anything goes wrong everything you've learnt will be lost. So you pull out your laptop, write down everything you know, encrypt it, hit send, and in horror watch an error appearing on the screen! You start investigating and quickly find out that a few blocks on your SSD chose this moment to die. But it gets worse - one of these blocks contained an encoding routine you needed for the data! No matter, you can implement it yourself in a few minutes, right?<br/><br/>
>What luck! You found the official documentation of the protocol with an example implementation! Uh, but that's that? You can't write to the disk anymore? What?! OK, slowly now. You find a partially writable block with 235 bytes of free space. How are you going to squeeze in the encoder.py's functionality in just 235 bytes?! Well, you guess you have to try.

## Solution

This challenge comes with a URL and a port. We can connect to it with [netcat](https://en.wikipedia.org/wiki/Netcat) (see [connect.sh](connect.sh)):

```sh
$ nc playing-golf.2021.ctfcompetition.com 1337
```

It also comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O golf.zip https://storage.googleapis.com/gctf-2021-attachments-project/bc7b1964e092df46b2b448b524d46ed264380144419d23973d075782363c76a2481639a9a139beef7ab8ba9825511cf96a2f68c1792c5d79be034c30dfee6de7
$ unzip golf.zip
Archive:  golf.zip
 extracting: decoder.py
 extracting: encoder.py
 extracting: protocol.txt
 extracting: tester.py
```

Let's look at the files and see what we're dealing with.

This challenge serves as an introduction to the game of [Code Golf](https://en.wikipedia.org/wiki/Code_golf). The way to play is to write a program that accomplishes some goal with the minimum number of bytes, similar to how in the sport of Golf you aim to get the ball in the hole in as few strokes as possible.

TODO
