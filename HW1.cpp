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

    std::cout << std::endl;

    DoublyLinkedList<int> DList;
    DList.Add(10);
    DList.Add(20);
    DList.Add(30);
    DList.Insert(15,1);

    std::cout << "Doubly List size: " << DList.Size() << std::endl;

    // Using iterator to traverse the list
    DListIterator<int> iterator = DList.Iterator();
    while (iterator.HasNext()) {
        std::cout << iterator.Next() << std::endl;
    }

    std::cout << "Get: " <<DList.Get(1) << "\n";
    std::cout << "Index of 11 (dne): " << DList.IndexOf(11) << "\n";

    return 0;
}
