import os

from data import common
from data import srdata

import numpy as np
import scipy.misc as misc

import torch
import torch.utils.data as data
import pdb

class XRAY(srdata.SRData):
    def __init__(self, args, train=True):
        super(XRAY, self).__init__(args, train)
        self.repeat = args.test_every // ((19999-4000) // args.batch_size)#(args.n_train // args.batch_size)

    def _scan(self):
        list_hr = []
        list_lr = [[] for _ in self.scale]
        if self.train:
            idx_begin = 4000
            idx_end = 19999#self.args.n_train
        else:
            idx_begin = 1#self.args.n_train
            idx_end = 3999#self.args.offset_val + self.args.n_val

        for i in range(idx_begin, idx_end + 1):
            if self.train:
                filename = 'train_{:0>5}'.format(i)
            else:
                filename = 'test_{:0>5}'.format(i)
            list_hr.append(os.path.join(self.dir_hr, filename + self.ext))
            for si, s in enumerate(self.scale):
                list_lr[si].append(os.path.join(
                    self.dir_lr,
                    '{}'.format(filename + self.ext)
                ))

        return list_hr, list_lr

    def _set_filesystem(self, dir_data):
        self.apath = dir_data + '/xray'
        if self.train:
            self.dir_hr = os.path.join(self.apath, 'HR')
            #self.dir_lr = os.path.join(self.apath, 'LR_bicubic_denoised')
            self.dir_lr = os.path.join(self.apath, 'LR_bicubic')
        else:
            self.dir_lr = os.path.join(self.apath,'test_images_64x64_denoised')
            self.dir_hr = os.path.join(self.apath,'placeholder')
        self.ext = '.png'

    def _name_hrbin(self):
        return os.path.join(
            self.apath,
            'bin',
            '{}_bin_HR.npy'.format(self.split)
        )

    def _name_lrbin(self, scale):
        return os.path.join(
            self.apath,
            'bin',
            '{}_bin_LR_X{}.npy'.format(self.split, scale)
        )

    def __len__(self):
        if self.train:
            return len(self.images_hr) * self.repeat
        else:
            return len(self.images_hr)

    def _get_index(self, idx):
        if self.train:
            return idx % len(self.images_hr)
        else:
            return idx

