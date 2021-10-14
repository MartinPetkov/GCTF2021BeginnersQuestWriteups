# Challenge #7 - ReadySetAction

Category: `crypto`

## Story

>You are showing the invitation so that you can enter the conference. There are hundreds of important looking people at the conference. You take a glass of champagne from a tray, and try to look important yourself. After being busy with trying to look important for a few minutes, you approach the person that you are here to get classified information from. He introduces himself as Dr. Nowak Wasilewski. Nowak asks who you are, and if you can prove your knowledge through a test that he has designed by himself.<br/><br/>
>Apparently this script was used to encrypt super secret messages. Maybe there is something interesting in it?

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O ready-set-action.zip https://storage.googleapis.com/gctf-2021-attachments-project/aad0cde922e43ccbf05b02b7ccb3851a96473d9a1e7e228344bfb6b45c95d1b6277250695f34bb94120033b90cb91b30e29ca24e9ea44b0a2e11fa202b8f19e5
$ unzip ready-set-action.zip
Archive:  ready-set-action.zip
 extracting: chall.py
 extracting: __pycache__/chall.cpython-39.pyc
```

These are Python 3 files. The [.pyc](https://docs.python.org/3/glossary.html#term-bytecode) file contains Python bytecode. However, the only thing of note in it is one "REDACTED" value:

```sh
$ hexdump -C __pycache__/chall.cpython-39.pyc
00000000  61 0d 0d 0a 00 00 00 00  ef c0 0a 61 03 03 00 00  |a..........a....|
00000010  e3 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000020  00 04 00 00 00 40 00 00  00 73 44 00 00 00 64 00  |.....@...sD...d.|
00000030  64 01 6c 00 54 00 64 02  5a 01 65 02 64 03 83 01  |d.l.T.d.Z.e.d...|
00000040  5a 03 65 02 64 03 83 01  5a 04 65 03 65 04 14 00  |Z.e.d...Z.e.e...|
00000050  5a 05 65 06 65 01 83 01  5a 07 65 08 65 07 64 04  |Z.e.e...Z.e.e.d.|
00000060  65 05 83 03 5a 09 65 0a  65 09 83 01 01 00 64 05  |e...Z.e.e.....d.|
00000070  53 00 29 06 e9 00 00 00  00 29 01 da 01 2a 5a 08  |S.)......)...*Z.|
00000080  52 45 44 41 43 54 45 44  69 00 04 00 00 e9 03 00  |REDACTEDi.......|
00000090  00 00 4e 29 0b 5a 12 43  72 79 70 74 6f 2e 55 74  |..N).Z.Crypto.Ut|
000000a0  69 6c 2e 6e 75 6d 62 65  72 da 04 66 6c 61 67 5a  |il.number..flagZ|
000000b0  08 67 65 74 50 72 69 6d  65 da 01 70 da 01 71 da  |.getPrime..p..q.|
000000c0  01 6e 5a 0d 62 79 74 65  73 5f 74 6f 5f 6c 6f 6e  |.nZ.bytes_to_lon|
000000d0  67 da 01 6d da 03 70 6f  77 da 01 63 da 05 70 72  |g..m..pow..c..pr|
000000e0  69 6e 74 a9 00 72 0c 00  00 00 72 0c 00 00 00 fa  |int..r....r.....|
000000f0  6f 2f 75 73 72 2f 6c 6f  63 61 6c 2f 67 6f 6f 67  |o/usr/local/goog|
00000100  6c 65 2f 68 6f 6d 65 2f  6a 62 75 66 66 2f 44 6f  |le/home/jbuff/Do|
00000110  63 75 6d 65 6e 74 73 2f  4b 43 54 46 2f 32 30 32  |cuments/KCTF/202|
00000120  31 2d 63 68 61 6c 6c 65  6e 67 65 73 2d 71 75 61  |1-challenges-qua|
00000130  6c 73 2f 62 65 67 69 6e  6e 65 72 73 2f 63 72 79  |ls/beginners/cry|
00000140  70 74 6f 2d 62 61 62 79  72 73 61 2f 61 74 74 61  |pto-babyrsa/atta|
00000150  63 68 6d 65 6e 74 73 2f  63 68 61 6c 6c 2e 70 79  |chments/chall.py|
00000160  da 08 3c 6d 6f 64 75 6c  65 3e 01 00 00 00 73 0e  |..<module>....s.|
00000170  00 00 00 08 02 04 02 08  01 08 01 08 02 08 02 0c  |................|
00000180  02                                                |.|
00000181
```

Let's move on and look at the [main file](chall.py).

```python
from Crypto.Util.number import *

flag = b"REDACTED"

p = getPrime(1024)
q = getPrime(1024)
n = p*q

m = bytes_to_long(flag)

c = pow(m,3,n)

