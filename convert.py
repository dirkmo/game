#!/usr/bin/python3

from PIL import Image
img = Image.open("test1.jpg")
img = img.resize( (64,128), Image.ANTIALIAS )

new = Image.new("1", (64,128))

pix = img.load()
for x in range(128):
    for y in range(64):
        p = pix[y,x]
        mono = (p[0] + p[1] + p[2]) / 3
        if mono > 130:
            mono = 1
        else:
            mono = 0
        new.putpixel((y,x), mono)
        

dat = [0]*128*8
for x in range(128):
    for y in range(8):
        p = 0
        for bit in range(8):
            v = new.getpixel((y*8 + bit,x))
            p = p | (v << bit)
        dat[x+y*128] = p

new.save("mono.bmp")
print(dat)
