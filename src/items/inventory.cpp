#include "inventory.h"

using namespace engine;

Inventory::Inventory(int rows, int columns) : m_rows(rows), m_columns(columns) {
	m_inventory = new Item[rows * columns];
	m_amounts = new int[rows * columns];
}

void Inventory::addItem(Item item, GLuint amount) {
	// Item ID of 0 means it isn't an item

	// If the item has an ID of 0 or the amount to add is 0
	if (item.getID() == 0 && amount == 0)
		return;

	// The amount that is left to add
	int left = amount;

	// Loops through every slot in the inventory, which is not empty
	for (int i = 0; i < m_rows * m_columns; i++) {

		// If the current inventory slot is full or if the current item has an ID of 0
		if (m_amounts[i] >= m_inventory[i].getMaxAmount() || m_inventory[i].getID() == 0)
			continue;

		// If the added item has the same ID as the current item
		if (m_inventory[i].getID() == item.getID()) {

			// If the left amount is smaller than or equal to the space left in the current slot
			if (left <= m_inventory[i].getMaxAmount() - m_amounts[i]) {
				m_amounts[i] += left;
				return;
			}

			// If the left amount is greater than the space left in the current slot
			else {
				left -= m_inventory[i].getMaxAmount() - m_amounts[i];
				m_amounts[i] = m_inventory[i].getMaxAmount();
				continue;
			}
		}
	}

	// Loops through every empty slot in the inventory
	for (int i = 0; i < m_rows * m_columns; i++) {

		// Check if the current item has an ID of 0
		if (m_inventory[i].getID() == 0) {
			m_inventory[i] = item;

			// If the left amount is smaller than or equal to the maximum amount of allowed items
			if (left <= m_inventory[i].getMaxAmount()) {
				m_amounts[i] = left;
				return;
			}

			// If the left amount is greater than the maximum amount of allowed items
			else {
				m_amounts[i] = m_inventory[i].getMaxAmount();
				left -= m_inventory[i].getMaxAmount();
				continue;
			}
		}
	}
}

void Inventory::removeItem(Item item, GLuint amount) {
	if (item.getID() == 0 && amount == 0)
		return;

	int left = amount;
	for (int i = 0; i < m_rows * m_columns; i++) {
		if (m_inventory[i].getID() == item.getID()) {
			if (m_amounts[i] > left) {
				m_amounts[i] -= left;
				break;
			}
			else if (m_amounts[i] == left) {
				m_amounts[i] = 0;
				m_inventory[i] = Item();
				break;
			}
			else if (m_amounts[i] < left) {
				left -= m_amounts[i];
				m_amounts[i] = 0;
				m_inventory[i] = Item();
				continue;
			}
		}
	}
}

bool Inventory::contains(Item item, GLuint amount) {
	int current = 0;
	for (int i = 0; i < m_rows * m_columns; i++) {
		if (item.getID() == m_inventory[i].getID()) {
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
