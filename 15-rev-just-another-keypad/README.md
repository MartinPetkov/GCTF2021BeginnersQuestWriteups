# Challenge #15: Just Another Keypad

Category: `rev`

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

Let's go through the [keypad.pas](keypad.pas) file top-to-bottom and try to understand what's happening.

### Understanding the Free Pascal program

```pas
type
  DigitType = array[1..16] of SmallInt;
```

This looks like a type definition. That's not necessary in Python so we'll omit it, but remember that any occurrence of "DigitType" is really just an array of 16 ints. In Python 3, [ints have infinite size](https://note.nkmk.me/en/python-int-max-value/), so there's no need to differentiate between Pascal's "Small" Int and any other types of Int.

---

```pas
function CheckKeyPadCode(code : DigitType) : Boolean;
var
  digit : SmallInt;
  i : SmallInt;
  x, a, b, c, d : QWord;
```

This is a function definition and variable declarations. Most of this is unnecessary in Python but let's remember that it takes a DigitType and returns a bool.

---

```pas
x := 0;
i := 0;

For digit In code Do
Begin
  If (digit < 0) or (digit > 9) then
  begin
    CheckKeyPadCode := False;
    Exit;
  end;

  x := x or (QWord(digit) shl i);
  i += 4;
End;
```

This seems to check that each digit in the code is 0-9 then `or` it with certain bits in `x`, which starts off as all 0s. 

In Free Pascal, it appears that a [QWord](https://wiki.freepascal.org/QWord) is an unsigned 64-bit integer and [`or`](https://wiki.freepascal.org/Or) is an [overloaded](https://wiki.freepascal.org/Operator_overloading) operator which acts as a [bitwise OR](https://wiki.freepascal.org/Or#bitwise_operation) when operating on ints. [`shl`](https://wiki.freepascal.org/Shl) is a bitwise left shift which fills with 0s.

All in all, this appears to set `x` to the digits in `code` from right to left, since:

* `code` is an array of 16 ints
* `i` increments by 4
* QWord is 64 bits = 16 * 4 bits
* 9, the largest digit value, is `1001` in binary, which takes up 4 bits

---

```pas
x := x xor &1275437152437512431354;
x := RolQWord(x, 10);
```

This first XORs `x` with a value. But the `&` is a subtle gotcha. If you've seen it in other languages, you might think it's an [address operator](https://en.wikipedia.org/wiki/Dereference_operator), but in fact in Free Pascal, [`&` (ampersand) denotes an octal base number](https://wiki.freepascal.org/&).

Let's let that sink in for a minute. Close your eyes and let all those instincts from years of programming in C-derived languages gently float out of your head and into the cool breeze.

Now that that's done let's look at [`RolQWord`](https://wiki.freepascal.org/FPC_New_Features_2.6.0#ROL.2FROR_intrinsics). It's kind of hard to research but it seems like it "rotates" to the left, inserting the exiting bits to the "right" side of the number.

---

```pas
a := x and 1229782938247303441;
b := x and &0210421042104210421042;
c := x and RolQWord(1229782938247303441, 2);
d := x and RolQWord(&0210421042104210421042, 2);
```

Nothing shocking. More <strike>addresses</strike> octal numbers. As with `or`, [`and` is a bitwise operation when used with ints](https://wiki.freepascal.org/Or#bitwise_operation).

---

```pas
if ((a = $0100101000011110) and (b = $2002220020022220) and
    (c = $4444040044044400) and (d = QWord($8880008080000880))) then
  CheckKeyPadCode := True
else
  CheckKeyPadCode := False;
```

The last few lines are equivalent to a `return`.

But oh boy, now we have dollar signs too. Probably not [variable accessors](https://stackoverflow.com/a/5163260). Instead, [`$` (dollar sign) denotes a hexadecimal base number](https://wiki.freepascal.org/Dollar_sign).

Cool breeze.

---

Taking all that into account, this is what it looks like in Python (see [keypad.py](keypad.py)):

```py
INT_BITS = 64

def rotate_left(n, d):
    return (n << d) | (n >> (INT_BITS - d))

def rotate_right(n, d):
    return (n >> d) | (n << (INT_BITS - d)) & 0xFFFFFFFF


def check(code):
  x = 0
  i = 0

  for digit in code:
    if digit < 0 or digit > 9:
      return False

    x = x | (digit << i)
    i += 4

  x = x ^ 0o1275437152437512431354
  x = rotate_left(x, 10)

  a = x & 1229782938247303441
  b = x & 0o0210421042104210421042
  c = x & rotate_left(1229782938247303441, 2)
  d = x & rotate_left(0o0210421042104210421042, 2)

  return (
    a == 0x0100101000011110
    and b == 0x2002220020022220
    and c == 0x4444040044044400
    and d == 0x8880008080000880
  )
```

### Reversing the code to make it return True

We need to understand what input code will make the function return True, so we can use that as the flag. To do that, we need to "undo" the operations in reverse order.

First, we know that `x` ANDed with 4 numbers produces 4 other numbers (`a`, `b`, `c` and `d`). Intiutively, this can be solved as a set of linear equations, but in practice it's a bit more complicated.

AND is not a directly reversible operation. If we know the result and one operand, we can only determine the following:

* ? & 1 = 1; our unknown must be a 1
* ? & 1 = 0; our unknown must be a 0
* ? & 0 = 0; **our unknown might be a 0 or a 1**
* <strike>? & 0 = 1; not possible with AND</strike>

With that in mind, we can progressively uncover `x` by figuring out which bits must be 0s or 1s for `a`, then for `b`, etc. until we uncover (hopefully) all of `x`.

```
x = ___0___1___0___0___1___0___1___0___0___0___0___1___1___1___1___0
&   0001000100010001000100010001000100010001000100010001000100010001  # 1229782938247303441
------------------------------------------------------------------
a = 0000000100000000000100000001000000000000000000010001000100010000  # 0x0100101000011110


x = __10__01__00__10__11__10__01__00__10__00__00__11__11__11__11__00  # 0o0210421042104210421042
&   0010001000100010001000100010001000100010001000100010001000100010
------------------------------------------------------------------
b = 0010000000000010001000100000000000100000000000100010001000100000  # 0x2002220020022220


x = _110_101_100_110_011_110_001_000_110_100_000_111_111_111_011_000
&   0100010001000100010001000100010001000100010001000100010001000100  # rotate_left(1229782938247303441, 2)
------------------------------------------------------------------
c = 0100010001000100000001000000000001000100000001000100010000000000  # 0x4444040044044400


x = 1110110111000110001101101001000011100100000001110111111110110000
&   1000100010001000100010001000100010001000100010001000100010001000  # rotate_left(0o0210421042104210421042, 2)
------------------------------------------------------------------
d = 1000100010000000000000001000000010000000000000000000100010000000  # 0x8880008080000880
```

With this, we have `x`. Let's more on to the next step.

---

We have to undo the rotation. We previously rotated 10 to the left, so now let's rotate 10 to the right.

```
               111011011100011000110110100100001110010000000111011111 1110110000
        |------------------------------------------------------------------|
        V
x = 1110110000 111011011100011000110110100100001110010000000111011111
```

---

XOR actually is a reversible operation. XORing the result with one of the operands gives the other operand. So let's XOR our `x` so far with the static value:

```py
x = x ^ 0o1275437152437512431354
```

---

Finally, we have to undo the loop and bit shifts. This might sound complicated (and it would be in the general case), but our analysis of the loop from earlier means we're actually done, in a sense.

`x` currently represents the correct code, expressed as 4-bit digits from right to left. So let's decode it 4 bits at a time and reverse:

```py
xs = format(x, "064b")
code_digits = [int(xs[i:i+4], 2) for i in range(0, len(xs), 4)]
code = ''.join(reversed([str(d) for d in code_digits]))
```

And with that, we've got our flag.

```
CTF{3333319552798534}
```
