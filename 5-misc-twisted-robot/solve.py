from randcrack import RandCrack


rc = RandCrack()

# This recovers what the generated bits were from random.getrandbits()
# and feeds them into the predictor to prime it.
# See https://github.com/tna0y/Python-random-module-cracker
with open('robo_numbers_list.txt', 'r') as f:
  for line in f.readlines():
    # Undo the formatting and the bit shift.
    recovered = int(line.strip().replace('-','')) - (1<<31)

    # Feed the predictor.
    rc.submit(recovered)

# Now the moment of truth, try predicting and decoding.
recovered_bytes = []
with open('secret.enc','rb') as secret:
  while (byte := secret.read(1)):
    key = rc.predict_getrandbits(8)
    recovered_bytes.append(key ^ byte[0])

print(''.join([chr(b) for b in recovered_bytes]))
