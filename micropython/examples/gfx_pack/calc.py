'''
calc.py
Graphical demo for the GFX Pack with Raspberry Pi Pico
This example draws a nice sine wave on the display, reminiscent of the graphical calculators from the 90s.
'''
from math import radians, sin
from gfx_pack import GfxPack


gp = GfxPack()
display = gp.display
WIDTH, HEIGHT = display.get_bounds()
display.set_backlight(1)  # Turns on the white component of the backlight
gp.set_backlight(0, 0, 0)  # Leaves The other back light colours off


def draw_axis():
    display.line(0, 32, 128, 32)
    display.line(64, 8, 64, 56)
    for i in range(8):
        display.line(64, (i * 12) + 8, 67, (i * 12) + 8)
        display.line((i * 16), 32, (i * 16), 34)


def draw_sine(offset=0, vlines=False):
    for x in range(128):
        angle = 720 / 128 * x
        y = int((sin(radians(angle + offset)) * 24) + 32)
        display.pixel(x, y)
        if vlines:
            if x % 2 == 0:
                display.line(x, 32, x, y)


def draw_text():
    display.text("Remember A-Level Maths!", 0, 0, WIDTH, 1)
    display.text("y=sin(x)           x=(-360:360)", 0, 58, WIDTH, 1)


# Clear Display
display.set_pen(0)
display.clear()

# Set pen to black
display.set_pen(15)

# Draw the details in the picographics frame buffer
draw_axis()
draw_sine(0, True)
draw_text()

# Update the display
display.update()
