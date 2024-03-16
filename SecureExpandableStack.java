public class SecureExpandableStack {
    private String[] stackArray;
    private int size;
    private int capacity;

    // Constructor with initial capacity
    public SecureExpandableStack(int initialCapacity) {
        if (initialCapacity <= 0) {
            throw new IllegalArgumentException("Initial capacity must be greater than 0.");
        }
        this.capacity = initialCapacity;
        this.stackArray = new String[capacity];
        this.size = 0;
    }

    // Push method to add a new string to the stack
    public void push(String item) {
        if (item == null) {
            throw new NullPointerException("Cannot add null item to the stack");
        }
        if (size == capacity) {
            expandCapacity();
        }
        stackArray[size++] = item;
    }

    // Pop method to remove and return the top string from the stack
    public String pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Cannot pop from an empty stack.");
        }
        String item = stackArray[--size];
        stackArray[size] = null; 
        return item;
    }

    // Peek method to return the top string without removing it
    public String peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Cannot peek an empty stack.");
        }
        return stackArray[size - 1];
    }

    // Method to check if the stack is empty
    public boolean isEmpty() {
        return size == 0;
    }

    // Method to expand the capacity of the stack array
    private void expandCapacity() {
        capacity *= 2;
        String[] newArray = new String[capacity];
        System.arraycopy(stackArray, 0, newArray, 0, stackArray.length);
        stackArray = newArray;
    }

    public static void main(String[] args) {
        SecureExpandableStack stack = new SecureExpandableStack(2);
        System.out.println("Pushing \"Hello\" onto the stack.");
        stack.push("Hello");
        System.out.println("Pushing \"World\" onto the stack.");
        stack.push("World");
        System.out.println("Peeking at the top item: " + stack.peek());
        System.out.println("Pushing \"Java\" onto the stack.");
        stack.push("Java");
        System.out.println("Popping from the stack: " + stack.pop());
        System.out.println("Checking if the stack is empty: " + stack.isEmpty());
        System.out.println("Popping all remaining items...");
        while (!stack.isEmpty()) {
            System.out.println("Popped: " + stack.pop());
        }
        try {
            System.out.println("Attempting to pop from an empty stack...");
            stack.pop(); // This should trigger an exception.
        } catch (IllegalStateException e) {
            System.out.println(e.getMessage());
        }
    }
     
}
    
        
    
