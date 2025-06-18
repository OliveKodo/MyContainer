// tomergal40@gmail.com
#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <functional>

namespace mycontainers {

template<typename T = int>
class MyContainer {
private:
    std::vector<T> data;

public:
    // Constructors and destructor
    MyContainer() = default;
    MyContainer(const MyContainer& other) = default;
    MyContainer& operator=(const MyContainer& other) = default;
    ~MyContainer() = default;

    // Basic operations
    void add(const T& element) {
        data.push_back(element);
    }

    void remove(const T& element) {
        auto it = std::find(data.begin(), data.end(), element);
        if (it == data.end()) {
            throw std::invalid_argument("Element not found in container");
        }
        // Remove ALL instances of the element
        data.erase(std::remove(data.begin(), data.end(), element), data.end());
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
        os << "[";
        for (size_t i = 0; i < container.data.size(); ++i) {
            if (i > 0) os << ", ";
            os << container.data[i];
        }
        os << "]";
        return os;
    }

    // Iterator classes
    
    // AscendingOrder Iterator - sorts in ascending order
    class AscendingOrder {
    private:
        std::vector<T> sortedData;
        size_t currentIndex;
        
    public:
        AscendingOrder(const std::vector<T>& data) : sortedData(data), currentIndex(0) {
            std::sort(sortedData.begin(), sortedData.end());
        }

        AscendingOrder& operator++() {
            if (currentIndex < sortedData.size()) {
                currentIndex++;
            }
            return *this;
        }

        const T& operator*() const {
            if (currentIndex >= sortedData.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return sortedData[currentIndex];
        }

        bool operator!=(const AscendingOrder& other) const {
            return currentIndex != other.currentIndex;
        }

        bool operator==(const AscendingOrder& other) const {
            return currentIndex == other.currentIndex;
        }

        AscendingOrder begin() const {
            AscendingOrder iter(*this);
            iter.currentIndex = 0;
            return iter;
        }

        AscendingOrder end() const {
            AscendingOrder iter(*this);
            iter.currentIndex = sortedData.size();
            return iter;
        }
    };

    // DescendingOrder Iterator - sorts in descending order
    class DescendingOrder {
    private:
        std::vector<T> sortedData;
        size_t currentIndex;
        
    public:
        DescendingOrder(const std::vector<T>& data) : sortedData(data), currentIndex(0) {
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }

        DescendingOrder& operator++() {
            if (currentIndex < sortedData.size()) {
                currentIndex++;
            }
            return *this;
        }

        const T& operator*() const {
            if (currentIndex >= sortedData.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return sortedData[currentIndex];
        }

        bool operator!=(const DescendingOrder& other) const {
            return currentIndex != other.currentIndex;
        }

        bool operator==(const DescendingOrder& other) const {
            return currentIndex == other.currentIndex;
        }

        DescendingOrder begin() const {
            DescendingOrder iter(*this);
            iter.currentIndex = 0;
            return iter;
        }

        DescendingOrder end() const {
            DescendingOrder iter(*this);
            iter.currentIndex = sortedData.size();
            return iter;
        }
    };

    // SideCrossOrder Iterator - alternates between smallest and largest
    class SideCrossOrder {
    private:
        std::vector<T> sortedData;
        size_t currentIndex;
        
    public:
        SideCrossOrder(const std::vector<T>& data) : sortedData(), currentIndex(0) {
            if (!data.empty()) {
                std::vector<T> temp = data;
                std::sort(temp.begin(), temp.end());
                
                sortedData.clear();
                size_t left = 0, right = temp.size() - 1;
                bool takeLeft = true;
                
                while (left <= right) {
                    if (takeLeft) {
                        sortedData.push_back(temp[left]);
                        left++;
                    } else {
                        sortedData.push_back(temp[right]);
                        if (right > 0) right--;
                        else break;
                    }
                    takeLeft = !takeLeft;
                    
                    // Break if left exceeds right
                    if (left > right) break;
                }
            }
        }

        SideCrossOrder& operator++() {
            if (currentIndex < sortedData.size()) {
                currentIndex++;
            }
            return *this;
        }

        const T& operator*() const {
            if (currentIndex >= sortedData.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return sortedData[currentIndex];
        }

        bool operator!=(const SideCrossOrder& other) const {
            return currentIndex != other.currentIndex;
        }

        bool operator==(const SideCrossOrder& other) const {
            return currentIndex == other.currentIndex;
        }

        SideCrossOrder begin() const {
            SideCrossOrder iter(*this);
            iter.currentIndex = 0;
            return iter;
        }

        SideCrossOrder end() const {
            SideCrossOrder iter(*this);
            iter.currentIndex = sortedData.size();
            return iter;
        }
    };

