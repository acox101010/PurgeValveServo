# -*- coding: utf-8 -*-
"""
Created on Tue Sep 24 12:01:51 2019
@author: A8DPDZZ
Start Reading Analog Values into DAQ
"""

#import libraries
import nidaqmx
import cv2
import time

#Function to capture image
def get_image(): 
    cam_port = 0 #cam port defined
    camera = cv2.VideoCapture(cam_port)
    #cv2.namedWindow("Camera Feed") #Removed window as it is to slow for capture
    retval, im = camera.read() #retrieve image out of VideoCapture oject
    return im
    del(camera)

#initiat daqmx to read input voltage values
with nidaqmx.Task() as task:
    print('Test Started on:',str(time.strftime('%Y_%m_%d_%H_%M_%S'))) #timestamp printed to console
    task.ai_channels.add_ai_voltage_chan("Dev1/ai0")
    data = task.read() 
    #Need to convert Raw transducer values to pressures!!!
    while (data >= 0):
        try:
            data = task.read() # store DAQ reading in data variable
            if (data < 4.75 and data >= 4.65):
                #img_time = time.strftime('%X-%x') # variable to hold time date from cpu
                camera_capture = get_image()
                #full cylinder
                cv2.imwrite('FullCyl'+str(time.strftime('%Y_%m_%d_%H_%M_%S'))+'.png', camera_capture)
                print(data,'FullCyl_Captured')
                #del(camera)
            elif (data < 3.5 and data >=3.40):
                camera_capture = get_image()
                #3/4 Cylinder
                cv2.imwrite('3-4_Cyl'+str(time.strftime('%Y_%m_%d_%H_%M_%S'))+'.png', camera_capture)
                print(data,'3-4_Cyl_Captured')
            elif (data < 2.5 and data >=2.40):
                camera_capture = get_image()
                #1/2 Cylinder
                cv2.imwrite('1-2_Cyl'+str(time.strftime('%Y_%m_%d_%H_%M_%S'))+'.png', camera_capture)
                print(data,'1-2_Cyl_Captured')
            elif (data < 1.5 and data >=1.40):
                camera_capture = get_image()
                #1/3 Cylinder
                cv2.imwrite('1-3_Cyl'+str(time.strftime('%Y_%m_%d_%H_%M_%S'))+'.png', camera_capture)
                print(data,'1-3_Cyl_Captured')
            else:
                print(data,str(time.strftime('%Y_%m_%d_%H_%M_%S')))
        except (KeyboardInterrupt, SystemExit):
            print('loop exited by user or error')
print(data) #print last data point that was <0
print('Test Completed')

"""
Start Post Processing Images after Completion of Capture
"""


