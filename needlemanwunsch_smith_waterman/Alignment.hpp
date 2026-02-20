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
  
  /// Constructor with two sequences
  /// Makes an internal copy of the sequences.
  Alignment(const std::string& seq_v, const std::string& seq_h);
  
  /// Compute the aligment (i.e. score and traceback)
  /// given the three alignment parameters match, mismatch and gap.
  /// If local_align == true, compute the local Smith-Waterman (SW) alignment (extra points), or throw
  /// an exception if your implementation does not support SW.
  void compute(const int match, const int mismatch, const int gap, const bool local_align = false);
  
  /// Return the score of the alignment;
  /// Throws an exception if compute(...) was not called first
  int getScore() const;
  
  /// Output alignment into three strings.
  /// Gaps are denoted as '-' in sequences.
  /// The gap-string uses '|' (match) and ' ' (mismatch/gap).
  /// Note: all strings are equal in size
  /// e.g.
  /// a1:   "IMISSMISSIS-SIPPI-"
  /// gaps: " |   ||||||  |||| "
  /// a2:   "-M--YMISSISAHIPPIE"
  /// , where a1 corresponds to seq1, etc.
  /// Throws an exception if compute(...) was not called first
  void getAlignment(std::string& a1, std::string& gaps, std::string& a2) const;
  
  
private:
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
 * @brief Computes a global sequence alignment using the Needleman–Wunsch algorithm.
 *
 * @param match     Score for matching characters
 * @param mismatch  Penalty for mismatching characters
 * @param gap       Penalty for introducing a gap
 */
	void nw(const int match, const int mismatch, const int gap);

	/**
 * @brief Computes a local sequence alignment using the Smith–Waterman algorithm.
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
