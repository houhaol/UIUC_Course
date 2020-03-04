Dominic Roberts djrbrts2
Houhao Liang houhaol2

We adapted "Image Super-Resolution Using Very Deep Residual Channel Attention Networks", (ECCV 2018) from https://github.com/yulunzhang/RCAN. We chose this method as it achieved state-of-the-art image super-resolution results on Urban100 and Manga109 image super-resolution datasets. The specificities of its architecture are residual groups ("Residual in Residual" structures) and a channel attention mechanism that rescales channel-specific features. We did not make any changes to the network structure. However we did adapt the data loaders to only deal with the RGB channels of our images and changed the training parameters as specified in RCAN_TrainCode/code/option.py. We preprocessed images by merely subtracting the mean RGB value. We trained our model using ADAM with an initial learning rate of 1e-4 and decayed the learning rate by a factor of 0.5 every 3 epochs. We trained for 10 epochs using an L1 loss.


