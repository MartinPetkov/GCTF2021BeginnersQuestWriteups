# Challenge #10 - Spycam

Category: `hardware`

## Story

>New York is hot, and you are on your way to the office complex. It seems like it is well guarded, even though you are expected under the alias of the assassin, perhaps it will be a better idea to sneak inside the building, unseen? You climb through a window on the side of the building. Inside you spot more guards, quick, hide behind a desk. Now you have to sneak past the guards into the main office.<br/><br/>
>You manage to find some exposed wires and quickly hook them up to your portable terminal. It seems to be a live feed of the internal CCTV system. If you can manage to decode the signal you might find something interesting, maybe a code or a password to get past the locked door.

## Solution

*Note: I'll freely admit this is the challenge I understood the least. Conceptually I think I get what's supposed to be done, but in practice I could only solve it with the help of Discord buddies.*

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O spycam.zip https://storage.googleapis.com/gctf-2021-attachments-project/c153d94221901baaba0eea8fbf6239be785741f5dd61aad22ba05cd862578b1b8cf04e7ebb9251f5a118f75ea567ae51cd37029c967f7dbff40c6453d38974dc
$ unzip spycam.zip
Archive:  spycam.zip
 extracting: chall.tar.gz
$ tar -tvzf chall.tar.gz
-rw-r--r-- chief/chief 25451543 2021-08-23 04:52 1.csv
-rw-r--r-- chief/chief 25723209 2021-08-23 04:52 2.csv
-rw-r--r-- chief/chief 25388488 2021-08-23 04:52 3.csv
-rw-r--r-- chief/chief 25078780 2021-08-23 04:52 4.csv
-rw-r--r-- chief/chief 25194368 2021-08-23 04:52 5.csv
-rw-r--r-- chief/chief 25223228 2021-08-23 04:52 6.csv
-rw-r--r-- chief/chief 25287005 2021-08-23 04:52 7.csv
```

Let's look at the files and see what we're dealing with.

TODO
