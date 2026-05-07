// self-assessment for robotics practical course:
// you can use this exercise as self-assessment for your C++ programming skills.
// you should be able to solve this without any help in 30 minutes only using https://en.cppreference.com/w/ as reference
// if you can't do this, you will have problems when participating in the practical course
// if you still decide to participate, you really should improve your C++ skills

#include <vector>
#include <iostream>

//problem:
// given vector of integers <numbers> and value <sum>
// test if there are two different elements of <numbers> with the sum of <sum>
// it should work with unordered vectors
// return the indices if found or {-1,-1}
// you have O(n*log(n)) time (it is possible in O(n) for unordered vectors)

// you can use http://coliru.stacked-crooked.com/ to test your code
// To run it on linux execute:
// g++ find_sum_of_two.cpp -o find_sum_of_two && ./find_sum_of_two




// ////////////////////////////////////////////////////////////////////////// //
// /////////////////////// do not touch (testing code) ////////////////////// //
// ////////////////////////////////////////////////////////////////////////// //
#include <iostream>

struct test
{
    std::string test_name;
    int sum;
    std::vector<int> numbers;
    std::pair<int, int> result;

    void check(const char* name, std::pair<int, int> (*fnc)(const std::vector<int>&, int)) const
    {
        const auto r = fnc(numbers, sum);
        if (r.first != result.first || r.second != result.second)
        {
            std::cout << "    failure    test " << test_name << " with fnc " << name << '\n';
        }
    }
};

std::vector<test> tests_sorted
{
    //   test_name                         sum  numbers                       result
    test{"01_empty                       ",  8, {                          }, {-1, -1}},
    test{"02_value                       ",  8, {+8                        }, {-1, -1}},
    test{"03_half                        ",  8, {+4                        }, {-1, -1}},
    test{"04_two_numbers                 ",  8, {+1, +7                    }, { 0,  1}},
    test{"05_halfx2                      ",  8, {+4, +4                    }, { 0,  1}},
    test{"06_sorted_found                ",  8, {+1, +2, +3, +4, +5, +8, +9}, { 2,  4}},
    test{"07_sorted_not_found            ",  8, {+1, +2, +3, +4, +8, +9    }, {-1, -1}},
    test{"08_negative_sorted_found       ",  8, {-9, -4, -1, +4, +5, +8, +9}, { 2,  6}},
    test{"09_negative_sorted_not_found   ",  8, {-9, -4, +1, +4, +5, +8, +9}, {-1, -1}}
};
std::vector<test> tests_unordered
{
    test{"10_unordered_found             ",  8, {+4, +5, +8, +1, +2, +3, +9}, { 1,  5}},
    test{"11_unordered_not_found         ",  8, {+4, +5, +8, +1, +2, +9    }, {-1, -1}},
    test{"12_negative_unordered_found    ",  8, {+9, +5, +8, +4, -4, -1, -9}, { 0,  5}},
    test{"13_negative_unordered_not_found",  8, {+9, +5, +8, +4, -4, +1, -9}, {-1, -1}}
};

#include <unordered_map>
std::pair<int, int> find_sum_of_two(const std::vector<int>& numbers, int sum)
{
    std::unordered_map<int, int> seen;
    

    for (int i = 0; i < (int)numbers.size(); i++) {
        int need = sum - numbers[i];

        if (seen.count(need)) {
            return {seen[need], i};
        }

        seen[numbers[i]] = i;
    }

    return {-1, -1};
}

int main()
{
    std::vector<int> a = {1, 2, 4, 5};

    std::pair<int, int> number = find_sum_of_two(a,10); 
    
    std::cout << number.first;

}