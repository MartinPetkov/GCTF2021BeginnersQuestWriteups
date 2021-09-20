num = int(open('chall.from_nyan').read().strip())
numbin = format(num, 'b')

commands = [numbin[i:i+3] for i in range(1, len(numbin) - 2, 3)]

for command in commands:
  bf =  {
    '000': '>',
    '001': '<',
    '010': '+',
    '011': '-',
    '100': '.',
    '101': ',',
    '110': '[',
    '111': ']',
  }[command]
  print(bf, end='')
