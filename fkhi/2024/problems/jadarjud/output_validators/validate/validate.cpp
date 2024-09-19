#include "validate.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
    init_io(argc, argv);

    std::string true_line, outp_line;
    
    int query_num = 0;
    while(true) {
        if(!std::getline(judge_ans, true_line)) {
            if(author_out >> outp_line) {
                wrong_answer("Trailing output.\n");
            }
            accept();
        }
        if(!std::getline(author_out, outp_line)) {
            wrong_answer("Output too short.\n");
        }
        std::stringstream true_stream, outp_stream;
        true_stream << true_line;
        outp_stream << outp_line;
        std::vector<int> true_nums, outp_nums;
        int tmp;
        while(true_stream >> tmp) true_nums.push_back(tmp);
        while(outp_stream >> tmp) outp_nums.push_back(tmp);
        if(outp_nums.size() != true_nums.size()) {
            std::stringstream ss; 
            ss << "Failed to read right number of integers in query ";
            ss << query_num << ".\n";
            wrong_answer(ss.str());
        }
        std::sort(true_nums.begin(), true_nums.end());
        std::sort(outp_nums.begin(), outp_nums.end());
        if(outp_nums != true_nums) {
            std::stringstream ss;
            ss << "Incorrent values in query ";
            ss << query_num << ".\n";
            wrong_answer(ss.str());
        }
        query_num++;
    }
}