    // ReverseOrder Iterator - reverses the original order
    class ReverseOrder {
    private:
        std::vector<T> reversedData;
        size_t currentIndex;
        
    public:
        ReverseOrder(const std::vector<T>& data) : reversedData(data), currentIndex(0) {
            std::reverse(reversedData.begin(), reversedData.end());
        }

        ReverseOrder& operator++() {
            if (currentIndex < reversedData.size()) {
                currentIndex++;
            }
            return *this;
        }

        const T& operator*() const {
            if (currentIndex >= reversedData.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return reversedData[currentIndex];
        }

        bool operator!=(const ReverseOrder& other) const {
            return currentIndex != other.currentIndex;
        }

        bool operator==(const ReverseOrder& other) const {
            return currentIndex == other.currentIndex;
        }

        ReverseOrder begin() const {
            ReverseOrder iter(*this);
            iter.currentIndex = 0;
            return iter;
        }

        ReverseOrder end() const {
            ReverseOrder iter(*this);
            iter.currentIndex = reversedData.size();
            return iter;
        }
    };

    // Order Iterator - maintains original insertion order
    class Order {
    private:
        std::vector<T> originalData;
        size_t currentIndex;
        
    public:
        Order(const std::vector<T>& data) : originalData(data), currentIndex(0) {
            // Keep original order - no changes needed
        }

        Order& operator++() {
            if (currentIndex < originalData.size()) {
                currentIndex++;
            }
            return *this;
        }

        const T& operator*() const {
            if (currentIndex >= originalData.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return originalData[currentIndex];
        }

        bool operator!=(const Order& other) const {
            return currentIndex != other.currentIndex;
        }

        bool operator==(const Order& other) const {
            return currentIndex == other.currentIndex;
        }

        Order begin() const {
            Order iter(*this);
            iter.currentIndex = 0;
            return iter;
        }

        Order end() const {
            Order iter(*this);
            iter.currentIndex = originalData.size();
            return iter;
        }
    };

    // MiddleOutOrder Iterator - starts from middle, then alternates left-right
    class MiddleOutOrder {
    private:
        std::vector<T> middleOutData;
        size_t currentIndex;
        
    public:
        MiddleOutOrder(const std::vector<T>& data) : middleOutData(), currentIndex(0) {
            if (!data.empty()) {
                middleOutData.clear();
                
                size_t middle = data.size() / 2;
                middleOutData.push_back(data[middle]);
                
                // For [7,15,6,1,2] (indices 0,1,2,3,4): 
                // middle=2, so start with data[2]=6
                // Expected pattern: 6,15,1,7,2
                // This means: middle, left, right, left, right
                
                int left = static_cast<int>(middle) - 1;  // Start at middle-1
                size_t right = middle + 1;                // Start at middle+1
                bool takeLeft = true;  // Start with left after middle
                
                while (middleOutData.size() < data.size()) {
                    if (takeLeft && left >= 0) {
                        middleOutData.push_back(data[left]);
                        left--;
                        takeLeft = false;
                    } else if (!takeLeft && right < data.size()) {
                        middleOutData.push_back(data[right]);
                        right++;
                        takeLeft = true;
                    } else if (left >= 0) {
                        // Only left elements remain
                        middleOutData.push_back(data[left]);
                        left--;
                    } else if (right < data.size()) {
                        // Only right elements remain
                        middleOutData.push_back(data[right]);
                        right++;
                    } else {
                        break;
                    }
                }
            }
        }

        MiddleOutOrder& operator++() {
            if (currentIndex < middleOutData.size()) {
                currentIndex++;
            }
            return *this;
        }

        const T& operator*() const {
            if (currentIndex >= middleOutData.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return middleOutData[currentIndex];
        }

        bool operator!=(const MiddleOutOrder& other) const {
            return currentIndex != other.currentIndex;
        }

        bool operator==(const MiddleOutOrder& other) const {
            return currentIndex == other.currentIndex;
        }

        MiddleOutOrder begin() const {
            MiddleOutOrder iter(*this);
            iter.currentIndex = 0;
            return iter;
        }

        MiddleOutOrder end() const {
            MiddleOutOrder iter(*this);
            iter.currentIndex = middleOutData.size();
            return iter;
        }
    };

    // Iterator factory methods
    AscendingOrder ascending() const {
        return AscendingOrder(data);
    }

    DescendingOrder descending() const {
        return DescendingOrder(data);
    }

    SideCrossOrder sideCross() const {
        return SideCrossOrder(data);
    }

    ReverseOrder reverse() const {
        return ReverseOrder(data);
    }

    Order order() const {
        return Order(data);
    }

    MiddleOutOrder middleOut() const {
        return MiddleOutOrder(data);
    }
};

} // namespace mycontainers

#endif // MYCONTAINER_HPP