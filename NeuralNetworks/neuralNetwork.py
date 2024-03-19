import numpy
import scipy.special

class neuralNetwork:
    def __init__(self, inputNodes, hiddenNodes, outputNodes, learningRate):
        self.inodes = inputNodes
        self.hnodes = hiddenNodes
        self.onodes = outputNodes
        self.lr = learningRate
        print (neuralNetwork.__init__.__qualname__, ": input nodes:", self.inodes,
                " hidden nodes:", self.hnodes, " output nodes:", self.onodes, " learning rate:", self.lr)
        # initialize weight matrices
        # simple random weights
        # self.wih = numpy.random.rand(self.hnodes, self.inodes) - 0.5
        # self.who = numpy.random.rand(self.onodes, self.hnodes) - 0.5
        # random weights based on normal distribution
        self.wih = numpy.random.normal(0.0, pow (self.inodes, -0.5), (self.hnodes, self.inodes))
        self.who = numpy.random.normal(0.0, pow (self.hnodes, -0.5), (self.onodes, self.hnodes))
        print (neuralNetwork.__init__.__qualname__,": Weights input hidden")
        print (self.wih)
        print (neuralNetwork.__init__.__qualname__,": Weights hidden output")
        print (self.who )
        # set the activation function
        self.activationFunction = lambda x : scipy.special.expit(x)
        pass
    def train(self, inputsList, targetList):
        # convert list to 2d array
        inputs = numpy.array(inputsList, ndmin=2).T
        targets = numpy.array(targetList, ndmin=2).T
        # hidden layer
        hiddenInputs = numpy.dot(self.wih, inputs)
        hiddenOutputs = self.activationFunction(hiddenInputs)
        # final layer
        finalInputs = numpy.dot(self.who, hiddenOutputs)
        finalOutpus = self.activationFunction(finalInputs)
        # compute the error
        outputErrors = targets - finalOutpus
        # compute hidden layer error
        hiddenErrors = numpy.dot(self.who.T, outputErrors)
        # update hidden layer weights
        self.who += self.lr * numpy.dot(outputErrors * finalOutpus * (1.0 - finalOutpus), numpy.transpose(hiddenOutputs))
        # update the input layer weights
        self.wih += self.lr * numpy.dot(hiddenErrors * hiddenOutputs * (1.0 - hiddenOutputs), numpy.transpose(inputs))
        pass
    def query(self, inputsList):
        # convert input list to 2d input array
        inputs = numpy.array(inputsList, ndmin=2).T
        print (neuralNetwork.query.__qualname__,": inputs")
        print (inputs)
        # calculate input to hidden nodes
        hiddenInputs = numpy.dot(self.wih, inputs)
        print (neuralNetwork.query.__qualname__,": hidden inputs")
        print (hiddenInputs)
        # calculate the hidden outputs
        hiddenOutputs = self.activationFunction(hiddenInputs)
        print (neuralNetwork.query.__qualname__,": hidden outputs")
        print (hiddenOutputs)
        # calculate the signals for the final layer
        finalInputs = numpy.dot(self.who, hiddenOutputs)
        print (neuralNetwork.query.__qualname__,": final inputs")
        print (finalInputs)
        finalOutpus = self.activationFunction(finalInputs)
        print (neuralNetwork.query.__qualname__,": final outputs")
        print (finalOutpus)
        return finalOutpus

inputNodes = 3
hiddenNodes = 3
outputNodes = 3
learningRate = 0.5

n = neuralNetwork(inputNodes, hiddenNodes, outputNodes, learningRate)
n.query([1.0, 0.5, -1.5])