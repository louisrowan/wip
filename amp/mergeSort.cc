#include <iostream>
#include <vector>


std::vector<int> merge (std::vector<int> v) {

    int pivot = *(--v.end());
    std::vector<int> left;
    std::vector<int> right;

    std::vector<int>::iterator it;
    for (it = v.begin(); it != --v.end(); ++it) {
        if (*it < pivot) {
            left.push_back(*it);
        }
        else {
            right.push_back(*it);
        }
    }

    if (left.size() > 1) {
        left = merge(left);
    }
    if (right.size() > 1) {
        right = merge(right);
    }

    std::vector<int> res;
    std::vector<int>::iterator i;
    for (i = left.begin(); i != left.end(); ++i) {
        res.push_back(*i);
    }
    res.push_back(pivot);
    for (i = right.begin(); i != right.end(); ++i) {
        res.push_back(*i);
    }

    return res;
}


int main () {

    std::vector<int> vec = { 1, 9, 3, 6, 99, 5, 9, 8, 3, 34, 9, 35, -99, 99, 0, 3 };

    std::vector<int> ret = merge(vec);

    std::cout << "final result:" << std::endl;
    for (std::vector<int>::iterator i = ret.begin(); i != ret.end(); ++i) {
        std::cout << *i << std::endl;
    }

    return 0;
}