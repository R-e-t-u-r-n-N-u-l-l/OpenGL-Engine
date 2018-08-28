#pragma once

#include <vector>

#include "item.h"

namespace engine {

	class Inventory {

	protected:
		const int m_rows, m_columns;
		std::vector<Item*> m_inventory;
		int* m_amounts;

	public:
		Inventory(int rows, int columns);

		void addItem(Item* item, GLuint amount = 1);
		void removeItem(Item* item, GLuint amount = 1);
		bool contains(Item* item, GLuint amount = 1);

		int getRows() const;
		int getColumns() const;
	};
}
