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


def undo():
  a = 0x0100101000011110  # = x & 1229782938247303441
  b = 0x2002220020022220  # = x & 0o0210421042104210421042
  c = 0x4444040044044400  # = x & rotate_left(1229782938247303441, 2)
  d = 0x8880008080000880  # = x & rotate_left(0o0210421042104210421042, 2)

  x = 0b1110110111000110001101101001000011100100000001110111111110110000

  #x = rotate_right(x, 10)
  x = 0b1110110000111011011100011000110110100100001110010000000111011111

  x = x ^ 0o1275437152437512431354
  #x = 0b0100001101011000000111110010010101011001000100110011001100110011

  xs = format(x, "064b")
  code_digits = [int(i, 2) for i in reversed([xs[i:i+4] for i in range(0, len(xs), 4)])]
  code = ''.join([str(d) for d in code_digits])

  return code


print(undo())
