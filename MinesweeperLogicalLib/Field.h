#pragma once
class Field
{
	public:
		Field() noexcept;
		~Field() noexcept = default;

		bool IsMine() const noexcept;
		void SetMine() noexcept;
		void SetMine(bool ismine) noexcept;

		bool IsFlagged() const noexcept;
		void ToggleFlag() noexcept;

		bool IsRevealed() const noexcept;
		void Reveal() noexcept;

		int getAdjacentMines() noexcept;
		void setAdjacentMines(int mines) noexcept;
		void incrementAdjacentMines() noexcept;

	private:
		bool isMine;
		bool isFlagged;
		bool isRevealed;
		int adjacentMines;
};

