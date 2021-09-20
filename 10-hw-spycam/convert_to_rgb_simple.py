'''
Try to treat the last 3 streams as "raw image data" for GIMP.

For GIMP, a .data file is literally the bytes in order of RGB RGB RGB ...

So, try to convert the last 3 streams of the CSV to RGB bytes and load into GIMP.
'''

# Normalize the range of -0.5 to 0.5
# See https://stackoverflow.com/a/929107
def normalize(color_val):
  return int((float(color_val) + 0.5) * 255)

# Process stdin
with open(f'all.data', 'wb') as allf:
  for i in range(1,8):
    with open(f'{i}.csv', 'r') as f:
      lines = f.readlines()

    for line in lines:
      line = line.strip()
      _, _, R, G, B = line.split(',')

      # Normalize
      R, G, B = normalize(R), normalize(G), normalize(B)

      # Write the bytes as RGB in order.
      allf.write(R.to_bytes(1, byteorder='little', signed=False))
      allf.write(G.to_bytes(1, byteorder='little', signed=False))
      allf.write(B.to_bytes(1, byteorder='little', signed=False))
