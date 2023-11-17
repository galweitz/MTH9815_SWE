#include <iostream>
#include "Containers/LinkedList.hpp"
#include "Containers/DoublyLinkedList.hpp"
#include "Containers/Hashtable.hpp"

/*
 * Contributions of ChatGPT:
 * 1. ChatGPT outlined for us the basic structure and components of the hash table, including the Hashtable class and its dependencies, Hasher and EqualityPredicate.
 * 2. ChatGPT provided the initial templates for the Hashtable, Hasher, and EqualityPredicate classes, establishing a foundation for the implementation.
 * 3. ChatGPT suggested simple yet effective strategies for hashing and comparing keys, which were particularly useful for handling integer keys.
 
 * Notes:
 * - The implementation was further refined and tested beyond the initial guidance from ChatGPT.
 * - While ChatGPT was instrumental in providing a starting point and basic logic, additional development work was performed to ensure robustness and functionality of the code.
 * - This collaboration showcases the potential of AI-assisted coding, especially in conceptualizing data structures and writing initial code drafts.
 */


int main() 
{
    std::cout << "LinkedList\n";
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

    std::cout << "\n";

    std::cout << "DoublyLinkedList\n";
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

    std::cout << "\n";

    std::cout << "Hashtable\n";
    Hashtable<int, std::string> table(10, std::make_unique<IntHasher>(), std::make_unique<IntEqualityPredicate>());

    table.insert(1, "One");
    table.insert(2, "Two");
    table.insert(3, "Three");

    std::string value;
    if (table.find(2, value))
        std::cout << "Value for key 2: " << value << std::endl;
    else 
        std::cout << "Key 2 not found." << std::endl;

    if (table.find(4, value))
        std::cout << "Value for key 4: " << value << std::endl;
    else
        std::cout << "Key 4 not found." << std::endl;

    return 0;
}
