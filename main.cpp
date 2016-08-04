#include <iostream>
#include <string>
#include <vector>

class solution
{
  public:
    std::vector<std::string> diffWaysToCompute(std::string input) {
        std::vector<std::string> expr = addParen(input);
        return expr;
    }

  private:
    std::vector<std::string> addParen(std::string str) {
        std::vector<std::string> result;
        if (getNumOps(str) == 0)
            result.push_back(str);
        else if (getNumOps(str) == 1)
            result.push_back("("+str+")");
        else {
            auto op_loc = getOpLoc(str);
            for (auto loc : op_loc) {
                auto left = addParen(str.substr(0, loc));
                auto right = addParen(str.substr(loc+1));
                for (auto lft : left) {
                    for (auto rgt : right)
                        result.push_back("("+lft+str.substr(loc,1)+rgt+")");
                }
            }
        }
        return result;
    }

    std::vector<size_t> getOpLoc(std::string input) {
        std::vector<size_t> op_loc;
        size_t it = 0;
        while (it < input.length()) {
            if (input[it] == '+' || input[it] == '-' || input[it] == '*')
                op_loc.push_back(it);
            it++;
        }
        return op_loc;
    }

    int getNumOps(std::string str) {
        int num = 0;
        size_t start = str.find_first_of("+-*");
        while (start != std::string::npos) {
            num++;
            start = str.find_first_of("+-*", start+1);
        }
        return num;
    }
};

int main()
{
    // std::string expr{"2-1-1"};
    std::string expr{"2*3-4*5"};

    solution soln;
    auto result = soln.diffWaysToCompute(expr);

    std::cout << "All possible expressions with parentheses are:\n";
    for (auto s : result)
        std::cout << s << std::endl;
}
