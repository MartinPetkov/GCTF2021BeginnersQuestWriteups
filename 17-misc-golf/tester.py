import random
import os

from encoder_golfed import encode
from decoder import decode

for i in range(1000):
  sz = random.randint(0, 800)
  data = os.urandom(sz)
  data_processed = decode(encode(data))
  if data != data_processed:
    raise Exception('data mismatch')

print('Success!')
