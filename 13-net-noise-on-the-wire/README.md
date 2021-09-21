# Challenge #13: Noise on the Wire

Category: `net`

## Story

>That was close! The armed guard didn’t notice you. The floor shakes, the boat is leaving the harbor. You are trying to stay hidden. You see two guards coming your way, you sneak into a small scrubber, they pass it, but then one of the guards takes out his phone and says “OK Google” and your phone suddenly makes a noise: PLING! The guards heard it: Guard 1: "Did you hear that?" Guard 2: "It must have come from the scrubber" Guard 1: "Let's have a look!" The guards close in, you are trapped! Suddenly a bell rings in the distance, and a voice talks through speakers: "Every man to their positions, the ship is about to debark, I repeat, every man to their positions." The guards change their course and head for their positions. Pheww, that was close! You find a better place to hide and settle in for the journey. Then you notice an ethernet socket in the wall. Might as well sniff some traffic while you're here.<br/><br/>
>You connect your laptop to the ethernet socket and start wireshark. It taks a while before something interesting pops up - perhaps the crew as busy with whatever is that they normally do. You look through the packets, and hey, these look pretty interesting...

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O noise-on-the-wire.zip https://storage.googleapis.com/gctf-2021-attachments-project/c857cf4543aafba2cd93b1d381088557ccc63e839c505310a8e212ecd8355a0b6fce3421ed822fb0cdb6c63d0aec9ef794c90ace6010695334816fab88b6a740
$ unzip noise-on-the-wire.zip
Archive:  noise-on-the-wire.zip
 extracting: httponly.pcap
```

Let's look at the files and see what we're dealing with.

TODO
