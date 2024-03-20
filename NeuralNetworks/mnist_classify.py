import numpy
import matplotlib.pyplot
import neuralNetwork
import time

inputNodes = 784
hiddenNodes = 200
outputNodes = 10
learningRate = 0.1

startTime = time.time()
n = neuralNetwork.neuralNetwork(inputNodes, hiddenNodes, outputNodes, learningRate)
trainingDataFile = open("NeuralNetworks/mnist_dataset/mnist_train.csv", 'r')
trainingDataList = trainingDataFile.readlines()
trainingDataFile.close()

# sample = 44
# print ("list size:", len(trainingDataList))
# print (trainingDataList[sample])
# allValues = trainingDataList[sample].split(',')
# imageArray = numpy.asfarray(allValues[1:]).reshape((28,28))
# matplotlib.pyplot.imshow(imageArray, cmap='Greys', interpolation='None')
# matplotlib.pyplot.imshow(imageArray, cmap='Greys', interpolation='None')
# matplotlib.pyplot.show()

# train network
epochs = 5
for e in range(epochs):
    print ("training epoch:", e)
    for record in trainingDataList:
        allValues = record.split(',')
        # scale pixel values (0 - 255) to range (0.01 to 1.0)
        inputs = (numpy.asfarray(allValues[1:]) / 255 * 0.99) + 0.01
        # create target output values (all 0.01 except the desiered label which is 0.99)
        targets = numpy.zeros(outputNodes) + 0.01
        targets[int(allValues[0])] = 0.99
        n.train(inputs, targets)

print("training time:", time.time() - startTime)
startTime = time.time()

# test network
testDataFile = open("NeuralNetworks/mnist_dataset/mnist_test.csv", 'r')
testDataList = testDataFile.readlines()
testDataFile.close()
scorecard = []
for record in testDataList:
    allValues = record.split(',')
    inputs = (numpy.asfarray(allValues[1:]) / 255 * 0.99) + 0.01
    outputs = n.query(inputs)
    # index with highest value corresponds to label
    label = numpy.argmax(outputs)
    correct_label = int(allValues[0])
    # print("correct label:", correct_label, "neuralNetwork answer:", label)
    if (label == correct_label):
        scorecard.append(1)
    else:
        scorecard.append(0)

print("test run time:", time.time() - startTime)
# print scorecard and performance
# print("score card:", scorecard)
scorecard_array = numpy.asarray(scorecard)
print("performance:", scorecard_array.sum() / scorecard_array.size)