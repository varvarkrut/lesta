from collections import deque


class CircularBuffer:
    def __init__(self, maxlen):
        self.buffer = deque(maxlen=maxlen)

    def append(self, element):
        self.buffer.append(element)

    def get(self):
        return list(self.buffer)
