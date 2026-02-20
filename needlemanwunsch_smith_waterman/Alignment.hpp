#pragma once

#include <string>
#include <array>
#include <vector>
#include <iostream>


class Alignment
{

public:
  
  /// This makes the default constructor private
  /// i.e. an object of the class can not be created without providing 2 sequences
  Alignment() = delete;  // no NOT implement this function. Just leave it as is.
  
  /**
 * @brief Constructs an Alignment object for two sequences.
 *
 * @param seq_v Sequence aligned along the vertical axis.
 * @param seq_h Sequence aligned along the horizontal axis.
 */
  Alignment(const std::string& seq_v, const std::string& seq_h);
  
 /**
 * @brief Computes the sequence alignment using either global or local DP.
 *
 * @param match       Score added for matching characters.
 * @param mismatch    Penalty applied for mismatching characters.
 * @param gap         Penalty applied for gap insertion.
 * @param local_align If true, performs Smith–Waterman (local);
 *                    otherwise Needleman–Wunsch (global).
 */
  void compute(const int match, const int mismatch, const int gap, const bool local_align = false);
  
  /**
 * @brief Returns the computed alignment score.
 *
 * @return Final alignment score.
 * @throws std::logic_error If compute() has not been called yet.
 */
  int getScore() const;
  
  /**
 * @brief Returns the reconstructed alignment strings.
 *
 * @param a1   Aligned version of the first sequence (including gaps).
 * @param gaps String indicating matches ('|') and mismatches/gaps (' ').
 * @param a2   Aligned version of the second sequence (including gaps).
 *
 * @throws std::logic_error If compute() has not been called yet.
 */
  void getAlignment(std::string& a1, std::string& gaps, std::string& a2) const;
  
  
private:

    /**
 * @brief Direction indicators used for traceback.
 *
 * Encodes the predecessor direction of each DP cell:
 * - DIAGONAL   → match/mismatch
 * - HORIZONTAL → gap in vertical sequence
 * - VERTIKAL   → gap in horizontal sequence
 * - HOME       → traceback stop (used in local alignment)
 */
	enum class Dir : int {
		HOME = 0,
		DIAGONAL = 1,
		HORIZONTAL = 2,
		VERTIKAL = 3
	};

	int score{};
	bool _compute{ false };
	std::string _seq_v{};
	std::string _seq_h{};
	std::string _a1{};
	std::string _a2{};
	std::string _gaps{};
	std::vector <std::vector<int>> score_matrix{};
	std::vector <std::vector<Dir>> trace_matrix{};
	std::pair<size_t, size_t>max_index{};
	bool _local_align{};

	/**
 * @brief Computes a global sequence alignment using the NeedlemanWunsch algorithm.
 *
 * @param match     Score for matching characters
 * @param mismatch  Penalty for mismatching characters
 * @param gap       Penalty for introducing a gap
 */
	void nw(const int match, const int mismatch, const int gap);

	/**
 * @brief Computes a local sequence alignment using the SmithWaterman algorithm.
 *
 * @param match     Score for matching characters
 * @param mismatch  Penalty for mismatching characters
 * @param gap       Penalty for introducing a gap
 */
	void sw(const int match, const int mismatch, const int gap);

	/**
	 * @brief Reconstructs the alignment (for NW or SW) by tracing back through the traceback matrix.
	 *
	 */
	void trace_back();

};