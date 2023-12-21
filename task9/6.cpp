#include <iostream>
#include <algorithm>

const int MAX_SIZE = 100;

class Set {
private:
    int elements[MAX_SIZE];
    int size;

public:
    Set() {
        size = 0;
    }

    void addElement(int element) {
        if (size < MAX_SIZE) {
            elements[size] = element;
            size++;
        }
    }

    void removeElement(int element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                for (int j = i; j < size - 1; j++) {
                    elements[j] = elements[j + 1];
                }
                size--;
                break;
            }
        }
    }

    Set intersection(const Set& otherSet) {
        Set result;
        std::copy_if(elements, elements + size, std::back_inserter(result.elements), [&otherSet](int element) {
            return std::find(otherSet.elements, otherSet.elements + otherSet.size, element) != otherSet.elements + otherSet.size;
        });
        result.size = std::distance(result.elements, std::find(result.elements, result.elements + MAX_SIZE, 0));
        return result;
    }

    Set operator-(const Set& otherSet) {
        Set result;
        std::copy_if(elements, elements + size, std::back_inserter(result.elements), [&otherSet](int element) {
            return std::find(otherSet.elements, otherSet.elements + otherSet.size, element) == otherSet.elements + otherSet.size;
        });
        result.size = std::distance(result.elements, std::find(result.elements, result.elements + MAX_SIZE, 0));
        return result;
    }

    friend void printSet(const Set& set);
};

void printSet(const Set& set) {
    for (int i = 0; i < set.size; i++) {
        std::cout << set.elements[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    Set set1;
    set1.addElement(1);
    set1.addElement(2);
    set1.addElement(3);

    Set set2;
    set2.addElement(2);
    set2.addElement(3);
    set2.addElement(4);

    std::cout << "Set 1: ";
    printSet(set1);

    std::cout << "Set 2: ";
    printSet(set2);

    std::cout << "Intersection: ";
    Set intersection = set1.intersection(set2);
    printSet(intersection);

    std::cout << "Difference: ";
    Set difference = set1 - set2;
    printSet(difference);

    return 0;
}