print(c)
print(n)
#15478048932253023588842854432571029804744949209594765981036255304813254166907810390192307350179797882093083784426352342087386691689161026226569013804504365566204100805862352164561719654280948792015789195399733700259059935680481573899984998394415788262265875692091207614378805150701529546742392550951341185298005693491963903543935069284550225309898331197615201102487312122192298599020216776805409980803971858120342903012970709061841713605643921523217733499022158425449427449899738610289476607420350484142468536513735888550288469210058284022654492024363192602734200593501660208945967931790414578623472262181672206606709
#21034814455172467787319632067588541051616978031477984909593707891829600195022041640200088624987623056713604514239406145871910044808006741636513624835862657042742260288941962019533183418661144639940608960169440421588092324928046033370735375447302576018460809597788053566456538713152022888984084306297869362373871810139948930387868426850576062496427583397660227337178607544043400076287217521751017970956067448273578322298078706011759257235310210160153287198740097954054080553667336498134630979908988858940173520975701311654172499116958019179004876438417238730801165613806576140914402525031242813240005791376093215124477
```

There's seemingly very little going on here. We get 2 1024-bit prime numbers (presumably in a cryptographically-secure way, as it's using a function from the [Crypto.Util](https://pycryptodome.readthedocs.io/en/latest/src/util/util.html#Crypto.Util.number.getPrime) package), multiply them together, and raise the flag to the power of 3 modulo the product. We're also given the values of the power and the product.

An astute observer may realize that this is [textbook RSA](https://crypto.stackexchange.com/questions/1448/definition-of-textbook-rsa) with the lowest possible value for `e` of `3`. I spent a good deal of time looking for simple/straightforward attacks against RSA but honestly crypto is not one of my strengths, so I eventually decided to just look at the mathematical properties and try to reverse the equation.

## Quick Maths

The formula we have is this:

```
c = (flag ^ 3) % n
```

Where `c` and `n` are known.

Can we directly reverse this? Raising to a power can be undone with a logarithm but modulo does not have a direct inverse. By its definition, an infinite amount of numbers could produce the same remainder. Finding the two original primes directly is infeasible, otherwise RSA with 1024 bits wouldn't be cryptographically secure.

It might seem like we're stuck, but it also seems like we know enough values to reverse the flag somehow.

Let's think about it some more:

* The remainder (`c`) is some value between 0 and `n`, by the definition of how modulo works.
* The value other than `c` is always going to be some multiple of `n`, again by the definition of how modulo works.
* That means that flag raised to `e` (`flag ^ 3`) is `<some multiple of n> + c`.
* And the flag itself is that value at the 3rd root.

This is enough intuition to start guessing the flag.

## Solving

We can simply try increasing multiples of `n`, add `c`, and attempt to find the 3rd root of the resulting value. If we find an exact root, we've likely found the flag itself (expressed as `bytes_to_long`, which has an inverse [`long_to_bytes`](https://www.kite.com/python/docs/Crypto.Util.number.long_to_bytes)) but also we should see something like `CTF{` at the beginning. Exact root, because libraries that work with very large numbers will give approximate roots for any number.

That's exactly what we do in [solve.py](solve.py):

```python
import gmpy2

from Crypto.Util.number import *


c = 15478048932253023588842854432571029804744949209594765981036255304813254166907810390192307350179797882093083784426352342087386691689161026226569013804504365566204100805862352164561719654280948792015789195399733700259059935680481573899984998394415788262265875692091207614378805150701529546742392550951341185298005693491963903543935069284550225309898331197615201102487312122192298599020216776805409980803971858120342903012970709061841713605643921523217733499022158425449427449899738610289476607420350484142468536513735888550288469210058284022654492024363192602734200593501660208945967931790414578623472262181672206606709

n = 21034814455172467787319632067588541051616978031477984909593707891829600195022041640200088624987623056713604514239406145871910044808006741636513624835862657042742260288941962019533183418661144639940608960169440421588092324928046033370735375447302576018460809597788053566456538713152022888984084306297869362373871810139948930387868426850576062496427583397660227337178607544043400076287217521751017970956067448273578322298078706011759257235310210160153287198740097954054080553667336498134630979908988858940173520975701311654172499116958019179004876438417238730801165613806576140914402525031242813240005791376093215124477

e = 3

# Try different multiples of the modulus and root by 3
for k in range(0,100000):
  plaintext, exact = gmpy2.iroot(gmpy2.mpz((k * n) + c), e)
  if exact:
    data = long_to_bytes(plaintext)
    print(f'Exact: {exact} ; {data}')
```

We run it and it almost immediately spits out something:

```
$ python solve.py
Exact: True ; b'CTF{34sy_RS4_1s_e4sy_us3}\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
```

And there we have our flag.

```
CTF{34sy_RS4_1s_e4sy_us3}
```
