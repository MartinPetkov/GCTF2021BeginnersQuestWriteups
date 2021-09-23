data  = [
  66, 82, 66, 117, 75, 91, 86, 87, 31, 51, 222, 187, 112, 236, 9, 98, 34, 69, 0, 198, 150, 29,
  96, 10, 69, 26, 253, 225, 164, 8, 110, 67, 102, 108, 103, 162, 209, 1, 173, 130, 186, 5, 123,
  109, 187, 215, 86, 232, 23, 215, 184, 79, 171, 232, 128, 67, 138, 153, 251, 92, 4, 94, 93,
]

diffs = []
delta = 1

for i, d in enumerate(data):
  if len(diffs) < 1:
    diff = 1
  elif len(diffs) < 2:
    diff = 2
  else:
    diff = diffs[-1] + diffs[-2] + delta
    delta -=1
  print(chr((d + diff) % 256), end='')
  diffs.append(diff)

print()
