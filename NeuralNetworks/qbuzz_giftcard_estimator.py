import os
import numpy as np
import matplotlib.pyplot
import neuralNetwork as nn
import neuralNetworkManager as nnm
import time
from datetime import datetime
import math

class giftCardEstimator (nnm.neuralNetworkManager):
    def trainModel(self, trainingDataList, epochs):
        print ("training dataset size: ", len(trainingDataList))
        self.epochs = epochs
        # normalize data
        normInputs = []
        normtargets = []
        for record in trainingDataList:
            qbuzzUserData = record.split(',')
            normInputs.append(self.normalizeData(qbuzzUserData[1:14]))
            amountNormalized = float(qbuzzUserData[-1]) / 200
            # amountNormalized = math.log(float(qbuzzUserData[-1])) / 5.3 # ln(200)
            if amountNormalized < 0.01:
                amountNormalized = 0.01
            normtargets.append(np.zeros(self.nn.onodes) + amountNormalized)
        
        for e in range(epochs):
            print ("training epoch:", e)
            for index in range(len(trainingDataList)):
                self.nn.train(normInputs[index], normtargets[index])

    def normalizeData(self, userData):
        normalizedData = []
        normDataMin = 0.1
        normDataMax = 0.9
        # print (userData)
        # normalize signup age to 4500 days roughly 12 years
        if userData[0] != "":
            normSingupAge = 1.0 - (float(self.conDateToAge(userData[0])) / 4500.0)
        else:
            # for hole, fill the maximum value
            normSingupAge = normDataMax # assume new user
        normalizedData.append(normSingupAge)
        # normalize last order age to 4500 days roughly 12 years
        if userData[1] != "":
            normLastOrderAge = 1.0 - (float(self.conDateToAge(userData[1])) / 4500.0)
        else:
            # for hole fill the minimum value
            normLastOrderAge = normDataMax # assume new user
        normalizedData.append(normLastOrderAge)
        # normalize orders to 1000
        if userData[2] != "":
            normOrders = float(userData[2]) / 1000.0
        else:
            normOrders = normDataMin
        normalizedData.append(normOrders)
        # normalize minimum first bill to 500
        if userData[4] != "":
            normMinBill = float(userData[4]) / 500.0
        else:
            normMinBill = normDataMin
        normalizedData.append(normMinBill)
        # now normalize minimum bill to 3000 as well
        if userData[3] != "":
            normMaxBill = float(userData[3]) / 3000.0
        else:
            # for hole use minimum bill
            normMaxBill = normMinBill
        normalizedData.append(normMaxBill)
        # normalize reviews to 300
        if userData[5] != "":
            normReviews = float(userData[5]) / 300.0
        else:
            normReviews = normDataMin
        normalizedData.append(normReviews)
        # normalize comments to 300 as well
        if userData[6] != "":
            normComments = float(userData[6]) / 300.0
        else:
            normComments = normDataMin
        normalizedData.append(normComments)
        # normalize images to 300
        if userData[7] != "":
            normImages = float(userData[7]) / 300.0
        else:
            normImages = normDataMin
        normalizedData.append(normImages)
        # normalize issues to 300
        if  userData [8] != "":
            normIssues = float(userData[8]) / 300.0
        else:
            normIssues = normDataMin
        normalizedData.append(normIssues)
        # normalize orders returned to 100
        if userData[9] != "":
            normReturns = float(userData[9]) / 100.0
        else:
            normReturns = normDataMin
        normalizedData.append(normReturns)
        # normalize category 
        category = {"Active": normDataMin + 0.2, "Passive": normDataMin, "Inactive": normDataMin}
        if userData[10] != "":
            normCategory = category[userData[10]]
        else:
            normCategory = category["Inactive"]
        normalizedData.append(normCategory)
        # normalize gender, don't add much weight to gender
        gender = {"Male": normDataMin, "Female": normDataMin}
        if userData[11] != "":
            normGender = gender[userData[11]]
        else:
            normGender = gender["Male"]
        normalizedData.append(normGender)
        # normalize premium
        premium = {"Yes": normDataMax, "No": normDataMin}
        if userData[12] != "":
            normPremium = premium[userData[12]]
        else:
            normPremium = premium["No"]
        normalizedData.append(normPremium)
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
            estimatedAmount = outputs[0].item() * 200.0
            # estimatedAmount = math.exp(outputs[0].item() * 5.3)
            correctAmount = float(qbuzzUserData[-1])
            # compute 1 - deviation
            score = 1.0 - (abs(correctAmount - estimatedAmount) / correctAmount)
            # score = 1.0 - (abs(correctAmount - estimatedAmount) / 200)
            if (score < 0):
                score = 0
            scorecard.append(score)
            if (len(testDataList) <= 100):
                print ("estimated amount: ", estimatedAmount, "correct amount: ", correctAmount, "score: ", scorecard[-1])
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
hiddenNodes = 10
outputNodes = 1 # gift card amount
learningRate = 0.01
epochs = 1000
shouldSave = True
modelFile = ""
modelFile = "NeuralNetworks/saved_networks/gift_card_estimator_nn_ip(13)_hn(10)_on(1)_lr(0.01)_ep(1000).npy"
# modelFile = "NeuralNetworks/saved_networks/gift_card_estimator_nn_ip(13)_hn(5)_on(1)_lr(0.5)_ep(100).npy"

if os.path.exists(modelFile):
    # load trained model
    n = nn.neuralNetwork()
    estimator = giftCardEstimator(n)
    estimator.loadNetwork(modelFile)
    # don't save when loading trained model
    shouldSave = False
    shouldTrain = False
    # shouldTrain = True
else: 
    # create neural network and gfit card estimator
    n = nn.neuralNetwork(inputNodes, hiddenNodes, outputNodes, learningRate)
    estimator = giftCardEstimator(n)
    shouldTrain = True

if shouldTrain:
    # train netowrk
    startTime = time.time()
    estimator.trainModelCSV("NeuralNetworks/Qbuzz_dataset/train_10K.csv", epochs)
    print("training time:", time.time() - startTime)

# test network
startTime = time.time()
scorecard = estimator.testModelCSV("NeuralNetworks/Qbuzz_dataset/test_train_2K.csv")
print("test run time:", time.time() - startTime)
#print("score card:", scorecard)
scorecard_array = np.asarray(scorecard)
print("performance:", scorecard_array.sum() / scorecard_array.size)

# save network
if shouldSave:
    estimator.saveNetwork("NeuralNetworks/saved_networks/", "gift_card_estimator_")