# Simulate just the pinouts as character bits.
# No need to get an actual Raspberry Pi Pico or anything.

import time


gpios = [0, 0, 0, 0, 0, 0, 0, 0]
flag = []


def bin(num):
  return format(num, '08b')

def drive_pins(mask, value):
  for i, bit in enumerate(bin(mask)):
    if bit == '1':
      gpios[i] = value

def gpio_set_mask(mask):
  '''
  Drive high every GPIO appearing in mask.

  Parameters
    mask  Bitmask of GPIO values to set, as bits 0-29
  '''
  drive_pins(mask, 1)

def gpio_clr_mask(mask):
  '''
  Drive low every GPIO appearing in mask.

  Parameters
    mask  Bitmask of GPIO values to set, as bits 0-29
  '''
  drive_pins(mask, 0)

def sleep_us(n):
  bits = ''.join([str(g) for g in gpios])
  c = chr(int(bits, 2))
  print(f'{bits} -> {c}')
  flag.append(c)


# The C code from chal.c
gpio_set_mask(67);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(20);
gpio_clr_mask(3);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(16);
sleep_us(100);
gpio_set_mask(57);
gpio_clr_mask(4);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(25);
sleep_us(100);
gpio_set_mask(5);
gpio_clr_mask(2);
sleep_us(100);
gpio_set_mask(18);
gpio_clr_mask(65);
sleep_us(100);
gpio_set_mask(1);
gpio_clr_mask(2);
sleep_us(100);
gpio_set_mask(64);
gpio_clr_mask(17);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(1);
gpio_clr_mask(6);
sleep_us(100);
gpio_set_mask(18);
gpio_clr_mask(65);
sleep_us(100);
gpio_set_mask(1);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(4);
gpio_clr_mask(2);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(64);
gpio_clr_mask(16);
sleep_us(100);
gpio_set_mask(16);
gpio_clr_mask(64);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(4);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(3);
sleep_us(100);
gpio_set_mask(9);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(1);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(8);
sleep_us(100);
gpio_set_mask(8);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(65);
gpio_clr_mask(24);
sleep_us(100);
gpio_set_mask(22);
gpio_clr_mask(64);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(5);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(2);
sleep_us(100);
gpio_set_mask(65);
gpio_clr_mask(16);
sleep_us(100);
gpio_set_mask(22);
gpio_clr_mask(65);
sleep_us(100);
gpio_set_mask(1);
gpio_clr_mask(6);
sleep_us(100);
gpio_set_mask(4);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(66);
gpio_clr_mask(21);
sleep_us(100);
gpio_set_mask(1);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(0);
gpio_clr_mask(2);
sleep_us(100);
gpio_set_mask(24);
gpio_clr_mask(65);
sleep_us(100);
gpio_set_mask(67);
gpio_clr_mask(24);
sleep_us(100);
gpio_set_mask(24);
gpio_clr_mask(67);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(8);
sleep_us(100);
gpio_set_mask(65);
gpio_clr_mask(18);
sleep_us(100);
gpio_set_mask(16);
gpio_clr_mask(64);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(0);
sleep_us(100);
gpio_set_mask(68);
gpio_clr_mask(19);
sleep_us(100);
gpio_set_mask(19);
gpio_clr_mask(64);
sleep_us(100);
gpio_set_mask(72);
gpio_clr_mask(2);
sleep_us(100);
gpio_set_mask(2);
gpio_clr_mask(117);
sleep_us(100);
#gpio_put_all(0);
#sleep_ms(500);



print(''.join(flag))
