import cv2
import numpy as np

# Load the cascade
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# To capture video from webcam. 
cap = cv2.VideoCapture(0)
# To use a video file as input 
# cap = cv2.VideoCapture('filename.mp4')

ball = cv2.imread('/home/sleepyhead/Desktop/ARK Task Round/Task2.2faceDetectionGame/ball.png')
ball_resized = cv2.resize(ball, dsize = (100, 100))
#rows, cols, channels = ball.shape()

x0 = 1
y0 = 1
x00 = 1
y00 = 1
time = 0
velx = 10
vely = 6



while True:
    # Read the frame
    _, img = cap.read()

    img = cv2.flip(img, 1)
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray)
    # Draw the rectangle around each face
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)

    ###############################
    print(x0, y0)
    if(x0 >= img.shape[0] - 100):
        time0 = time - 1
        velx = -1*velx
        print("Collision!!!!!!!!!!!!", velx)

    if(x0 <= 0):
        time = 1
        velx = -1*velx
        print("Collision")

    if(velx >= 0):
        x0 = x00 + velx*time
        y0 = y00 + vely*time
    elif(velx < 0):
        x0 = img.shape[0] + velx*(time -time0) - 100
        y0 = y00 + vely*time
    #    y0 = img.shape[1] + vely*time - 100
        print(x0, y0)


    time +=1

    #updaing frame
    img[x0:x0 + 100, y0: y0 + 100] = ball_resized
    # Display
    cv2.imshow('img', img)
    # Stop if escape key is pressed
    k = cv2.waitKey(30) & 0xff
    if k==27:
        break

    



# Release the VideoCapture object

cap.release()