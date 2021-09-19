# Simulate just the pinouts as character bits.
# No need to get an actual Raspberry Pi Pico or anything.

gpios = 0

def gpio_set_mask(mask):
  global gpios
  gpios = gpios ^ mask

def gpio_clr_mask(mask):
  global gpios
  gpios = gpios & (~mask)

def sleep_us(n):
  global gpios
  print(chr(gpios), end="")


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
