#ifndef Dataset__
#define Dataset__

#include <cstring>

/**
 * Dataset (base) class
 *
 * @author Leon van der Veen
 */
class Dataset
{
	public:
		/**
		 * Item base class
		 *
		 * @author Leon van der Veen
		 */
		class Item
		{
			public:
				/**
				 * Distance
				 *
				 * Calculate distance to an other item.
				 *
				 * @return Distance
				 */
				virtual double distance(Item *other) = 0;
		};
	
	protected:
		Item *data;
		size_t dataSize;
	
	public:
		/**
		 * Constructor
		 */
		Dataset() :
			data(NULL), dataSize(0)
		{
		}
		
		/**
		 * Add items
		 *
		 * @param Items
		 * @param Count
		 */
		void addItems(Item *items, size_t count);
		
		/**
		 * Add item
		 *
		 * @param Item
		 */
		void addItem(Item *item)
		{
			addItems(item, 1);
		}
		
		/**
		 * Get data
		 *
		 * @return Data pointer
		 */
		const Item* getData() const
		{
			return data;
		}
		
		/**
		 * Get data
		 *
		 * @return Data pointer
		 */
		Item* getData()
		{
			return data;
		}
		
		/**
		 * Get data size
		 *
		 * @return Data size
		 */
		size_t getSize() const
		{
			return dataSize;
		}
};

#endif
