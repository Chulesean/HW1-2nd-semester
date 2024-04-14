#include <iostream>
#include <stdexcept>

template<typename T>
class Deque {
private:
    T* buffer;
    size_t head;
    size_t tail;
    size_t bufferSize;
    size_t dequeSize;

    void resize() {
        size_t newBufferSize = bufferSize == 0 ? 1 : 2 * bufferSize;
        T* newBuffer = new T[newBufferSize];

        for (size_t i = 0; i < dequeSize; ++i) {
            newBuffer[i] = buffer[(head + i) % bufferSize];
        }

        delete[] buffer;
        buffer = newBuffer;
        bufferSize = newBufferSize;
        head = 0;
        tail = dequeSize;
    }

public:
    Deque() : buffer(nullptr), head(0), tail(0), bufferSize(0), dequeSize(0) {}

    ~Deque() {
        delete[] buffer;
    }

    Deque(const Deque& other) : head(other.head), tail(other.tail), bufferSize(other.bufferSize), dequeSize(other.dequeSize) {
        buffer = new T[bufferSize];
        for (size_t i = 0; i < dequeSize; ++i) {
            buffer[i] = other.buffer[(other.head + i) % other.bufferSize];
        }
    }

    Deque& operator=(const Deque& other) {
        if (this != &other) {
            delete[] buffer;
            head = other.head;
            tail = other.tail;
            bufferSize = other.bufferSize;
            dequeSize = other.dequeSize;

            buffer = new T[bufferSize];
            for (size_t i = 0; i < dequeSize; ++i) {
                buffer[i] = other.buffer[(other.head + i) % other.bufferSize];
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (dequeSize == bufferSize) {
            resize();
        }
        buffer[tail] = value;
        tail = (tail + 1) % bufferSize;
        dequeSize++;
    }

    void push_front(const T& value) {
        if (dequeSize == bufferSize) {
            resize();
        }
        head = (head - 1 + bufferSize) % bufferSize;
        buffer[head] = value;
        dequeSize++;
    }

    T pop_back() {
        if (dequeSize == 0) {
            throw std::out_of_range("Oops! Can't take from the back. It's empty!");
        }
        tail = (tail - 1 + bufferSize) % bufferSize;
        T value = buffer[tail];
        dequeSize--;
        return value;
    }

    T pop_front() {
        if (dequeSize == 0) {
            throw std::out_of_range("Oops! Can't take from the front. It's empty!");
        }
        T value = buffer[head];
        head = (head + 1) % bufferSize;
        dequeSize--;
        return value;
    }

    size_t size() const {
        return dequeSize;
    }

    size_t capacity() const {
        return bufferSize;
    }
};

int main() {
    Deque<int> myDeque;
    myDeque.push_back(1);
    myDeque.push_back(2);
    myDeque.push_front(3);
    myDeque.push_front(4);

    std::cout << "items " << myDeque.size() << std::endl;
    std::cout << "Capacity " << myDeque.capacity() << std::endl;

    std::cout << "first " << myDeque.pop_front() << std::endl;
    std::cout << "last " << myDeque.pop_back() << std::endl;

    return 0;
}
