# Convert nyan's output to brainfuck according to https://esolangs.org/wiki/A

with open('chall.from_nyan_base8', 'r') as f:
  data = f.read().strip()


for n in data:
  bf =  {
    '0': '>',
    '1': '<',
    '2': '+',
    '3': '-',
    '4': '.',
    '5': ',',
    '6': '[',
    '7': ']',
  }[n]
  print(bf, end='')
