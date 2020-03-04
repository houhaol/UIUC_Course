import os
import pdb
import cv2
import numpy as np


resdir = '/media/storage2/dominic/RCAN/RCAN_TrainCode/experiment/xray/results'

for i in [j for j in sorted(os.listdir(resdir)) if '.png' in j]:
    os.rename(os.path.join(resdir,i),
              i.split('_x2')[0] + '.png')


subdir = resdir #'submission'
newsubdir = 'submission_1channel'

for i in os.listdir(subdir):
    image = cv2.imread(os.path.join(subdir,i))
    alpha_channel = np.ones((128,128))*255
    newimage = np.concatenate((image,alpha_channel[:,:,None]),axis=2)
    cv2.imwrite(os.path.join(newsubdir,i),newimage)
