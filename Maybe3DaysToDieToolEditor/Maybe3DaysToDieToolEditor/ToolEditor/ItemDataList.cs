using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    class ItemDataList
    {
        public List<Item> ItemList
        {
            get { return m_items; }
            set { m_items = value; }
        }

        private List<Item> m_items;
        private List<ToolData> m_tools;
        private List<PlacementObject> m_placements;
        private List<Block> m_blocks;
        private List<Terrain> m_terrains;
        private List<FoodAndCure> m_foods;
        private List<Material> m_materials;

        public ItemDataList()
        {
            m_tools = new List<ToolData>();
            m_placements = new List<PlacementObject>();
            m_blocks = new List<Block>();
            m_terrains = new List<Terrain>();
            m_foods = new List<FoodAndCure>();
            m_materials = new List<Material>();
        }

        public void UpdateItemListID()
        {
            m_tools.Clear();
            m_placements.Clear();
            m_blocks.Clear();
            m_terrains.Clear();
            m_foods.Clear();
            m_materials.Clear();
            for (int i = 0; i < m_items.Count; i++)
            {
                var _item = m_items[i];
                _item.itemID = i;

                if(_item.GetType() == typeof(ToolData))
                {
                    _item.itemTypeID = m_tools.Count;
                    m_tools.Add((ToolData)_item);
                }
                else if(_item.GetType() == typeof(PlacementObject))
                {
                    _item.itemTypeID = m_placements.Count;
                    m_placements.Add((PlacementObject)_item);
                }
                else if(_item.GetType() == typeof(Block))
                {
                    _item.itemTypeID = m_blocks.Count;
                    m_blocks.Add((Block)_item);
                }
                else if(_item.GetType() == typeof(Terrain))
                {
                    _item.itemTypeID = m_terrains.Count;
                    m_terrains.Add((Terrain)_item);
                }
                else if(_item.GetType() == typeof(FoodAndCure))
                {
                    _item.itemTypeID = m_foods.Count;
                    m_foods.Add((FoodAndCure)_item);
                }
                else if(_item.GetType() == typeof(Material))
                {
                    _item.itemTypeID = m_materials.Count;
                    m_materials.Add((Material)_item);
                }
            }
        }

    }
}
