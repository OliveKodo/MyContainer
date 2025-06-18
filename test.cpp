// tomergal40@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <vector>
#include <string>

using namespace mycontainers;

TEST_CASE("MyContainer Basic Operations") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        CHECK(container.size() == 0);
        CHECK(container.empty() == true);
    }
    
    SUBCASE("Add elements") {
        container.add(5);
        container.add(3);
        container.add(8);
        
        CHECK(container.size() == 3);
        CHECK(container.empty() == false);
    }
    
    SUBCASE("Remove existing element") {
        container.add(5);
        container.add(3);
        container.add(8);
        
        container.remove(3);
        CHECK(container.size() == 2);
    }
    
    SUBCASE("Remove non-existing element throws exception") {
        container.add(5);
        container.add(3);
        
        CHECK_THROWS_AS(container.remove(10), std::invalid_argument);
    }
    
    SUBCASE("Remove all duplicates") {
        container.add(5);
        container.add(3);
        container.add(5);
        container.add(8);
        container.add(5);
        
        CHECK(container.size() == 5);
        container.remove(5);  // Should remove all instances of 5
        CHECK(container.size() == 2);
    }
}

TEST_CASE("Iterator Tests - Assignment Example [7,15,6,1,2]") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    SUBCASE("Order Iterator - Original order: 7,15,6,1,2") {
        std::vector<int> expected = {7, 15, 6, 1, 2};
        std::vector<int> actual;
        
        auto iter = container.order();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("AscendingOrder Iterator - Expected: 1,2,6,7,15") {
        std::vector<int> expected = {1, 2, 6, 7, 15};
        std::vector<int> actual;
        
        auto iter = container.ascending();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("DescendingOrder Iterator - Expected: 15,7,6,2,1") {
        std::vector<int> expected = {15, 7, 6, 2, 1};
        std::vector<int> actual;
        
        auto iter = container.descending();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("SideCrossOrder Iterator - Expected: 1,15,2,7,6") {
        std::vector<int> expected = {1, 15, 2, 7, 6};
        std::vector<int> actual;
        
        auto iter = container.sideCross();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("ReverseOrder Iterator - Expected: 2,1,6,15,7") {
        std::vector<int> expected = {2, 1, 6, 15, 7};
        std::vector<int> actual;
        
        auto iter = container.reverse();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("MiddleOutOrder Iterator - Expected: 6,15,1,7,2") {
        std::vector<int> expected = {6, 15, 1, 7, 2};
        std::vector<int> actual;
        
        auto iter = container.middleOut();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
}

TEST_CASE("String Container Tests") {
    MyContainer<std::string> container;
    container.add("hello");
    container.add("world");
    container.add("cpp");
    container.add("assignment");
    
    SUBCASE("Basic string operations") {
        CHECK(container.size() == 4);
        CHECK_FALSE(container.empty());
    }
    
    SUBCASE("String ascending order") {
        std::vector<std::string> expected = {"assignment", "cpp", "hello", "world"};
        std::vector<std::string> actual;
        
        auto iter = container.ascending();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("Remove string element") {
        container.remove("cpp");
        CHECK(container.size() == 3);
        
        CHECK_THROWS_AS(container.remove("nonexistent"), std::invalid_argument);
    }
}

TEST_CASE("Double Container Tests") {
    MyContainer<double> container;
    container.add(3.14);
    container.add(2.71);
    container.add(1.41);
    container.add(0.57);
    
    SUBCASE("Double ascending order") {
        std::vector<double> expected = {0.57, 1.41, 2.71, 3.14};
        std::vector<double> actual;
        
        auto iter = container.ascending();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
    
    SUBCASE("Double descending order") {
        std::vector<double> expected = {3.14, 2.71, 1.41, 0.57};
        std::vector<double> actual;
        
        auto iter = container.descending();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
}

TEST_CASE("Edge Cases") {
    SUBCASE("Empty container iterators") {
        MyContainer<int> container;
        
        // All iterators should work with empty containers
        auto ascIter = container.ascending();
        CHECK(ascIter.begin() == ascIter.end());
        
        auto descIter = container.descending();
        CHECK(descIter.begin() == descIter.end());
        
        auto orderIter = container.order();
        CHECK(orderIter.begin() == orderIter.end());
        
        auto revIter = container.reverse();
        CHECK(revIter.begin() == revIter.end());
        
        auto sideIter = container.sideCross();
        CHECK(sideIter.begin() == sideIter.end());
        
        auto middleIter = container.middleOut();
        CHECK(middleIter.begin() == middleIter.end());
    }
    
    SUBCASE("Single element container") {
        MyContainer<int> container;
        container.add(42);
        
        std::vector<int> expected = {42};
        std::vector<int> actual;
        
        // Test all iterators with single element
        auto ascIter = container.ascending();
        for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
        
        actual.clear();
        auto middleIter = container.middleOut();
        for (auto it = middleIter.begin(); it != middleIter.end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    
    SUBCASE("Two elements container") {
        MyContainer<int> container;
        container.add(10);
        container.add(5);
        
        // Test MiddleOut with even number of elements
        std::vector<int> actual;
        auto middleIter = container.middleOut();
        for (auto it = middleIter.begin(); it != middleIter.end(); ++it) {
            actual.push_back(*it);
        }
        
        // With 2 elements, middle index is 1, so should start with second element
        CHECK(actual.size() == 2);
        CHECK(actual[0] == 5);  // middle element (index 1)
        CHECK(actual[1] == 10); // left element (index 0)
    }
}

TEST_CASE("Iterator Out of Range Exception") {
    MyContainer<int> container;
    container.add(1);
    container.add(2);
    
    SUBCASE("Dereferencing end iterator should throw") {
        auto iter = container.ascending();
        auto endIter = iter.end();
        
        CHECK_THROWS_AS(*endIter, std::out_of_range);
    }
}

TEST_CASE("Container with Duplicates") {
    MyContainer<int> container;
    container.add(5);
    container.add(3);
    container.add(5);
    container.add(1);
    container.add(5);
    container.add(3);
    
    SUBCASE("Remove all instances of duplicate") {
        CHECK(container.size() == 6);
        
        container.remove(5);  // Should remove all three 5s
        CHECK(container.size() == 3);
        
        container.remove(3);  // Should remove both 3s
        CHECK(container.size() == 1);
    }
    
    SUBCASE("Iterators work correctly with duplicates") {
        std::vector<int> expected = {1, 3, 3, 5, 5, 5};
        std::vector<int> actual;
        
        auto iter = container.ascending();
        for (auto it = iter.begin(); it != iter.end(); ++it) {
            actual.push_back(*it);
        }
        
        CHECK(actual == expected);
    }
}

TEST_CASE("Assignment Example Validation") {
    SUBCASE("Exact assignment example test") {
        MyContainer<int> container;
        
        // Add elements exactly as in assignment: [7,15,6,1,2]
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        // Test each iterator matches assignment requirements exactly
        
        // Order: 7,15,6,1,2
        std::vector<int> orderResult;
        auto orderIter = container.order();
        for (auto it = orderIter.begin(); it != orderIter.end(); ++it) {
            orderResult.push_back(*it);
        }
        CHECK(orderResult == std::vector<int>({7, 15, 6, 1, 2}));
        
        // AscendingOrder: 1,2,6,7,15
        std::vector<int> ascResult;
        auto ascIter = container.ascending();
        for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
            ascResult.push_back(*it);
        }
        CHECK(ascResult == std::vector<int>({1, 2, 6, 7, 15}));
        
        // DescendingOrder: 15,7,6,2,1
        std::vector<int> descResult;
        auto descIter = container.descending();
        for (auto it = descIter.begin(); it != descIter.end(); ++it) {
            descResult.push_back(*it);
        }
        CHECK(descResult == std::vector<int>({15, 7, 6, 2, 1}));
        
        // SideCrossOrder: 1,15,2,7,6
        std::vector<int> sideResult;
        auto sideIter = container.sideCross();
        for (auto it = sideIter.begin(); it != sideIter.end(); ++it) {
            sideResult.push_back(*it);
        }
        CHECK(sideResult == std::vector<int>({1, 15, 2, 7, 6}));
        
        // ReverseOrder: 2,1,6,15,7
        std::vector<int> revResult;
        auto revIter = container.reverse();
        for (auto it = revIter.begin(); it != revIter.end(); ++it) {
            revResult.push_back(*it);
        }
        CHECK(revResult == std::vector<int>({2, 1, 6, 15, 7}));
        
        // MiddleOutOrder: 6,15,1,7,2
        std::vector<int> middleResult;
        auto middleIter = container.middleOut();
        for (auto it = middleIter.begin(); it != middleIter.end(); ++it) {
            middleResult.push_back(*it);
        }
        CHECK(middleResult == std::vector<int>({6, 15, 1, 7, 2}));
    }
}