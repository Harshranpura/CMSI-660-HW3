#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class ExpandableStack {
public:
    ExpandableStack() : capacity(1), size(0), stack(std::make_unique<std::string[]>(capacity)) {}

    void push(const std::string& item) {
        if (size == capacity) {
            expandCapacity();
        }
        stack[size++] = item;
    }

    std::string pop() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot pop from an empty stack.");
        }
        return std::move(stack[--size]);
    }

    const std::string& peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Cannot peek an empty stack.");
        }
        return stack[size - 1];
    }

    bool isEmpty() const { return size == 0; }

    std::size_t getSize() const { return size; }

private:
    std::size_t capacity;
    std::size_t size;
    std::unique_ptr<std::string[]> stack;

    void expandCapacity() {
        std::size_t newCapacity = capacity * 2;
        std::unique_ptr<std::string[]> newStack = std::make_unique<std::string[]>(newCapacity);

        for (std::size_t i = 0; i < size; ++i) {
            newStack[i] = std::move(stack[i]);
        }

        stack = std::move(newStack);
        capacity = newCapacity;
    }
};

int main() {
    try {
        ExpandableStack stack;
        stack.push("Hello");
        stack.push("Professor");
        std::cout << "Top of stack: " << stack.peek() << std::endl;
        std::cout << "Popped: " << stack.pop() << std::endl;
        std::cout << "Popped: " << stack.pop() << std::endl;

        std::cout << "Popped: " << stack.pop() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
