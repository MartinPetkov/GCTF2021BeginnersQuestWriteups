# Challenge #16: Hash Meee

Category: `misc`

## Story

>Well, okay, you’re back in the cell again, and they changed the lock to something quite heavier. This one cannot be picked with a paperclip… So, is this where the mission ends? PLING, another message from the boss. Another GIF… No wait, not only a GIF, also text: "Hi AGENT, I was just contacting you to say that we’re running out of time, if you fail to reach the office and pull the self destruction lever in under 30 minutes, they will already have executed their evil plan. I’m counting on you!." Well, that wasn’t too helpful... What to do, what to do?<br/><br/>
>I heard BotBot, the resident Discord bot, is experimenting with hashing. He specifically wants to see 2 different strings, both starting with `gctf`, that have the same MD5 hash. He will reward this with a flag. You can access our Discord with the following invite link: https://discord.gg/FbrXTjvv To solve this challenge DM BotBot on discord using the command `!hashme` followed by the two strings, encoded in hex. E.g. if your strings are "gctfhello" and "gctfhola" you would send `!hashme 6763746668656c6c6f 67637466686f6c61`

## Solution

This challenge comes with...nothing. Just the instructions.

We are asked to produce 2 different strings, both starting with `gctf`, that have the same [MD5](https://en.wikipedia.org/wiki/MD5) hashes. A [hash function](https://en.wikipedia.org/wiki/Hash_function) maps data to a fixed size value and a "hash" is the output of applying that function on some data (i.e. our two strings), but in the context of computer security "hashing" almost invariably refers to [cryptographic hashing](https://en.wikipedia.org/wiki/Cryptographic_hash_function). Given that, this challenge seems impossible when considering one of the properties of a hash function:

```
* It is infeasible to find two different messages with the same hash value
```

Or is it?

"Hashing" on its own is abstract and must be implemented as a real algorithm in order to be useful. There appear to be [many cryptographic hash algorithms](https://en.wikipedia.org/wiki/Cryptographic_hash_function#Cryptographic_hash_algorithms) out there, but why is that? Well, looking at the [comparison](https://en.wikipedia.org/wiki/Comparison_of_cryptographic_hash_functions) and the [security summary](https://en.wikipedia.org/wiki/Hash_function_security_summary) (all linked directly from the earlier Wikipedia page), we can clearly see that some are more "secure" than others. Some algorithms implement the required properties really well, and others do so poorly (by today's standards; hash functions historically been considered safe but then been "broken" after enough time and research focus; it's reasonable to assume all of today's "secure" hash algorithms may eventually be broken).

A common pattern in each of these pages is that MD5 is a at the bottom of the list and considered hopelessly insecure. Some choice quotes:

* "This attack takes seconds on a regular PC."
* "Collisions against MD5 can be calculated within seconds which makes the algorithm unsuitable for most use cases where a cryptographic hash is required."

It seems the goal of this challenge really is to make you aware of this fact, and to have you experience it for yourself. Let's do some research and reproduce these results.

### Generating chosen-prefix MD5 collisions

Specifically, we need a chosen-prefix MD5 collision, not just any two random strings that collide.

It wouldn't be interesting to recreate the research process here. It's really just a lot of Googling, reading papers/websites, and following links. Personally I found the following:

* [MD5 and SHA-1 Collision Attacks: A Tutorial](http://koclab.cs.ucsb.edu/teaching/cren/project/2008/savage.pdf)
* [Peter Sellinger: MD5 Collision Demo](https://www.mscs.dal.ca/~selinger/md5collision/) (the "evilize" library)
* [Marc Stevens: Single-block collision attack on MD5](https://marc-stevens.nl/research/md5-1block-collision/)
* [HashClash](https://github.com/cr-marcstevens/hashclash) (this one is also in the "See also" section of the MD5 Wikipedia page).

HashClash is the most interesting of these because it has a section specifically about [creating your own identical-prefix collision](https://github.com/cr-marcstevens/hashclash#create-you-own-identical-prefix-collision). It says the prefix should be a multiple of 64 bytes, but optionally a small multiple of 4 bytes. Our prefix `gctf` is 4 bytes, so this fits.

Let's clone the repo and try it:

```sh
$ ./build.sh
$ echo -n 'gctf' > prefix.txt
$ ./scripts/poc_no.sh prefix.txt
<runs for a while>
```

This outputs files `collision1.bin` and `collision2.bin`. Let's compare them.

```sh
$ hexdump -C collision1.bin
00000000  67 63 74 66 78 17 86 b2  c0 20 f7 9d 6f e8 82 ad  |gctfx.... ..o...|
00000010  8d 1e a6 66 7c 7f 43 df  5c 0b c9 a2 d0 a6 b8 8b  |...f|.C.\.......|
00000020  ea cd 73 34 20 4d 83 f1  cb d3 5e bc e1 e6 df b3  |..s4 M....^.....|
00000030  64 82 47 94 28 7c 99 82  3f 72 a8 73 42 39 ee a7  |d.G.(|..?r.sB9..|
00000040  6d d8 87 72 d1 fe 69 ed  0d 05 2a ce 18 e3 f9 ba  |m..r..i...*.....|
00000050  32 a5 96 87 cc 00 82 aa  53 43 69 06 18 4f 56 30  |2.......SCi..OV0|
00000060  d7 c1 ac 93 eb eb 68 02  bc a9 0a c0 4b dc 61 89  |......h.....K.a.|
00000070  f9 91 4a 0a 66 c5 a1 73  45 66 d5 86 40 4e 5d 2a  |..J.f..sEf..@N]*|
00000080

$ hexdump -C collision2.bin
00000000  67 63 74 66 78 17 86 b2  c0 21 f7 9d 6f e8 82 ad  |gctfx....!..o...|
00000010  8d 1e a6 66 7c 7f 43 df  5c 0b c9 a2 d0 a6 b8 8b  |...f|.C.\.......|
00000020  ea cd 73 34 20 4d 83 f1  cb d3 5e bc e1 e6 df b3  |..s4 M....^.....|
00000030  64 82 47 94 28 7c 99 82  3f 72 a8 73 42 39 ee a7  |d.G.(|..?r.sB9..|
00000040  6d d8 87 72 d1 fe 69 ed  0d 04 2a ce 18 e3 f9 ba  |m..r..i...*.....|
00000050  32 a5 96 87 cc 00 82 aa  53 43 69 06 18 4f 56 30  |2.......SCi..OV0|
00000060  d7 c1 ac 93 eb eb 68 02  bc a9 0a c0 4b dc 61 89  |......h.....K.a.|
00000070  f9 91 4a 0a 66 c5 a1 73  45 66 d5 86 40 4e 5d 2a  |..J.f..sEf..@N]*|
00000080

$ diff collision1.bin collision2.bin
Binary files collision1.bin and collision2.bin differ
```

The files look similar and start with the same prefix, but are in fact different.

Let's convert them for the Discord bot (thanks to [this StackOverflow answer](https://stackoverflow.com/a/2614850)):

```sh
$ echo '!'"hashme $(xxd -p collision1.bin | tr -d '\n') $(xxd -p collision2.bin | tr -d '\n')"
!hashme 67637466781786b2c020f79d6fe882ad8d1ea6667c7f43df5c0bc9a2d0a6b88beacd7334204d83f1cbd35ebce1e6dfb364824794287c99823f72a8734239eea76dd88772d1fe69ed0d052ace18e3f9ba32a59687cc0082aa53436906184f5630d7c1ac93ebeb6802bca90ac04bdc6189f9914a0a66c5a1734566d586404e5d2a 67637466781786b2c021f79d6fe882ad8d1ea6667c7f43df5c0bc9a2d0a6b88beacd7334204d83f1cbd35ebce1e6dfb364824794287c99823f72a8734239eea76dd88772d1fe69ed0d042ace18e3f9ba32a59687cc0082aa53436906184f5630d7c1ac93ebeb6802bca90ac04bdc6189f9914a0a66c5a1734566d586404e5d2a
```

Sending this to the Discord bot happily gives us our flag.

```
CTF{h4sh_m3_tw1c3_1245fd3}
```
