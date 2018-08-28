#include "inventory.h"

using namespace engine;

Inventory::Inventory(int rows, int columns) : m_rows(rows), m_columns(columns) {
	m_amounts = new int[rows * columns];

	for (int i = 0; i < rows * columns; i++) {
		m_inventory.push_back(nullptr);
		m_amounts[i] = 0;
	}
}

void Inventory::addItem(Item* item, GLuint amount) {
	// If the item is null or the amount to add is 0
	if (!item || amount == 0)
		return;

	// The amount that is left to add
	int left = amount;

	// Loops through every non-empty slot in the inventory
	for (int i = 0; i < m_rows * m_columns; i++) {

		// If the current inventory slot is full or if the current item is null
		if (!m_inventory[i] || m_amounts[i] >= m_inventory[i]->getMaxAmount())
			continue;

		// If the added item has the same ID as the current item
		if (m_inventory[i]->getID() == item->getID()) {

			// If the left amount is smaller than or equal to the space left in the current slot
			if (left <= m_inventory[i]->getMaxAmount() - m_amounts[i]) {
				m_amounts[i] += left;
				return;
			}

			// If the left amount is greater than the space left in the current slot
			else {
				left -= m_inventory[i]->getMaxAmount() - m_amounts[i];
				m_amounts[i] = m_inventory[i]->getMaxAmount();
				continue;
			}
		}
	}

	// Loops through every empty slot in the inventory
	for (int i = 0; i < m_rows * m_columns; i++) {

		// Check if the current item is null
		if (!m_inventory[i]) {
			m_inventory[i] = item;

			// If the left amount is smaller than or equal to the maximum amount of allowed items
			if (left <= m_inventory[i]->getMaxAmount()) {
				m_amounts[i] = left;
				return;
			}

			// If the left amount is greater than the maximum amount of allowed items
			else {
				m_amounts[i] = m_inventory[i]->getMaxAmount();
				left -= m_inventory[i]->getMaxAmount();
				continue;
			}
		}
	}
}

void Inventory::removeItem(Item*item, GLuint amount) {
	if (!item || amount == 0)
		return;

	int left = amount;
	for (int i = 0; i < m_rows * m_columns; i++) {
		if (!m_inventory[i])
			continue;

		if (m_inventory[i]->getID() == item->getID()) {
			if (m_amounts[i] > left) {
				m_amounts[i] -= left;
				break;
			}
			else if (m_amounts[i] == left) {
				m_amounts[i] = 0;
				m_inventory[i] = nullptr;
				break;
			}
			else if (m_amounts[i] < left) {
				left -= m_amounts[i];
				m_amounts[i] = 0;
				m_inventory[i] = nullptr;
				continue;
			}
		}
	}
}

bool Inventory::contains(Item* item, GLuint amount) {
	int current = 0;

	if (!item)
		return false;

	if (amount == 0)
		return true;

	for (int i = 0; i < m_rows * m_columns; i++) {
		if (!m_inventory[i])
			continue;

		if (item->getID() == m_inventory[i]->getID()) {
			if (m_amounts[i] >= amount)
				return true;
			else
				current += m_amounts[i];
		}
		if (current >= amount)
			return true;
	}

	return false;
}

int Inventory::getRows() const {
	return m_rows;
}

int Inventory::getColumns() const {
	return m_columns;
}
