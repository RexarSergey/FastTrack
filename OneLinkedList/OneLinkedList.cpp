#include <iostream>
#include <format>
#include "LinkedList.h"


int main()
{
    LinkedList<int> linkedList{};
    
    linkedList.add(1);
    linkedList.add(2);
    linkedList.add(3);
    linkedList.add(4);
    linkedList.print();
    std::cout << '\n';

    linkedList.add_forward(5);
    linkedList.add_forward(6);
    linkedList.add(3, 7);
    linkedList.add(linkedList.size() + 1, 8);
    linkedList.print();
    std::cout << '\n';

    linkedList.remove(8);
    linkedList.remove(2);
    linkedList.remove_first();
    linkedList.remove_last();
    linkedList.print();
    std::cout << '\n';

    int pos = linkedList.contains(3);
    std::cout << (pos != -1 ? std::format("3 contains on position {}\n", pos) : "3 not founded\n");
    pos = linkedList.contains(33);
    std::cout << (pos != -1 ? std::format("33 contains on position {}\n", pos) : "33 not founded\n");
    std::cout << '\n';

    linkedList.clear();
    linkedList.print();
    std::cout << '\n';

    linkedList.add(3, 7);
    linkedList.add(0, 7);
    linkedList.print();
    std::cout << '\n';
}