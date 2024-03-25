import os
import numpy as np
import matplotlib.pyplot
import neuralNetwork as nn
import neuralNetworkManager as nnm
import time

class mnistClassifier(nnm.neuralNetworkManager):
    def trainModel(self, trainingDataList, epochs):
        self.epochs = epochs
        for e in range(epochs):
            print ("training epoch:", e)
            for record in trainingDataList:
                allValues = record.split(',')
                # scale pixel values (0 - 255) to range (0.01 to 1.0)
                inputs = (np.asfarray(allValues[1:]) / 255 * 0.99) + 0.01
                # create target output values (all 0.01 except the desiered label which is 0.99)
                targets = np.zeros(outputNodes) + 0.01
                targets[int(allValues[0])] = 0.99
                self.nn.train(inputs, targets)

    def trainModelCSV(self, fileName, epochs):
        if os.path.exists(fileName):
            trainingDataFile = open(fileName, 'r')
            trainingDataList = trainingDataFile.readlines()
            trainingDataFile.close()
            self.trainModel(trainingDataList, epochs)
        else:
            print (fileName, "does not exist!")

    def testModel(self, testDataList):
        scorecard = []
        for record in testDataList:
            allValues = record.split(',')
            inputs = (np.asfarray(allValues[1:]) / 255 * 0.99) + 0.01
            outputs = n.query(inputs)
            # index with highest value corresponds to label
            label = np.argmax(outputs)
            correct_label = int(allValues[0])
            # print("correct label:", correct_label, "neuralNetwork answer:", label)
            if (label == correct_label):
                scorecard.append(1)
            else:
                scorecard.append(0)
        return scorecard

    def testModelCSV(self, fileName):
        if os.path.exists(fileName):
            testDataFile = open(fileName, 'r')
            testDataList = testDataFile.readlines()
            testDataFile.close()
            return self.testModel(testDataList)
        else:
            print (fileName, "does not exist!")

################################################################################################
inputNodes = 784
hiddenNodes = 500
outputNodes = 10
learningRate = 0.1
epochs = 1
shouldSave = True
# modelFile = ""
modelFile = "NeuralNetworks/saved_networks/nn_ip(784)_hn(500)_on(10)_lr(0.1)_ep(1).npy"
# modelFile = "NeuralNetworks/saved_networks/nn_ip(784)_hn(100)_on(10)_lr(0.1)_ep(5).npy"

if os.path.exists(modelFile):
    # load trained model
    n = nn.neuralNetwork()
    mnist = mnistClassifier(n)
    mnist.loadNetwork(modelFile)
    # don't save when loading trained model
    shouldSave = False
else: 
    # create neural network and mnist classifier
    n = nn.neuralNetwork(inputNodes, hiddenNodes, outputNodes, learningRate)
    mnist = mnistClassifier(n)

    # train network
    startTime = time.time()
    mnist.trainModelCSV("NeuralNetworks/mnist_dataset/mnist_train.csv", epochs)
    print("training time:", time.time() - startTime)

# test network
startTime = time.time()
scorecard = mnist.testModelCSV("NeuralNetworks/mnist_dataset/mnist_test.csv")
print("test run time:", time.time() - startTime)
# print scorecard and performance
# print("score card:", scorecard)
scorecard_array = np.asarray(scorecard)
print("performance:", scorecard_array.sum() / scorecard_array.size)

# save network
if shouldSave:
    mnist.saveNetwork("NeuralNetworks/saved_networks/")

# trainingDataFile = open("NeuralNetworks/mnist_dataset/mnist_train.csv", 'r')
# trainingDataList = trainingDataFile.readlines()
# trainingDataFile.close()
# sample = 44
# print ("list size:", len(trainingDataList))
# print (trainingDataList[sample])
# allValues = trainingDataList[sample].split(',')
# imageArray = np.asfarray(allValues[1:]).reshape((28,28))
# matplotlib.pyplot.imshow(imageArray, cmap='Greys', interpolation='None')
# matplotlib.pyplot.imshow(imageArray, cmap='Greys', interpolation='None')
# matplotlib.pyplot.show()
