
# Singleton Template Class

This repository contains a template-based Singleton class implemented in C++. The purpose of the Singleton pattern is to ensure that only one instance of a class exists throughout the application's lifecycle.

## Features

- Ensures a single instance of the object is created and managed.
- Thread-safe with `static` initialization.
- Prevents copying or moving of the Singleton instance.
- Generic implementation that can be used with any object type.

## Singleton Template Class

```cpp
#include <utility>
#include <memory>

template <typename T>
class Singleton
{
private:
    std::unique_ptr<T> m_instance = nullptr;

    // Deleted constructors and assignment operators to prevent copying
    Singleton(Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;
    Singleton &operator=(Singleton &) = delete;

    // Private constructor for Singleton initialization
    Singleton(T &&t)
        : m_instance(std::make_unique<T>(std::move(t))) {}

public:
    ~Singleton() {}

    // Static function to initialize and get the Singleton instance
    inline static Singleton &init(T &&obj)
    {
        static Singleton<T> Singleton{std::move(obj)};
        return Singleton;
    }

    // Function to get a pointer to the unique instance
    T *getInstance()
    {
        return m_instance.get();
    }
};
```

### Key Points
- **Initialization:** The `init()` method initializes the Singleton with the object of type `T`. It accepts an rvalue reference to ensure the passed object is moved.
- **Access:** The `getInstance()` method returns a pointer to the instance of `T`.
- **Protection:** The copy constructor, move constructor, and assignment operators are deleted to prevent accidental creation of multiple instances.

## Usage Example

Here is a demonstration of how to use this `Singleton` template class with a custom class `MyClass`.

### Custom Class Example

```cpp
#include <iostream>
#include "Singleton.h" // Include your Singleton template implementation

class MyClass
{
public:
    MyClass(int value) : m_value(value) {}

    void display()
    {
        std::cout << "Value: " << m_value << std::endl;
    }

private:
    int m_value;
};

int main()
{
    // Initialize Singleton with MyClass object
    Singleton<MyClass>::init(MyClass(100)).getInstance()->display();

    // Fetch the same Singleton instance and display the value
    Singleton<MyClass>::init(MyClass(200)).getInstance()->display();

    return 0;
}
```

### Expected Output:

```
Value: 100
Value: 100
```

### Explanation:
1. The `Singleton<MyClass>::init(MyClass(100))` creates and initializes a single instance of `MyClass` with the value `100`.
2. Any subsequent calls to `Singleton<MyClass>::init(MyClass(200))` will not create a new instance, but instead, return the already created one, thus still displaying the value `100`.

## How to Compile and Run

To compile and run the example code:

```bash
g++ -std=c++11 -o singleton_demo main.cpp
./singleton_demo
```

Make sure to include the `Singleton` implementation in your project to compile the above example.

## License

This project is licensed under the MIT License.
