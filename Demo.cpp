// tomergal40@gmail.com
#include "MyContainer.hpp"
#include <iostream>
#include <string>

using namespace mycontainers;

int main() {
    std::cout << "=== Demo for Assignment 4 - MyContainer ===" << std::endl;
    
    // Create container with assignment example: [7,15,6,1,2]
    MyContainer<int> container;
    
    std::cout << "\nAdding elements: 7, 15, 6, 1, 2" << std::endl;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    std::cout << "Original container: " << container << std::endl;
    std::cout << "Container size: " << container.size() << std::endl;
    
    std::cout << "\n=== Testing All Iterator Types ===" << std::endl;
    
    // Order Iterator - original order: 7,15,6,1,2
    std::cout << "Order iterator (original): ";
    auto orderIter = container.order();
    for (auto it = orderIter.begin(); it != orderIter.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << " -> Expected: 7,15,6,1,2" << std::endl;
    
    // AscendingOrder Iterator - ascending order: 1,2,6,7,15
    std::cout << "AscendingOrder iterator: ";
    auto ascIter = container.ascending();
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << " -> Expected: 1,2,6,7,15" << std::endl;
    
    // DescendingOrder Iterator - descending order: 15,7,6,2,1
    std::cout << "DescendingOrder iterator: ";
    auto descIter = container.descending();
    for (auto it = descIter.begin(); it != descIter.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << " -> Expected: 15,7,6,2,1" << std::endl;
    
    // SideCrossOrder Iterator - 1,15,2,7,6
    std::cout << "SideCrossOrder iterator: ";
    auto sideIter = container.sideCross();
    for (auto it = sideIter.begin(); it != sideIter.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << " -> Expected: 1,15,2,7,6" << std::endl;
    
    // ReverseOrder Iterator - reverse: 2,1,6,15,7
    std::cout << "ReverseOrder iterator: ";
    auto revIter = container.reverse();
    for (auto it = revIter.begin(); it != revIter.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << " -> Expected: 2,1,6,15,7" << std::endl;
    
    // MiddleOutOrder Iterator - middle out: 6,15,1,7,2
    std::cout << "MiddleOutOrder iterator: ";
    auto middleIter = container.middleOut();
    for (auto it = middleIter.begin(); it != middleIter.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << " -> Expected: 6,15,1,7,2" << std::endl;
    
    std::cout << "\n=== Testing Container Operations ===" << std::endl;
    
    // Test remove
    std::cout << "Before removing 15: " << container << std::endl;
    container.remove(15);
    std::cout << "After removing 15: " << container << std::endl;
    std::cout << "New size: " << container.size() << std::endl;
    
    // Test duplicate removal
    std::cout << "\n=== Testing Duplicate Removal ===" << std::endl;
    MyContainer<int> dupContainer;
    dupContainer.add(5);
    dupContainer.add(3);
    dupContainer.add(5);
    dupContainer.add(1);
    dupContainer.add(5);
    
    std::cout << "Container with duplicates: " << dupContainer << std::endl;
    dupContainer.remove(5);  // Should remove all instances of 5
    std::cout << "After removing all 5s: " << dupContainer << std::endl;
    
    // Test with strings
    std::cout << "\n=== Testing with Strings ===" << std::endl;
    MyContainer<std::string> stringContainer;
    stringContainer.add("hello");
    stringContainer.add("world");
    stringContainer.add("cpp");
    stringContainer.add("assignment");
    
    std::cout << "String container: " << stringContainer << std::endl;
    std::cout << "Ascending order: ";
    auto strAscIter = stringContainer.ascending();
    for (auto it = strAscIter.begin(); it != strAscIter.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test with doubles
    std::cout << "\n=== Testing with Doubles ===" << std::endl;
    MyContainer<double> doubleContainer;
    doubleContainer.add(3.14);
    doubleContainer.add(2.71);
    doubleContainer.add(1.41);
    
    std::cout << "Double container: " << doubleContainer << std::endl;
    std::cout << "Descending order: ";
    auto dblDescIter = doubleContainer.descending();
    for (auto it = dblDescIter.begin(); it != dblDescIter.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test error handling
    std::cout << "\n=== Testing Error Handling ===" << std::endl;
    try {
        container.remove(999);  // Element doesn't exist
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Successfully caught exception: " << e.what() << std::endl;
    }
    
    // Test empty container
    std::cout << "\n=== Testing Empty Container ===" << std::endl;
    MyContainer<int> emptyContainer;
    std::cout << "Empty container: " << emptyContainer << std::endl;
    std::cout << "Empty container size: " << emptyContainer.size() << std::endl;
    std::cout << "Is empty: " << (emptyContainer.empty() ? "true" : "false") << std::endl;
    
    auto emptyAscIter = emptyContainer.ascending();
    std::cout << "Empty ascending iterator works: ";
    for (auto it = emptyAscIter.begin(); it != emptyAscIter.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(should print nothing)" << std::endl;
    
    std::cout << "\n=== Demo completed successfully! ===" << std::endl;
    return 0;
}