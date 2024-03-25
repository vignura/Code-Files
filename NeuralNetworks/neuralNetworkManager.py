import os
import numpy as np
import neuralNetwork

class neuralNetworkManager:
    def __init__(self, nn):
        self.nn = nn
        self.epochs = 1

    def generateFileName(self):
        fileName = f"nn_ip({self.nn.inodes})_hn({self.nn.hnodes})_on({self.nn.onodes})_lr({self.nn.lr})_ep({self.epochs}).npy"
        return fileName

    def saveNetwork(self, path):
        fileName = path + self.generateFileName()
        nn = {
            'inodes': self.nn.inodes,
            'hnodes': self.nn.hnodes,
            'onodes': self.nn.onodes,
            'lr': self.nn.lr,
            'wih': self.nn.wih,
            'who': self.nn.who
        }
        np.save(fileName, nn)
        print ("Saved neural netowrk to file", fileName)

    def loadNetwork(self, fileName):
        if os.path.exists(fileName):
            nn = np.load(fileName, allow_pickle=True).item()
            self.nn.inodes = nn['inodes']
            self.nn.hnodes = nn['hnodes']
            self.nn.onodes = nn['onodes']
            self.nn.lr = nn['lr']
            self.nn.wih = nn['wih']
            self.nn.who = nn['who']
            print ("loaded neural network from file", fileName)
        else:
            print (fileName,"does not exist")

    def trainModel(self, trainingDataList, epochs):
        # Abstract method for training the model
        raise NotImplementedError("This method should be implemented by subclasses.")

    def testModel(self, testDataList):
        # Abstract method for running the trained model
        raise NotImplementedError("This method should be implemented by subclasses.")
        
