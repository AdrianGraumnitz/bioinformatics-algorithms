
#include "Alignment.hpp"
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

Alignment::Alignment(const std::string& seq_v, const std::string& seq_h) 
    :_seq_v{ seq_v }, _seq_h{ seq_h }, 
    score_matrix(_seq_v.size() + 1, std::vector<int>(_seq_h.size() + 1, 0)),
    trace_matrix(_seq_v.size() + 1, std::vector<Dir>(_seq_h.size() + 1, Alignment::Dir::HOME)) {}

void Alignment::nw(const int match, const int mismatch, const int gap) {
    for (size_t i = 1; i < score_matrix.at(0).size(); ++i) {
        score_matrix.at(0).at(i) = gap + score_matrix.at(0).at(i - 1);
        trace_matrix.at(0).at(i) = Alignment::Dir::HORIZONTAL;
    }
    for (size_t i = 1; i < score_matrix.size(); ++i) {
        score_matrix.at(i).at(0) = gap + score_matrix.at(i - 1).at(0);
        trace_matrix.at(i).at(0) = Alignment::Dir::VERTIKAL;
    }
    //Score and Trace Matrix
    for (size_t i = 0; i < _seq_v.size(); ++i) {
        for (size_t j = 0; j < _seq_h.size(); ++j) {
            int d{ score_matrix.at(i).at(j) + (_seq_v.at(i) == _seq_h.at(j) ? match : mismatch) };
            int h{ score_matrix.at(i + 1).at(j) + gap }; //horizontal
            int v{ score_matrix.at(i).at(j + 1) + gap }; //vertikal
            int opt{ std::max({ d, v, h }) };
            score_matrix.at(i + 1).at(j + 1) = opt;
            Dir dir{ Alignment::Dir::HOME };

            if (d == opt)dir = Alignment::Dir::DIAGONAL;
            else if (v == opt)dir = Alignment::Dir::VERTIKAL;
            else if (h == opt)dir = Alignment::Dir::HORIZONTAL;
            trace_matrix.at(i + 1).at(j + 1) = dir;
        }
    }
}
void Alignment::sw(const int match, const int mismatch, const int gap) {
    
    int max_score{};
    for (size_t i = 1; i < score_matrix.at(0).size(); ++i) {
        score_matrix.at(0).at(i) = 0;
        trace_matrix.at(0).at(i) = Alignment::Dir::HOME;
    }
    for (size_t i = 1; i < score_matrix.size(); ++i) {
        score_matrix.at(i).at(0) = 0;
        trace_matrix.at(i).at(0) = Alignment::Dir::HOME;
    }
    //Score and Trace matrix
    for (size_t i = 0; i < _seq_v.size(); ++i) {
        for (size_t j = 0; j < _seq_h.size(); ++j) {
            int d{ score_matrix.at(i).at(j) + (_seq_v.at(i) == _seq_h.at(j) ? match : mismatch) };
            int h{ score_matrix.at(i + 1).at(j) + gap }; //horizontal
            int v{ score_matrix.at(i).at(j + 1) + gap }; //vertikal
            int opt{ std::max({ 0, d, v, h }) };
            score_matrix.at(i + 1).at(j + 1) = opt;
            if (max_score<score_matrix.at(i+1).at(j+1)) {
                max_score = score_matrix.at(i + 1).at(j + 1);
                max_index.first = i + 1;
                max_index.second = j + 1;
            }
            Dir dir{ Alignment::Dir::HOME };
            if (opt == 0)dir = Alignment::Dir::HOME;
            else if (d == opt)dir = Alignment::Dir::DIAGONAL;
            else if (v == opt)dir = Alignment::Dir::VERTIKAL;
            else if (h == opt)dir = Alignment::Dir::HORIZONTAL;
            trace_matrix.at(i + 1).at(j + 1) = dir;
        }
    }
}
void Alignment::trace_back() {
    size_t v{};
    size_t h{};
    if (_local_align == false) {
        v =static_cast<int>(_seq_v.size());
        h = static_cast<int>(_seq_h.size());
    }
    else {
        v = max_index.first;
        h = max_index.second;
    }
    _a1.clear();
    _a2.clear();
    _gaps.clear();
    while (trace_matrix.at(v).at(h) != Alignment::Dir::HOME) {
        Dir dir{ trace_matrix.at(v).at(h) };
        if (dir == Alignment::Dir::DIAGONAL) {
            _a1.push_back(_seq_v.at(v - 1));
            _a2.push_back(_seq_h.at(h - 1));
            if (_seq_v.at(v - 1) == _seq_h.at(h - 1)) {
                _gaps.push_back('|');
            }
            else {
                _gaps.push_back(' ');
            }
            --v;
            --h;
        }
        else if (dir == Alignment::Dir::VERTIKAL) {
            _a1.push_back(_seq_v.at(v - 1));
            _a2.push_back('-');
            _gaps.push_back(' ');
            --v;
        }
        else if (dir == Alignment::Dir::HORIZONTAL) {
            _a1.push_back('-');
            _a2.push_back(_seq_h.at(h - 1));
            _gaps.push_back(' ');
            --h;
        }
    }
    std::reverse(_a1.begin(), _a1.end());
    std::reverse(_a2.begin(), _a2.end());
    std::reverse(_gaps.begin(), _gaps.end());

    if (_local_align == false)score = score_matrix.at(_seq_v.size()).at(_seq_h.size());
    else score = score_matrix.at(max_index.first).at(max_index.second);
}
void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align) {
    //variablen für default parameter
    _local_align = local_align;
    if (local_align==false){
        nw(match, mismatch, gap);
    }
    else {
        sw(match, mismatch, gap);
    }
    trace_back();
    _compute = true;
}

int Alignment::getScore() const {
    if (!_compute) {
        throw std::logic_error("compute() was not called first");
    }
    return score;
}
void Alignment::getAlignment(std::string& a1, std::string& gaps, std::string& a2) const {
    if (!_compute) {
        throw std::logic_error("compute() was not called first");
    }
    a1 = _a1;
    a2 = _a2;
    gaps = _gaps;
}