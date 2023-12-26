import numpy as np


class CircularBuffer:

    def __init__(self, size_max, dtype=int):
        self.max = size_max
        self.data = np.empty(size_max, dtype=dtype)
        self.data.fill(0.0)

        self.size = 0

    def append(self, value):
        self.data = np.roll(self.data, 1)
        self.data[0] = value

        self.size += 1
        if len(self.data) == self.max:
            self.__class__ = CircularBufferFull

    def get(self):
        return self.data

    def __getitem__(self, key):
        return self.data[key]


class CircularBufferFull(CircularBuffer):
    def append(self, value):
        self.data = np.roll(self.data, 1)
        self.data[0] = value

