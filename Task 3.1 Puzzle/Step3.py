import cv2
import numpy as np



img = cv2.imread('Level1.png', cv2.IMREAD_COLOR)
# print(img.shape)
# print(img[6][93])   #[ 89 123 146]  [58 58 58]

zuckyElon = cv2.imread('zucky_elon.png', cv2.IMREAD_COLOR)
# print(zuckyElon.shape)

for x in range(0, 977):
    for y in range(0, 1440):
        #file1.write(chr(img[x][y]))
       if (zuckyElon[x][y][0] == 44 and zuckyElon[x][y][1] == 88 and zuckyElon[x][y][2] == 95):
            if (zuckyElon[x+1][y+1][0] == 50 and zuckyElon[x+1][y+1][1] == 93 and zuckyElon[x+1][y+1][2] == 102):
                print(x, y)
print(zuckyElon[460][231])        
        #print(chr(img[x][y]), end = "")

# cv2.namedWindow('My Image 2', cv2.WINDOW_AUTOSIZE)

# cv2.imshow('My Image 2', img)

# cv2.waitKey(0)
