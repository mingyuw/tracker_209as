#!/usr/bin/python

import torch
import argparse
import sys
import cv2
import numpy as np
import time

from siamtracker import SiamTracker
import collections


def trackersiamfc():
    Rectangle = collections.namedtuple('Rectangle', ['x', 'y', 'width', 'height'])

    vs = cv2.VideoCapture('../../../../videos/single_car.mp4')

    frame_cnt = 0  # global frame index
    if vs.isOpened() == False:
        print("No video find, exit")
        exit()

    while True:
        frame_cnt += 1
        ret, frame = vs.read()
        if ret:
            frame = cv2.putText(frame, 
                    "Select obj and press space to start tracking", 
                    (50, 50) , 
                    cv2.FONT_HERSHEY_SIMPLEX,
                    1, 
                    (255, 0, 0), 
                    2, 
                    cv2.LINE_AA)
            if frame_cnt < 55:                                    
                cv2.imshow("SiamFC", frame)
            else:
                break
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break


    # select the bounding box of the object we want to track (make
    # sure you press ENTER or SPACE after selecting the ROI)
    box = cv2.selectROI("SiamFC",
                        frame,
                        fromCenter=False,
                        showCrosshair=True)

    region = Rectangle(box[0], box[1], box[2], box[3])
    tracker = SiamTracker(frame, region)

    toc = 0
    frame_cnt = 0
    while True:
        ret, frame = vs.read()
        frame_cnt += 1
        if ret:
            tic = cv2.getTickCount()
    
            region, confidence = tracker.track(frame)
            toc = cv2.getTickCount() - tic

            cv2.rectangle(frame, (int(region.x), int(region.y)), (int(region.x + region.width), int(region.y + region.height)), (0, 255, 255), 3)
            fps = (cv2.getTickFrequency() / toc)
            frame = cv2.putText(frame, 
                    "Tracking Speed {:.1f}fps, press q to quit".format(fps), 
                    (50, 50) , 
                    cv2.FONT_HERSHEY_SIMPLEX,
                    1, 
                    (255, 0, 0), 
                    2, 
                    cv2.LINE_AA)
            cv2.imshow("SiamFC", frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

            print('Tracking Speed {:.1f}fps'.format(fps))
        else:
            break

if __name__ == "__main__":
    trackersiamfc()