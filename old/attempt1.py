from luma.core.interface.serial import i2c
from luma.oled.device import ssd1306
from luma.core.render import canvas
from PIL import ImageFont


serial = i2c(port=1, address=0x27)
device = ssd1306(serial)

#with canvas(device) as draw:
#    draw.text((5, 5), "Hello, World!")
