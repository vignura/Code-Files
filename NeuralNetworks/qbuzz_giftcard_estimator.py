import os
import numpy as np
import matplotlib.pyplot
import neuralNetwork as nn
import neuralNetworkManager as nnm
import time
from datetime import datetime

class giftCardEstimator (nnm.neuralNetworkManager):
    def trainModel(self, trainingDataList, epochs):
        print ("training dataset size: ", len(trainingDataList))
        self.epochs = epochs
        for e in range(epochs):
            print ("training epoch:", e)
            for record in trainingDataList:
                qbuzzUserData = record.split(',')
                # print (qbuzzUserData)
                # here customer ID and gift card amount are not needed
                inputs = self.normalizeData(qbuzzUserData[1:14])
                # print ("normalized input data:\n", inputs)
                # normalize gift card amount (max seems to be 200)
                amountNormalized = float(qbuzzUserData[-1]) / 200
                if amountNormalized < 0.01:
                    amountNormalized = 0.01
                targets = np.zeros(self.nn.onodes) + amountNormalized
                # print(targets)
                self.nn.train(inputs, targets)

    def normalizeData(self, userData):
        normalizedData = np.zeros(self.nn.inodes)
        # print (userData)
        # normalize signup age to 4500 days roughly 12 years
        if userData[0] != "":
            normSingupAge = float(self.conDateToAge(userData[0])) / 4500.0
        else:
            # for hole, fill the maximum value
            normSingupAge = 0.99
        normalizedData[0] = normSingupAge
        # normalize last order age to 4500 days roughly 12 years
        if userData[1] != "":
            normLastOrderAge = float(self.conDateToAge(userData[1])) / 4500.0
        else:
            # for hole fill the minimum value
            normLastOrderAge = 0.01
        normalizedData[1] = normLastOrderAge
        # normalize orders to 1000
        if userData[2] != "":
            normOrders = float(userData[2]) / 1000.0
        else:
            normOrders = 0.01
        normalizedData[2] = normOrders
        # normalize minimum first bill to 3000
        if userData[4] != "":
            normMinBill = float(userData[4]) / 3000.0
        else:
            normMinBill = 0.01
        normalizedData[4] = normMinBill
        # now normalize minimum bill to 3000 as well
        if userData[3] != "":
            normMaxBill = float(userData[3]) / 3000.0
        else:
            # for hole use minimum bill
            normMaxBill = normMinBill
        normalizedData[3] = normMaxBill
        # normalize reviews to 300
        if userData[5] != "":
            normReviews = float(userData[5]) / 300.0
        else:
            normReviews = 0.01
        normalizedData[5] = normReviews
        # normalize comments to 300 as well
        if userData[6] != "":
            normComments = float(userData[6]) / 300.0
        else:
            normComments = 0.01
        normalizedData[6] = normComments
        # normalize images to 300
        if userData[7] != "":
            normImages = float(userData[7]) / 300.0
        else:
            normImages = 0.01
        normalizedData[7] = normImages
        # normalize issues to 300
        if  userData [8] != "":
            normIssues = float(userData[8]) / 300.0
        else:
            normIssues = 0.01
        normalizedData[8] = normIssues
        # normalize orders returned to 100
        if userData[9] != "":
            normReturns = float(userData[9]) / 100.0
        else:
            normReturns = 0.01
        normalizedData[9] = normReturns
        # normalize category 
        category = {"Active": 0.99, "Passive": 0.1, "Inactive": 0.01}
        if userData[10] != "":
            normCategory = category[userData[10]]
        else:
            normCategory = category["Inactive"]
        normalizedData[10] = normCategory
        # normalize gender, don't add much weight to gender
        gender = {"Male": 0.1, "Female": 0.11}
        if userData[11] != "":
            normGender = gender[userData[11]]
        else:
            normGender = gender["Male"]
        normalizedData[11] = normGender
        # normalize premium
        premium = {"Yes": 0.99, "No": 0.01}
        if userData[12] != "":
            normPremium = premium[userData[12]]
        else:
            normPremium = premium["No"]
        normalizedData[12] = normPremium
        # print("normSingupAge: ", normSingupAge, "normLastOrderAge: ", normLastOrderAge, "orders: ", normOrders, "normMaxBill: ", normMaxBill)
        # print ("normMinBill: ", normMinBill, "normReviews: ", normReviews, "normComments: ", normComments, "normImages", normImages)
        # print ("normIssues:", normIssues, "normReturns: ", normReturns, "normCategory: ", normCategory, "normGender: ", normGender)
        # print ("normPremium: ", normPremium)
        return normalizedData

    # returns age in days with reference as 31st Dec 2021
    def conDateToAge(self, dateString):
        refDate = datetime(2021, 12, 31, 23, 59)
        date = datetime.strptime(dateString, '%m/%d/%Y %I:%M %p')
        age = refDate - date
        return age.days

    def trainModelCSV(self, fileName, epochs):
        if os.path.exists(fileName):
            trainingDataFile = open(fileName, 'r')
            trainingDataList = trainingDataFile.readlines()
            trainingDataFile.close()
            self.trainModel(trainingDataList, epochs)
        else:
            print (fileName, "does not exist!")
    def runModel(self, testDataList):
        pass
    def runModelCSV(self, testDataFile):
        pass
    def testModel(self, testDataList):
        scorecard = []
        print ("test dataset size: ", len(testDataList))
        for record in testDataList:
            qbuzzUserData = record.split(',')
            inputs = self.normalizeData(qbuzzUserData[1:14])
            outputs = self.nn.query(inputs)
            estimatedAmount = outputs[0] * 200
            correctAmount = float(qbuzzUserData[-1])
            # compute 1 - deviation
            scorecard.append(1.0 - (abs(correctAmount - estimatedAmount) / correctAmount))
        return scorecard

    def testModelCSV(self, fileName):
        if os.path.exists(fileName):
            testDataFile = open(fileName, 'r')
            testDataList = testDataFile.readlines()
            testDataFile.close()
            return self.testModel(testDataList)
        else:
            print (fileName, "does not exist!")

# define the neural network parameter
inputNodes = 13 # user profile parameters
hiddenNodes = 50
outputNodes = 1 # gift card amount
learningRate = 0.5
epochs = 50
shouldSave = True
modelFile = "NeuralNetworks/saved_networks/gift_card_estimator_nn_ip(13)_hn(50)_on(1)_lr(0.5)_ep(50).npy"

if os.path.exists(modelFile):
    # load trained model
    n = nn.neuralNetwork()
    estimator = giftCardEstimator(n)
    estimator.loadNetwork(modelFile)
    # don't save when loading trained model
    shouldSave = False
else: 
    # create neural network and gfit card estimator
    n = nn.neuralNetwork(inputNodes, hiddenNodes, outputNodes, learningRate)
    estimator = giftCardEstimator(n)

    # train netowrk
    startTime = time.time()
    estimator.trainModelCSV("NeuralNetworks/Qbuzz_dataset/train_10K.csv", epochs)
    print("training time:", time.time() - startTime)

# test network
startTime = time.time()
scorecard = estimator.testModelCSV("NeuralNetworks/Qbuzz_dataset/test_train_2K.csv")
print("test run time:", time.time() - startTime)
scorecard_array = np.asarray(scorecard)
print("performance:", scorecard_array.sum() / scorecard_array.size)

# save network
if shouldSave:
    estimator.saveNetwork("NeuralNetworks/saved_networks/", "gift_card_estimator_")