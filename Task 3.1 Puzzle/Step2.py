import cv2
import numpy as np



img = cv2.imread('Level1.png', cv2.IMREAD_COLOR)




string = '''Congrats on solving the first level of this task! You were able to figure out the ASCII text from the image, but wait! Your journey is not yet over. After the end of the text you will find a (200, 150, 3) coloured image. This image is a part of the bigger image called "zucky_elon.png". Find the top left coordinate (Image convention) from where this image was taken. The x coordinate represents the colour of a monochrome maze hidden in an image with coloured noise. Find the maze and solve the maze using any algothrim like dfs but better. Try comparing them and seeing how they perform like A*, RRT, RRT* for example. Once the maze is solved you will see a word. This word is a password to a password protected zip file which contains a png. Note that the password is case sensitive and all the aplhabets in the password will be capital letters This is your treasure. To open the treasure you need to convert the image in to an audio file in a simple way like you did for this ASCII text. Once converted, open the .mp3 file and enjoy your treasure, you deserved it! A part of the image "zucky_elon.png" will begin immediatly after the colon, image-lv2 :'''
leng = len(string)  #1156

level2 = np.reshape(img, (177*177,3))


# print("Original Shape:",img.shape)

# level2 = np.zeros((177*177,3), np.uint8)
# print(level2[0][1])

# for x in range(0, 177):
#     for y in range(0, 177):
#         level2[x + y] = img[x][y]
        # level2[x + y][0] = img[x][y][0]
        # level2[x + y][1] = img[x][y][1]
        # level2[x + y][2] = img[x][y][2]

# for y in range(0, 177):
#     for x in range(0, 177):
#         print("\n")
#         print(img[x][y], end = ' ')
#         print(level2[x+y], end=' ')


#MASK
mask = np.zeros((177*177, 3), dtype = bool)
for x in range(leng + 1, leng + 200*150 + 1):
    mask[x][0] = True
    mask[x][1] = True
    mask[x][2] = True

level2 = level2[mask,...]


# print(level2)

level2Final = np.reshape(level2, (200, 150, 3))

print(level2Final[0][0])
print(level2Final[1][1])

cv2.imwrite('level2Final.png', level2Final)
