import cv2

# import numpy as np

# dts = [10, 20, 30, 40, 50, 70, 90, 100, 110, 150, 170, 200]
dts = [10, 20, 30, 40, 50, ]


def apply_dt(dt, img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (13, 13), 0)
    _, thrsh1 = cv2.threshold(gray, dt, 255, cv2.THRESH_BINARY_INV)
    return thrsh1


cap = cv2.VideoCapture(0)


def autoconf_dt(img):
    dt = []
    height, width, _ = img.shape
    work_pos = 400
    work_width = 245
    work_height = 20
    blur = 13
    crop = img[work_pos:work_pos + work_height,
           0 + int((width - work_width) / 2):width - int((width - work_width) / 2)]
    gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (blur, blur), 0)
    for i in range(0, 256):
        _, thrsh1 = cv2.threshold(gray, i, 255, cv2.THRESH_BINARY_INV)
        m = cv2.moments(thrsh1)["m00"]
        if 255 * work_height * 30 < m < 255 * work_height * 60:
            dt.append(i)
    if len(dt):
        median = dt[len(dt) // 2]
        return median
    return 115


while True:
    ret, image = cap.read()
    cv2.imwrite("../tmp/colored.png", image)
    print("size:", image.shape)
    for i in dts:
        th = apply_dt(i, image)
        cv2.imwrite("../tmp/" + str(i) + ".png", th)

    dt = autoconf_dt(image)
    th = apply_dt(dt, image)
    cv2.imwrite("../tmp/autoconf_" + str(dt) + ".png", th)
    cv2.waitKey(1)
