#include <iostream>
#include "Containers/LinkedList.hpp"
#include "Containers/DoublyLinkedList.hpp"

int main() 
{
    LinkedList<int> list;
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Insert(15,1);

    LinkedList<int>::ListIterator it = list.Iterator();
    while (it.hasNext())
    {
        std::cout << it.Next() << std::endl;
    }

    std::cout << "Get: " << list.Get(1) << "\n";
    std::cout << "Index of 11 (dne): " << list.IndexOf(11) << "\n";
    return 0;
}
