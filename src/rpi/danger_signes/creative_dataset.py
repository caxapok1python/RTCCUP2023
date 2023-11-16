import cv2
import os
import sys

keys = {
    "shot": ord("s"),
    "next": ord("n"),
    "quit": ord("q")
}
classes = ["explosive", "blasting_agent", "flammable_gas", "non-flammable_gas", "flammable_liquid", "inhalation_hazard",
           "flammable_solid", "dangerous_wet", "combustible", "oxidizer", "poison", "infectious", "radioactive",
           "corrosive"]
dataset_dir = "dataset"
cam = cv2.VideoCapture(0)
num_per_sign = 35 if len(sys.argv) == 1 else int(sys.argv[0])


def shot(name, cnt, image):
    # image = cv2.resize(image, (480, 720))
    cv2.imwrite(dataset_dir + "/" + name + "." + str(cnt) + ".png", image)
    print("[+] " + name + " -> " + str(cnt) + "/" + str(num_per_sign) + "\r")


def read_znak(name, num):
    print(name)
    cnt = 0
    while cnt < num:
        ret, image = cam.read()
        while not ret:
            ret, image = cam.read()
        image = cv2.resize(image, (720, 480))
        cv2.imshow("camera", image)
        key = cv2.waitKey(1) & 0xFF

        if key == keys["quit"]:
            exit(0)
        elif key == keys["shot"]:
            shot(name, cnt, image)
            cnt += 1
        elif key == keys["next"]:
            return


def main():
    for sign in classes:
        read_znak(sign, num_per_sign)
        print("[+] Sign name: " + sign)


if __name__ == '__main__':
    main()
