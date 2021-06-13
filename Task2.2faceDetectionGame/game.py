import cv2
import numpy as np
import math

#initial contitions  
pos = [36,36] 
vel = [8,12]
dt = 1

frame = 0
frame_col = 0

game_stat = False

def playerCollision(head):
    dist = math.sqrt((head[0]-pos[0])*(head[0]-pos[0])+ (head[0]-pos[0])*(head[0]-pos[0])) #distance bw player and ball
    # if (dist <= 35 + head[2]):
    global frame_col
    if (dist <= 35 + head[2]):
        frame_col = frame
        vel[1] = -vel[1]
        # print("Player collision!!!!!!!!!!!")
        # vel[0] = -vel[0];

def frame_update(img, dt, head):
    global pos
    global frame
    global frame_col
    frame += 1
    wallCollision() 
    # print(frame)
    if((frame - frame_col) > 25):
        # print(frame - frame_col)
        playerCollision(head)
    pos[0] = pos[0] + vel[0]*dt
    pos[1] = pos[1] + vel[1]*dt
    cv2.circle(img, (pos[0],pos[1]), 35, (0, 0, 255), -1)
    # cv2.line(img,(pos[0],pos[1]),(head[0], head[1]),(0, 0, 0),2,8)
    # print(pos[0], pos[1],head[0], head[1], vel[0], vel[1])
    

def wallCollision():
    global game_stat
    if (pos[0] + 35 >= 640) or (pos[0]-35 <= 0):
        vel[0] = -vel[0] 
    if (pos[1]-35 <= 0):
        vel[1] = -vel[1] 
    if (pos[1] + 35 >= 480):
        game_stat = True



    

# def playerCollision(head):
#     dist = math.sqrt((head[0]-pos[0])*(head[0]-pos[0])+ (head[0]-pos[0])*(head[0]-pos[0])) #distance bw player and ball
#     impactAngle = 0
#     velN = 0
#     velT = 0
#     if (dist <= 35 + head[2]):
#         impactAngle = math.atan(abs((pos[1]-head[1])/(pos[0]-head[0])))
#         velN = -(vel[0]*math.cos(impactAngle) + vel[1]*math.sin(impactAngle))
#         velT = vel[0]*math.sin(impactAngle) + vel[1]*math.cos(impactAngle)
#         print("Player collision!!!!!!!!!!!")
#         vel[0] = int(velT*math.sin(impactAngle) + velN*math.cos(impactAngle));  vel[1] = int(velN*math.sin(impactAngle) + velT*math.cos(impactAngle))
    
GameOver = cv2.imread('Gameover.jpg', cv2.IMREAD_COLOR)

# Load the cascade
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# To capture video from webcam. 
cap = cv2.VideoCapture(0)

while True:
    # Read the frame
    _, img = cap.read()
    img = cv2.flip(img, 1)

    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    

    # Detect the faces

    faces = face_cascade.detectMultiScale(gray)
   
    # marking detected face with circle                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    for (x, y, w, h) in faces: 
        # cv2.circle(img, (x, y), int((w+h)/3.5), (255, 0, 0), 2)
        cv2.circle(img, (x+w//2, y + h//2), int((w+h)/3.5), (255, 0, 0), 2)

    # for (x, y, w, h) in faces:
    #     cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)

    # coordinates of centre of face
    head = [x+w//2, y + h//2, (int((w+h)/3.5))]
        #print(head[0], head[1])

    # updating frame
    frame_update(img, dt, head)

    loop = 1
    if(game_stat == True):
        # font = cv2.FONT_HERSHEY_SIMPLEX
        # cv2.putText(img,'Game Over',(10,400), font, 3,(255,255,255),2,cv2.LINE_AA)
        # for loop in range(1000):
        #     cv2.imshow('img', img)
        #     loop += 1
        #     print("here")
        exit(-1)

         
    # display
    cv2.imshow('img', img)

    

    # Stop if escape key is pressed
    k = cv2.waitKey(30) & 0xff
    if k==27:
        break

# Release the VideoCapture object

cap.release()

#########################################################################
"""
TODO
improve collision response
improve face detection by using additional parameters in haar cascade(eg. min neighbours)

4. Read cv2.cvtcolor


"""



"""
REFERENCES
**********

Face Detection using CV haarcascades
>Face detection using Haar cascades is a machine learning based approach where a cascade function is trained with a set of input data. 
>OpenCV already contains many pre-trained classifiers for face, eyes, smiles.
    https://towardsdatascience.com/face-detection-in-2-minutes-using-opencv-python-90f89d7c0f81
    https://www.bogotobogo.com/python/OpenCV_Python/python_opencv3_Image_Object_Detection_Face_Detection_Haar_Cascade_Classifiers.php

Drawing basic shapes in CV
    https://docs.opencv.org/3.4/d3/d96/tutorial_basic_geometric_drawing.html
    https://docs.opencv.org/master/d6/d6e/group__imgproc__draw.html#gaf10604b069374903dbd0f0488cb43670

Collision Detection and response
    https://www.youtube.com/watch?v=eED4bSkYCB8 ,Building Collision Simulations: An Introduction to Computer Graphics



"""

