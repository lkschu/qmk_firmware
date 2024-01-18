
from PIL import Image
import numpy as np
import os
from typing import List



WIDTH = 32
HEIGHT = 128



def png_to_pix_arr(filepath)->List[bool]:
    """
    Read png from given path and return 1D array of boolean=b/w values
    """
    img = Image.open(filepath)
    if img.size != (WIDTH,HEIGHT):
        raise ValueError(f"Img should be {WIDTH}x{HEIGHT}, but is {img.size}!")
    pixels = []
    img_data = img.load()
    for row in range(HEIGHT):
        for col in range(WIDTH):
            pixel = img_data[col,row]
            value = (sum(pixel)/3)
            value = value > 255/2
            pixels.append(value)
    return pixels

def pix_arr_to_oled(l:List[bool])->List[int]:
    """
    Convert 1D bool array into oled display format
    """
    if len(l) != WIDTH * HEIGHT:
        raise ValueError(f"Incorrect length of input list, should be W*H = {WIDTH*HEIGHT} but is {len(l)}!")
    oled_px = []
    for h in range(HEIGHT//8):
        for w in range(WIDTH):
            val = 0
            for x in range(8):
                if l[h*8*WIDTH + w + x*WIDTH]:
                    val += 2**x
            oled_px.append(val)
    return oled_px

def oled_to_pix_arr(l:List[int])->List[bool]:
    """
    Convert array of oled blocks into 1D b/w array
    """
    if len(l) != WIDTH * HEIGHT // 8:
        raise ValueError(f"Incorrect length of input list, should be W*H//8 = {WIDTH*HEIGHT//8} but is {len(l)}!")
    pixels = []
    for h in range(HEIGHT//8):
        for x in range(8):
            for w in range(WIDTH):
                pixel = l[h*WIDTH + w] & 2**x
                pixel = True if pixel != 0 else False
                pixels.append(pixel)
    return pixels

def pix_arr_to_png(l:List[bool],filepath:str):
    """
    Save 1D b/w array to new png
    """
    if len(l) != WIDTH * HEIGHT:
        raise ValueError(f"Incorrect length of input list, should be W*H = {WIDTH*HEIGHT} but is {len(l)}!")
    img = Image.new('RGB', (WIDTH,HEIGHT), color = 'black')
    for w in range(WIDTH):
        for h in range(HEIGHT):
            img.putpixel((w,h),(255,255,255) if l[h*WIDTH + w] else (0,0,0))
    img.save(filepath)









pixels = png_to_pix_arr("./oled-bg/getaway_cont.png")

oled_px = pix_arr_to_oled(pixels)
print(oled_px)

pixels2 = oled_to_pix_arr(oled_px)

# pix_arr_to_png(pixels2, "out.png")



