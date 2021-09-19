# Challenge #6 - To the Moon

Category: `misc`

## Story

>You’re exiting a crowded subway nearby the office that you are about to visit. You are showing the guards your ID and answering a couple of routine questions. They are not impressed, but the gate opens up and you can enter the area despite their doubt. You are not allowed to stroll freely on the company grounds, but are shown around by a woman that stares at you with a crooked smile. At last you're able to talk to the manager, a short man with a white robe and shades: "Greetings, AGENT, You must be thirsty after your long journey? No? You don’t mind if I’ll have something for myself, do you? Good! We have heard about the device that you possess, can I have a look at it. Hmm, it seems that it is encrypted. Help me break this quickly so that we can continue with the analysis."<br/><br/>
>This one is a doozie. We found this weird file on a memory stick with a post-it note on it. It looks like someone was working on a very obscure encryption system. Maybe we can decode it?

## Solution

>This one is a doozie

OH BOY they did not lie here. This was easily the most convoluted and guessy challenge of the entire CTF. I personally helped 10x as many people through this one specific challenge as I did for any other. I suspect if anyone found this repo, it was to see this writeup here. I'll give intuition where I can but honestly, I had several people help me and give me crucial nudges in at least 3 places where I got stuck so some of the steps will be "well you just have to guess right and have that flash of insight ¯\\_(ツ)_/¯"

Let's begin the adventure.

## Preparation

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O to-the-moon.zip https://storage.googleapis.com/gctf-2021-attachments-project/306a5e3c0faa213b4b3348366938020f90d38a41ae136a46547553fb3d6961c4bf598da6378092b4afd60f60a2510898c59d1a091961f0729c4839b1a6266a8f
$ unzip to-the-moon.zip
Archive:  to-the-moon.zip
 extracting: chall.txt
 extracting: encodings
```

Let's look at the files and see what we're dealing with.

TODO
