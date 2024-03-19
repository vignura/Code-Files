import numpy
import matplotlib.pyplot

dataFile = open("NeuralNetworks/mnist_dataset/mnist_train_100.csv", 'r')
dataList = dataFile.readlines()
dataFile.close()
sample = 44
print ("list size:", len(dataList))
print (dataList[sample])

allValues = dataList[sample].split(',')
imageArray = numpy.asfarray(allValues[1:]).reshape((28,28))
# matplotlib.pyplot.imshow(imageArray, cmap='Greys', interpolation='None')
# matplotlib.pyplot.imshow(imageArray, cmap='Greys', interpolation='None')
# matplotlib.pyplot.show()
# scale pixel values (0 - 255) to range (0.01 to 1.0)
scaledInput = (numpy.asfarray(allValues[1:]).reshape((28,28)) / 255 * 0.99) + 0.01
print (scaledInput)