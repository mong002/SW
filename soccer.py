import numpy as np
import cv2 as cv

img = cv.imread('soccer.jpg')
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

def mygray(red, green, blue,r,c):

    temp = np.zeros((r, c))
    gray = np.zeros((r, c))
    for i in range(r):
        for j in range(c):
            temp[i,j] = 0.299 * red[i, j] + 0.587 * green[i, j] + 0.114 * blue[i, j]
            #gray[i, j] = np.uint8(temp[i, j])
        
        if (i%50) == 0:
            print('#')
    
    gray = np.uint8(temp)
    return gray

red = img[:, :, 2]
green = img[:, :, 1]
blue = img[:, :, 0]
r, c, ch = img.shape

g = mygray(red, green, blue, r, c)
cv.imshow('',g)

#r, c, ch = img.shape

print(r, c, ch)

print(img.shape)

'''
cv.imshow('', gray)
cv.imshow('', red)
cv.imshow('', green)
cv.imshow('', blue)
'''

cv.waitKey(0)