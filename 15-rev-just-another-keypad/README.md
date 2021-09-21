# Challenge #13: Noise on the Wire

Category: `net`

## Story

>You’re still located behind the tree, but now you have a plan on how to get in. You have taken notice that the guards are changing every 45 minutes, and when they do that, you have a gap of about 30 seconds to sneak past and get into the main entrance. It’s risky of course, but you have to give it a try. You run towards the entrance. The new guards have not come yet, but suddenly you hear voices closing in. You trip and fall in front of the main entrance. The voices are very close now, and you glimpse a coat that belongs to a guard behind the corner, but at the last moment you get up and enter! ...only to face another door, this one closed, with an electronic lock - this one brand new. The good news is that it seems you won't be bothered for some time, and whoever is entering or leaving most likely won't notice you if you stand really still next to the wall. You pull out your handy screwdriver, unscrew the panel next to it, and stare at the circuit board for a few seconds. It doesn't look bad, you can do it! You pull out your laptop, attach some wires, and dump the firmware in seconds. It looks fairly simple actually...<br/><br/>
>You start to analyze the firmware, and uff, that's just a standard Linux. This does makes things easier (imagine having to reverse a custom 8051 RTOS on the spot!). You browse through the directories to find the lock controls, and spot both the right executable and THE SOURCE CODE! But wait... it's in Free Pascal?! Note: To make the final flag append "CTF{" prefix and "}" suffix to the keypad code you've got. E.g. if the code is 1234, the flag would be CTF{1234}

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O just-another-keypad.zip https://storage.googleapis.com/gctf-2021-attachments-project/babbd5920c39e92529ac48e8df7f90e7b0a0839455599592ae8e9b243297b01302628ab57b4abf3d63c5052b823e5fc3fe8ebd0dc5be77b75f93c24957aeff09
$ unzip just-another-keypad.zip
Archive:  just-another-keypad.zip
 extracting: keypad.pas
```

Let's look at the files and see what we're dealing with.

What is a .pas file? Well, as the story states, this is [Free Pascal](https://wiki.freepascal.org/). I have precisely 0 experience with Free Pascal, so I'm going to attempt to convert it into a Python program instead and hopefully that will make it much easier to understand. Along the way we'll be extra careful to double-check the meaning of all symbols and syntactical elements, just in case they mean something different in this world than elsewhere.

TODO
