'''
Try to treat the last 3 streams as "raw image data" for GIMP.

For GIMP, a .data file is literally the bytes in order of RGB RGB RGB ...

So, try to convert the last 3 streams of the CSV to RGB bytes and load into GIMP.
'''

# Normalize the range of -0.5 to 0.5
def normalize(float_color_val):
  return int((float_color_val * 255) % 255)

# Process stdin
with open(f'all.data', 'wb') as allf:
  for i in range(7,8):
    with open(f'{i}.csv', 'r') as f:
      lines = f.readlines()

    with open(f'{i}.data', 'wb') as f:
      for line in lines:
        line = line.strip()
        _, _, Y, Pb, Pr = line.split(',')
        Y, Pb, Pr = float(Y), float(Pb), float(Pr)

        # Convert according to https://en.wikipedia.org/wiki/YPbPr
        Y += 0.5
        Pb += 0.5
        Pr += 0.5

        R = Y - Pr
        B = Y - Pb
        G = (Y - (0.2126 * R + 0.0722 * B)) / 0.7152

        # Normalize
        R, G, B = normalize(R), normalize(G), normalize(B)

        # Write the bytes as RGB in order.
        f.write(R.to_bytes(1, byteorder='little', signed=False))
        f.write(G.to_bytes(1, byteorder='little', signed=False))
        f.write(B.to_bytes(1, byteorder='little', signed=False))

        # Add to the combined file.
        allf.write(R.to_bytes(1, byteorder='little', signed=False))
        allf.write(G.to_bytes(1, byteorder='little', signed=False))
        allf.write(B.to_bytes(1, byteorder='little', signed=False))
