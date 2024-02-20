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

    void printPyramidElement(int index)
    {
        std::cout << getLevel(index) << " ";
        std::cout << getSide(index);
        index != 0 ? std::cout << "(" << getParent(index) << ")" : std::cout << "";
        std::cout << " " << getValue(index);
    }

    int getLeftChildInd(int indexParent)
    {
        int index = 2 * indexParent + 1;
        if (index >= size_)
        {
            throw std::invalid_argument("Ошибка! Отсутствует левый потомок");
        }
        return index;
    }

    int getRightChildInd(int indexParent)
    {
        int index = 2 * indexParent + 2;
        if (index >= size_)
        {
            throw std::invalid_argument("Ошибка! Отсутствует правый потомок");
        }
        return index;
    }

    int getParentIndex(int index)
    {
        if (index == 0)
        {
            throw std::invalid_argument("Ошибка! Отсутствует родитель");
        }
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
            return data_[(index - 2) / 2];
        }
        else
        {
            // left child
            return data_[(index - 1) / 2];
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
    int arr[] = { 1, 3, 6, 5, 9, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Исходный массив: ";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    Pyramid pyr(size, arr);
    std::cout << "Пирамида:\n";
    for (size_t i = 0; i < size; ++i)
    {
        pyr.printPyramidElement(i);
        std::cout << std::endl;
    }

    std::string command = "";
    int index = 0;

    do
    {
        std::cout << "Вы находитесь здесь: ";
        pyr.printPyramidElement(index);
        std::cout << std::endl;

        std::cout << "Введите команду: ";
        std::cin >> command;
        if (command == "right")
        {
            try
            {
                index = pyr.getRightChildInd(index);
                std::cout << "Ок\n";
            } 
            catch (const std::invalid_argument& except)
            {
                std::cout << except.what() << std::endl;
            }
        }
        else if (command == "left")
        {
            try
            {
                index = pyr.getLeftChildInd(index);
                std::cout << "Ок\n";
            }
            catch (const std::invalid_argument& except)
            {
                std::cout << except.what() << std::endl;
            }
        }
        else if (command == "up")
        {
            try
            {
                index = pyr.getParentIndex(index);
                std::cout << "Ок\n";
            }
            catch (const std::invalid_argument& except)
            {
                std::cout << except.what() << std::endl;
            }
        }
    } while (command != "exit");
}
