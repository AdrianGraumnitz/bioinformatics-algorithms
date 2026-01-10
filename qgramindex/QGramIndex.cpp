#include "a5_util.hpp"
#include "QGramIndex.hpp"

#include <iostream>

QGramIndex::QGramIndex(const std::string& text, const uint8_t q) :_text{ text }, _q{q} {
    if (q < 1 || 13 < q) throw std::invalid_argument("Invalid q!");
    dir.resize((1ULL<<(2*_q))+1); //1ULL -> unsigned long long for big _q
    sa.resize(text.size() - _q + 1);
    _mask = bit_mask(_q);
    std::string qgram{text.substr(0,_q)};
    uint32_t h{ hash(qgram) };
    
    count_qgram(h, text);
    cumulative_sum();
    fill_dir_sa(h, text);
    
}
const std::string& QGramIndex::getText() const {
    return _text;
}
uint8_t QGramIndex::getQ() const {
    return _q;
}
std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const {
    if((1ULL<<(2*_q))<=h) throw std::invalid_argument("Invalid hash!");
    
    std::vector<uint32_t>hits{};
    uint32_t start{ dir.at(h) };
    uint32_t end{ dir.at(h + 1) };
    for (uint32_t i = start; i < end; i++) {
        hits.push_back(sa.at(i));
    }
    return hits;
    
}

uint32_t QGramIndex::bit_mask(uint8_t _q) {
    uint32_t mask{};
    for (uint8_t i = 0; i < 2 * _q; i++) {
        mask = (mask << 1) | 1;
    }
    return mask;
}
uint32_t QGramIndex::hash(const std::string& qgram) const {
    if (qgram.size() != static_cast<size_t>(_q)) throw std::invalid_argument("Invalid q-gram. Wrong length!");
    uint32_t hash{};
    for (size_t i = 0; i < qgram.size(); i++) {
        hash = (hash << 2) | ordValue(qgram.at(i));
    }
    return hash;
}
uint32_t QGramIndex::hashNext(const uint32_t prev_hash, const char new_pos) const {
    
    return ((prev_hash << 2) | ordValue(new_pos)) & _mask;
}
void QGramIndex::count_qgram(uint32_t h, std::string const& text) {
    dir.at(h) += 1;
    for (size_t i = static_cast<size_t>(_q); i < text.size(); i++) {
        h = hashNext(h, text.at(i));
        dir.at(h) += 1;
    }
}
void QGramIndex::cumulative_sum() {
    for (size_t i = 1; i < dir.size(); i++) {
        dir.at(i) += dir.at(i - 1);
    }
}
void QGramIndex::fill_dir_sa(uint32_t h, std::string const&text) {
    
    dir.at(h) -= 1;
    sa.at(dir.at(h)) = 0;
    for (size_t i = static_cast<size_t>(_q); i < text.size(); i++) {
        h = hashNext(h, text.at(i));
        dir.at(h) -= 1;
        sa.at(dir.at(h)) = i-_q+1;
    }
}



