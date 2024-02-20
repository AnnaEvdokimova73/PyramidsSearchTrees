#include <iostream>

class Pyramid {
public:
    Pyramid(int size, int* arr) : size_(size), data_(new int[size])
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = arr[i];
        }
    }

    void printPyramid(int index)
    {
        std::cout << getLevel(index) << " ";
        std::cout << getSide(index);
        index != 0 ? std::cout << "(" << getParent(index) << ")" : std::cout << "";
        std::cout << " " << getValue(index) << std::endl;
    }

    ~Pyramid() {
        delete[] data_;
    }

private:
    int getValue(int index)
    {
        return data_[index];
    }

    int getLevel(int index)
    {
        if (index == 0)
        {
            return 0;
        }

        //int levPar = getLevel(getParentIndex(index));
        return getLevel(getParentIndex(index)) + 1;
    }

    int getParent(int index)
    {
        if (index == 0)
        {
            return 0;
        }
        if (index % 2 == 0)
        {
            // right child - index is even 
            return data_[(index - 2)/2];
        }
        else
        {
            // left child
            return data_[(index - 1)/2];
        }
    }

    int getParentIndex(int index)
    {
        if (index % 2 == 0)
        {
            // right child - index is even 
            return (index - 2) / 2;
        }
        else
        {
            // left child
            return (index - 1) / 2;
        }
    }

    std::string getSide(int index)
    {
        if (index == 0)
        {
            return "root";
        }
        if (index % 2 == 0)
        {
            // right child - index is even 
            return "right";
        }
        else
        {
            // left child
            return "left";
        }
    }

private:
    int size_;
    int* data_;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int arr[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Исходный массив: ";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Пирамида:\n";
    Pyramid pyr(size, arr);

    for (size_t i = 0; i < size; ++i)
    {
        pyr.printPyramid(i);
    }
}
