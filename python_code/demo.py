import numpy as np 
import cv2 
def foo(img, img_row, img_col):
    img = img.reshape((img_row, img_col, -1))
    print(img.shape)
    cv2.imwrite('py_im.jpg', img)
    return np.random.randn(9).reshape(3, 3)
    # return name
