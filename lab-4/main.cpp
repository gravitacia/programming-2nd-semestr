#include <iostream>
#include <vector>
#include <algorithm>

namespace task {
    template<class InputIterator, class UnaryPredicate>
    bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (!pred(*first)) return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class UnaryPredicate>
    bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (pred(*first)) return true;
            ++first;
        }
        return false;
    }

    template<class InputIterator, class UnaryPredicate>
    bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (pred(*first)) return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class UnaryPredicate>
    bool one_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        int count = 0;

        while (first != last) {
            if (pred(*first))
                ++count;

            if (count == 1)
                return true;
            else
                return false;
        }
        return true;
    }

    template<class ForwardIterator, class Compare>
    bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
        if (first == last) return true;
        ForwardIterator next = first;
        while (++next != last) {
            if (comp(*next, *first))
                return false;
            ++first;
            ++next;
        }
        return true;
    }

    template<class InputIterator, class UnaryPredicate>
    bool is_partitioned(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (!pred(*first))
                break;
            ++first;
        }

        while (first != last) {
            if (pred(*first)) return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class Num>
    size_t find_not(InputIterator first, InputIterator last, Num el) {
        InputIterator iterator = first;
        while (iterator != last) {
            if (*iterator != el)
                return *iterator;
            ++iterator;
        }

        return 0;
    }

    template<class InputIterator, class Num>
    size_t find_backward(InputIterator first, InputIterator last, Num el) {

        InputIterator begin = first;
        InputIterator end = last - 1;

        while (last != first) {
            --last;
            if (*last == el)
                return *last;
        }
        return 0;

    }

    template<class InputIterator>
    bool is_palindrome(InputIterator first, InputIterator last) {

        InputIterator begin = first;
        InputIterator end = last - 1;

        while (begin != end) {
            if (*begin != *end)
                return false;
            ++begin;
            if (*begin == *end)
                break;
            --end;
        }
        return true;
    }

}

int main()
{
    std::vector<int> test {1, 2, 3, 3, 2, 1};

    std::cout << "test all_of: ";
    task::all_of(test.begin(), test.end(), [](int i) { return i >= 0; }) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;

    std::cout << "test any_of: ";
    task::any_of(test.begin(), test.end(), [](int i) { return i < 0; }) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;

    std::cout << "test none_of: ";
    task::none_of(test.begin(), test.end(), [](int i) { return i % 2 == 0; }) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;

    std::cout << "test one_of: ";
    task::one_of(test.begin(), test.end(), [](int i) { return i %3 == 0; }) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;

    std::cout << "test is_sorted: ";
    task::is_sorted(test.begin(), test.end(), [](int i, int j) { return i < j; }) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;

    std::cout << "test is_partitioned: ";
    task::is_partitioned(test.begin(), test.end(), [](int i) { return (i%2)==1; }) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;

    std::cout << "test find_not: ";
    std::cout << task::find_not(test.begin(), test.end(),3) << std::endl;


    std::cout << "test find_backward: ";
    std::cout << task::find_backward(test.begin(), test.end(),3) << std::endl;


    std::cout << "test is_palindrome: ";
    task::is_palindrome(test.begin(), test.end()) ? std::cout << "true" : std::cout << "false" << std::endl;

    return 0;
}