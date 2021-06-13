import cv2
import numpy as np

file1 = open('myfile.txt', 'w')

img = cv2.imread('Level1.png', cv2.IMREAD_GRAYSCALE)
for x in range(0, 177):
    for y in range(0, 177):
        file1.write(chr(img[x][y]))
        
file1.close()
