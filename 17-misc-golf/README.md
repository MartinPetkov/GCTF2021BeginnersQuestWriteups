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

This challenge serves as an introduction to the game of [Code Golf](https://en.wikipedia.org/wiki/Code_golf). The way to play is to write a program that accomplishes some goal with the minimum number of bytes, similar to how in the sport of Golf you aim to get the ball in the hole in as few strokes as possible.

The goal is pretty straightforward: golf `encoder.py` until it's 235 bytes. So just how far off are we from that?

```sh
$ wc -c ./encoder.py
7210 ./encoder.py
```

7210?! We have our work cut out for us.

*Disclaimer: The final result of this writeup is most likely not "optimal". I'm not an expert golfer, but those that are have been known to do truly wacky and wild stuff to achieve those sweet, sweet low byte numbers. Someone on Discord reached enlightenment and brought it down to 133 bytes. If you enjoy this kind of thing, try to minify the solution here even further!*

### Foreshadowing: Golf steps that will come last

There are a handful of immediately obvious reductions, particularly with Python:

* Remove blank lines (they count for bytes).
* Remove spaces wherever possible.
* Remove newlines and condense statements with the use of `;`.
* Use a single space for indentation (Python is okay with this, as long as it's consistent).
* Rename all functions and variables to single characters.
* Rename imports to single characters.

However, we're going to leave this until the very end. That's because to effectively golf code, you need to understand what it's doing in order to combine or eliminate whole swathes of it. The modifications above are trivial to implement but severely hinder comprehension, so it's best to leave them until the end and hope they get us over the threshold.

### Analysis of the original

This is what the file starts as:

```python
#!/usr/bin/python3
import struct

__all__ = ["encode"]

NUMBERS = [
     2,    3,    5,    7,   11,   13,   17,   19,   23,   29,
    31,   37,   41,   43,   47,   53,   59,   61,   67,   71,
    73,   79,   83,   89,   97,  101,  103,  107,  109,  113,
   127,  131,  137,  139,  149,  151,  157,  163,  167,  173,
   179,  181,  191,  193,  197,  199,  211,  223,  227,  229,
   233,  239,  241,  251,  257,  263,  269,  271,  277,  281,
   283,  293,  307,  311,  313,  317,  331,  337,  347,  349,
   353,  359,  367,  373,  379,  383,  389,  397,  401,  409,
   419,  421,  431,  433,  439,  443,  449,  457,  461,  463,
   467,  479,  487,  491,  499,  503,  509,  521,  523,  541,
   547,  557,  563,  569,  571,  577,  587,  593,  599,  601,
   607,  613,  617,  619,  631,  641,  643,  647,  653,  659,
   661,  673,  677,  683,  691,  701,  709,  719,  727,  733,
   739,  743,  751,  757,  761,  769,  773,  787,  797,  809,
   811,  821,  823,  827,  829,  839,  853,  857,  859,  863,
   877,  881,  883,  887,  907,  911,  919,  929,  937,  941,
   947,  953,  967,  971,  977,  983,  991,  997, 1009, 1013,
  1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
  1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
  1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
  1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
  1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
  1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
  1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
  1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
  1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
  1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733,
  1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
  1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889,
  1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
  1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053,
  2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
  2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213,
  2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
  2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357,
  2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
  2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531,
  2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617,
  2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687,
  2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741,
  2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819,
  2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903,
  2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999,
  3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079,
  3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181,
  3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257,
  3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331,
  3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413,
  3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511,
  3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571,
  3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643,
  3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
  3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821,
  3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907,
  3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989,
  4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057,
  4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139,
  4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231,
  4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297,
  4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409,
  4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493,
  4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583,
  4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657,
  4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751,
  4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831,
  4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937,
  4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003,
  5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087,
  5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179,
  5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279,
  5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387,
  5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443,
  5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521,
  5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639,
  5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693,
  5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791,
  5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857,
  5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939,
  5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053,
  6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133,
  6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221,
  6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301,
  6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367,
  6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473,
  6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571,
  6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673,
  6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761,
  6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833,
  6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917,
  6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997,
  7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103,
  7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207,
  7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297,
  7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411,
  7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499,
  7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561,
  7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643,
  7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723,
  7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829,
  7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919,
]

def make_tlv(type, byte_data):
  output = []
  output.append(bytes(type, "utf-8")[:4])
  output.append(struct.pack(">I", len(byte_data)))
  output.append(byte_data)
  return b''.join(output)

def step1_encode_as_tlv(input_data_as_byte_stream):
  output = []
  output.append(make_tlv("BEGN", bytes("abcdefghijklmnopqrstuvwxyz", "utf-8")))
  output.append(make_tlv("DATA", input_data_as_byte_stream))
  output.append(make_tlv("END.", bytes("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "utf-8")))
  return b''.join(output)

def step2_encrypt_data(data_to_encrypt):
  output = []
  for i in range(len(data_to_encrypt)):
    byte_to_encrypt = data_to_encrypt[i]
    key_number = NUMBERS[i]
    output.append(byte_to_encrypt ^ (key_number & 0xff))

  return bytes(bytearray(output))

def encode(input_data_as_byte_stream):
  tlv_data = step1_encode_as_tlv(input_data_as_byte_stream)
  encrypted_data = step2_encrypt_data(tlv_data)
  return encrypted_data
#END
```

SURELY not all of this is necessary. Let's make some observations:

* `#!/usr/bin/python3` is almost certainly not necessary. This is a [shell directive](https://en.wikipedia.org/wiki/Shebang_(Unix)) and can probably be removed if the file is ran directly instead of via a shell.
* `__all__ = ["encode"]` is used in [module importing](https://stackoverflow.com/questions/44834/can-someone-explain-all-in-python) and can probably be removed if the program directly imports the `encode` function by name.
* `NUMBERS` is just an array of all the primes up to 7919. We can surely generate this instead of having them all written out like this.
* The `encode` function must be left as-is and not renamed, judging by the code in `tester.py`.

(Note: The `#END` at the end is actually necessary when sending it to the server and doesn't contribute to the byte count, so let's ignore it)

This already gives us some ideas. Let's pursue those and see how many bytes we can remove.

Let's remove the directives are the top as those are trivial, and then we'll look at more substantial optimizations.

Our new size:
```sh
$ ./solve.sh
Success!
Testing your code (length 7163)...
Verifying tests...
All tests passed!
```

**Savings:** 47 **Total savings:** 47

## Hole 1: Golf the prime NUMBERS

That `NUMBERS` array is massive, and it can be generated. Now, we can go through the same exercise to golf a small implementation of prime numbers generation, but let's look for one instead, since this is probably a common task in code golf courses.

I found [this StackOverflow answer](https://codegolf.stackexchange.com/a/70027), which is pretty good, but ultimately we're not looking for an efficient implementation so let's focus on the definition of a prime number: that it is not divisible by any smaller number except 1. The way to express that in Python is by trying to divide by every smaller number and looking for a remainder:

```python
def is_prime(n):
  for i in range(2,n):
    if n % i == 0:
      return False
  return True
```

This can be optimized a bit since in Python numbers can be [tested as booleans](https://docs.python.org/3/library/stdtypes.html#truth-value-testing) - for example, `0` is False and `1` is True. We can also use the [`all()`](https://docs.python.org/3/library/functions.html#all) function to check that all the values are True.

```python
def is_prime(n):
  return all([n % i for i in range(2,n)])
```

That's nice. Now let's use this in for `NUMBERS`, but since we're not going to reuse the `is_prime` function, let's just inline it with a [list comprehension](https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions).

```python
NUMBERS = [n for n in range(2,8000) if all(n%i for i in range(2,n))]
```

Let's see how much progress we made:

```sh
$ ./solve.sh
Success!
Testing your code (length 1018)...
Verifying tests...
All tests passed!
```

Wonderful!

**Savings:** 6145 **Total savings:** 6192

## Hole 2: Golf the lists

Next, let's look at some of the functions.

```python
def make_tlv(type, byte_data):
  output = []
  output.append(bytes(type, "utf-8")[:4])
  output.append(struct.pack(">I", len(byte_data)))
  output.append(byte_data)
  return b''.join(output)

def step1_encode_as_tlv(input_data_as_byte_stream):
  output = []
  output.append(make_tlv("BEGN", bytes("abcdefghijklmnopqrstuvwxyz", "utf-8")))
  output.append(make_tlv("DATA", input_data_as_byte_stream))
  output.append(make_tlv("END.", bytes("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "utf-8")))
  return b''.join(output)

def step2_encrypt_data(data_to_encrypt):
  output = []
  for i in range(len(data_to_encrypt)):
    byte_to_encrypt = data_to_encrypt[i]
    key_number = NUMBERS[i]
    output.append(byte_to_encrypt ^ (key_number & 0xff))

  return bytes(bytearray(output))
```

We see in two places one line to define the `output` list and several lines to populate it. These can done all at once. We also see a for-loop populating a list, which can be converted to a list comprehension.

```python
def make_tlv(type, byte_data):
  return b''.join([
    bytes(type, "utf-8")[:4],
    struct.pack(">I", len(byte_data)),
    byte_data
  ])

def step1_encode_as_tlv(input_data_as_byte_stream):
  return b''.join([
    make_tlv("BEGN", bytes("abcdefghijklmnopqrstuvwxyz", "utf-8")),
    make_tlv("DATA", input_data_as_byte_stream),
    make_tlv("END.", bytes("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "utf-8"))
  ])

def step2_encrypt_data(data_to_encrypt):
  return bytes(bytearray([
    data_to_encrypt[i] ^ (NUMBERS[i] & 0xff)
    for i in range(len(data_to_encrypt))
  ]))
```

Let's try it.

```sh
$ ./solve.sh
Success!
Testing your code (length 818)...
Verifying tests...
All tests passed!
```

Great!

**Savings:** 200 **Total savings:** 6392

## Hole 3: Combine function calls

It's beginning to get a bit harder to find optimizations. But we can combine the two function calls in `encode`:

```python
def encode(input_data_as_byte_stream):
  return step2_encrypt_data(step1_encode_as_tlv(input_data_as_byte_stream))
```

While we're at it, it seems like step2 uses the output of step1, so let's just combine them and put the code in the encode function.

```python
def encode(input_data):
  data = b''.join([
    make_tlv("BEGN", bytes("abcdefghijklmnopqrstuvwxyz", "utf-8")),
    make_tlv("DATA", input_data),
    make_tlv("END.", bytes("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "utf-8"))
  ])
  return bytes(bytearray([
    data[i] ^ (NUMBERS[i] & 0xff)
    for i in range(len(data))
  ]))
```

Testing it:

```sh
$ ./solve.sh
Success!
Testing your code (length 539)...
Verifying tests...
All tests passed!
```

**Savings:** 279 **Total savings:** 6671

## Hole 4: Golf the bytes

It's definitely getting less obvious what to optimize now. But let's focus for a bit on the remaining function, `make_tlv`.

```python
def make_tlv(type, byte_data):
  return b''.join([
    bytes(type, "utf-8")[:4],
    struct.pack(">I", len(byte_data)),
    byte_data
  ])
```

It's joining some bytes and converting some of the input arguments into bytes. There's a few things we can do here:

* Looking lower down, all the types are 4 characters long so the `[:4]` is unnecessary.
* The types are static strings that then get converted to bytes. We can just pass them in as bytes to begin with, using Python's [literal bytes syntax](https://docs.python.org/3/library/stdtypes.html#bytes).
* [`struct`](https://docs.python.org/3/library/struct.html) is used to convert a variable to bytes. We can replace this with [`to_bytes`](https://docs.python.org/3/library/stdtypes.html#int.to_bytes) to save a few characters by omitting `import struct`.
* Instead of joining a list, we can just add all the byte values with `+`.

Let's see where all of these get us.

```python
NUMBERS = [n for n in range(2,8000) if all(n%i for i in range(2,n))]

def make_tlv(type, byte_data):
  return type + len(byte_data).to_bytes(4,'big') + byte_data

def encode(input_data):
  data = b''.join([
    make_tlv(b"BEGN", bytes("abcdefghijklmnopqrstuvwxyz", "utf-8")),
    make_tlv(b"DATA", input_data),
    make_tlv(b"END.", bytes("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "utf-8"))
  ])
  return bytes(bytearray([
    data[i] ^ (NUMBERS[i] & 0xff)
    for i in range(len(data))
  ]))
```

Let's try it.

```sh
$ ./solve.sh
Success!
Testing your code (length 480)...
Verifying tests...
All tests passed!
```

**Savings:** 59 **Total savings:** 6730

## Hole 5: Zip and XOR

What now? There's isn't all that much left to look at or optimize.

Well, one small thing we can do is use Python's [`zip`](https://docs.python.org/3/library/functions.html#zip) to join the bytes to XOR and the prime numbers. That should save a handful of bytes.

```python

NUMBERS = [n for n in range(2,8000) if all(n%i for i in range(2,n))]

def make_tlv(type, byte_data):
  return type + len(byte_data).to_bytes(4,'big') + byte_data

def encode(input_data):
  data = b''.join([
    make_tlv(b"BEGN", bytes("abcdefghijklmnopqrstuvwxyz", "utf-8")),
    make_tlv(b"DATA", input_data),
    make_tlv(b"END.", bytes("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "utf-8"))
  ])
  return bytes(d ^ (n & 0xff) for d,n in zip(data, NUMBERS))
```

Let's try it.

```sh
$ ./solve.sh
Success!
Testing your code (length 444)...
Verifying tests...
All tests passed!
```

**Savings:** 36 **Total savings:** 6766

## Hole 6: Inline make_tlv

We're getting pretty desperate now.

We can make one more observation: two of the calls to `make_tlv` use static data. That means that if we inline them and just use the final value, we might save some bytes. The second call will need to be inlined fully since it's not static data, but it should still help.

The result:

```python
NUMBERS = [n for n in range(2,8000) if all(n%i for i in range(2,n))]

def encode(input_data):
  data = b''.join([
    b'BEGN\x00\x00\x00\x1aabcdefghijklmnopqrstuvwxyz',
    b'DATA' + len(input_data).to_bytes(4,'big') + input_data,
    b'END.\x00\x00\x00\x1aABCDEFGHIJKLMNOPQRSTUVWXYZ'
  ])
  return bytes(d ^ (n & 0xff) for d,n in zip(data, NUMBERS))
```

Let's try it.

```sh
$ ./solve.sh
Success!
Testing your code (length 350)...
Verifying tests...
All tests passed!
```

**Savings:** 94 **Total savings:** 6860

## Hole 7: Add the data bytes

Similar to before, let's change the `b''.join([...])` to plain byte addition.

```python
NUMBERS = [n for n in range(2,8000) if all(n%i for i in range(2,n))]

def encode(input_data):
  data = b'BEGN\x00\x00\x00\x1aabcdefghijklmnopqrstuvwxyz' + b'DATA' + len(input_data).to_bytes(4,'big') + input_data + b'END.\x00\x00\x00\x1aABCDEFGHIJKLMNOPQRSTUVWXYZ'
  return bytes(d ^ (n & 0xff) for d,n in zip(data, NUMBERS))
```

The code is starting to look pretty ugly.

Let's try it.

```sh
$ ./solve.sh
Success!
Testing your code (length 324)...
Verifying tests...
All tests passed!
```

**Savings:** 26 **Total savings:** 6886

## Hole 8: Deduplicate

We're getting close. As a reminder, our target was 235 bytes of space. Maybe the steps we put off till now will get us there, but let's do one more optimization.

There's so little to look at by now, but we can make the observation that the extra bytes in the `END.` block are the same as the ones in the `BEGN` block, just uppercase. Let's save those in a variable and use Python's [`upper()`](https://docs.python.org/3/library/stdtypes.html#str.upper) to convert it.

```python
NUMBERS = [n for n in range(2,8000) if all(n%i for i in range(2,n))]

def encode(input_data):
  extra = b'\x00\x00\x00\x1aabcdefghijklmnopqrstuvwxyz'
  data = b'BEGN' + extra + b'DATA' + len(input_data).to_bytes(4,'big') + input_data + b'END' + extra.upper()
  return bytes(d ^ (n & 0xff) for d,n in zip(data, NUMBERS))
```

Let's try it.

```sh
$ ./solve.sh
Success!
Testing your code (length 319)...
Verifying tests...
All tests passed!
```

Didn't help too much.

**Savings:** 5 **Total savings:** 6891

## Hole 9: Uglify

It's time to reach our final form.

Let's apply all the changes from earlier that we've been putting off. This is what you see in [encoder_golfed.py](encoder_golfed.py).

```python.py
r=range;P=[n&0xff for n in r(2,8000) if all(n%i for i in r(2,n))]
def encode(t):l=b'\x00\x00\x00\x1aabcdefghijklmnopqrstuvwxyz';return bytes(b^p for b,p in zip(b'BEGN'+l+b'DATA'+len(t).to_bytes(4,'big')+t+b'END.'+l.upper(),P))
#END
```

Practically unintelligible, but still a far cry from something like [APL](https://stackoverflow.com/a/17823939).

We run it:

```sh
$ ./solve.sh
Success!
Testing your code (length 226)...
Verifying tests...
All tests passed!
```

And we finally get our flag:

```
CTF{EncodingSuccessfulIntelReceivedCorrectly}
```
