using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace Maybe3DaysToDieToolEditor
{
    public enum EnItemType
    {
        enItem_None = -1,
        enItem_Tool,
        enItem_Place,
        enItem_Block,
        enItem_Terrain,
        enItem_Food,
        enItem_Material,
        ItemTypeNum
    }

    /// <summary>
    /// アイテムの基本的な情報。
    /// </summary>
    [KnownType(typeof(ToolData))]
    [KnownType(typeof(PlacementObject))]
    [KnownType(typeof(Block))]
    [KnownType(typeof(Terrain))]
    [KnownType(typeof(FoodAndCure))]
    [KnownType(typeof(Material))]
    [DataContract]
    public abstract class Item 
    {
        [DataMember(Name = "itemType")] public EnItemType ItemType {
            get
            {
                if (this.GetType() == typeof(ToolData))
                {
                    return EnItemType.enItem_Tool;
                }
                else if (this.GetType() == typeof(PlacementObject))
                {
                    return EnItemType.enItem_Place;
                }
                else if (this.GetType() == typeof(Terrain))
                {
                    return EnItemType.enItem_Terrain;
                }
                else if (this.GetType() == typeof(FoodAndCure))
                {
                    return EnItemType.enItem_Food;
                }
                else if (this.GetType() == typeof(Material))
                {
                    return EnItemType.enItem_Material;
                }
                else return EnItemType.enItem_None;
            }
            set
            {

            }
        }

        [DataMember(Name = "itemID")] public int itemID { get; set; } = 0;
        [DataMember(Name = "itemTypeID")] public int itemTypeID { get; set; } = 0;
        [DataMember(Name = "name")] public string itemName { get; set; } = "";
        [DataMember(Name = "stackNum")] public int itemStackNum { get; set; } = 1;
        [DataMember(Name = "tkmFile")] public string tkmFile { get; set; } = "";
        [DataMember(Name = "iconData")] public string iconData { get; set; } = "";
        [DataMember(Name = "itemMaterialData")] public List<ItemCraftMaterial> itemCraftMaterials = new List<ItemCraftMaterial>();
        //クラフトに必要なアイテムのデータの数。
        [DataMember(Name = "itemMaterialDataNum")] public int itemCraftMaterialNum {
            get
            {
                if (itemCraftMaterials != null) return itemCraftMaterials.Count;
                else return 0;
            }
            set
            {

            }
        }
        [DataMember(Name = "craftableItemIDs")] public CraftableItems craftableItems = new CraftableItems();
        public bool isRegist = true;               //リスト登録フラグ。
    }

    /// <summary>
    /// アイテムをクラフトするための素材データ。
    /// </summary>
    [DataContract]
    public class ItemCraftMaterial
    {
        public ItemCraftMaterial(Item _item, int _materialNum)
        {
            craftMaterialData = _item;
            this.craftItemNum = _materialNum;
            craftMaterialItemID = _item.itemID;
        }
        /// <summary>
        /// アイテムIDから素材アイテムデータを構築し直す。
        /// </summary>
        /// <param name="itemList">アイテムリスト。</param>
        public void BuildCollectItemData(List<Item> itemList)
        {
            if (craftMaterialItemID != -1 && itemList.Count > craftMaterialItemID)
            {
                craftMaterialData = itemList[craftMaterialItemID];
            }
        }

        public Item craftMaterialData = null;
        private int craftMaterialItemID = -1;                                 //素材アイテムのID。
        public string ItemName
        {
            get
            {
                if (craftMaterialData == null
                    || craftMaterialData.isRegist == false) return "NoData";
                else return craftMaterialData.itemName;
            }
        }

        [DataMember(Name = "craftMaterialID")]
        public int ItemID
        {
            get
            {
                if (craftMaterialData == null
                    || craftMaterialData.isRegist == false) return -1;
                else return craftMaterialData.itemID;
            }
            set
            {
                craftMaterialItemID = value;
            }
        }
        [DataMember(Name = "craftItemNum")] public int craftItemNum;       //必要量。
    }

    /// <summary>
    /// クラフト可能アイテム。
    /// </summary>
    [DataContract]
    public class CraftableItems
    {
        public List<Item> craftableItemList = new List<Item>();
        private List<int> _craftableItemIDs = new List<int>();
        /// <summary>
        /// アイテムIDからクラフト先のアイテムデータを構築。
        /// </summary>
        /// <param name="itemList">アイテムリスト。</param>
        public void BuildCraftableData(List<Item> itemList)
        {
            craftableItemList = new List<Item>();
            foreach (int id in _craftableItemIDs)
            {
                craftableItemList.Add(itemList[id]);
            }
        }

        [DataMember(Name = "craftableIDs")]
        public List<int> CraftableIDs
        {
            get
            {
                _craftableItemIDs.Clear();

                foreach(var item in craftableItemList)
                {
                    if (item.isRegist)
                    {
                        _craftableItemIDs.Add(item.itemID);
                    }
                }

                return _craftableItemIDs;
            }
            set
            {
                _craftableItemIDs = value;
            }
        }
        [DataMember(Name = "craftableItemNum")] public int craftableItemNum
        {
            get
            {
                if (_craftableItemIDs != null) return CraftableIDs.Count;
                else return 0;
            }
            set
            {

            }
        }
    }

    public enum ToolKinds : uint
    {
        hand = 0,                //素手
        axe = 1 << 0,            //斧
        Pickaxe = 1 << 1,        //ツルハシ
        shovel = 1 << 2,         //ショベル
        others = 1 << 3,         //その他
        DebugTool = 0xffffffff,  //デバッグ用ツール
    };

    //設置物のタイプ。
    public enum EnPlaceTypes
    {
        enType_Chest,
        enType_WorkBench,
        enType_OthreObject,
        enPlaceTypeNum
    }

    /// <summary>
    /// ツールの情報。
    /// </summary>
    [DataContract]
    public class ToolData : Item
    {
        [DataMember(Name = "damage")] public int damage { get; set; } = 0;
        [DataMember(Name = "durable")] public int durable { get; set; } = 0;
        [DataMember(Name = "useStamina")] public int useStamina { get; set; } = 0;
        [DataMember(Name = "tool")] public int tool { get; set; } = 0;
    }

    /// <summary>
    /// 設置物の情報。
    /// </summary>
    [DataContract]
    public class PlacementObject : Item
    {
        [DataMember(Name = "durable")] public int durable { get; set; } = 0;
        [DataMember(Name = "tool")] public int tool { get; set; } = 0;
        [DataMember(Name = "Type")] public EnPlaceTypes placeType { get; set; } = EnPlaceTypes.enType_Chest;
        [DataMember(Name = "collectItems")] public List<CollectItem> collectItemList = new List<CollectItem>();
        [DataMember(Name = "collectItemDataNum")]
        public int collectItemDataNum
        {
            get
            {
                if (collectItemList != null) return collectItemList.Count;
                else return 0;
            }
            set
            {

            }
        }
    }

    /// <summary>
    /// 設置物の情報。
    /// </summary>
    [DataContract]
    public class Block : Item
    {
        [DataMember(Name = "durable")] public int durable { get; set; } = 0;
        [DataMember(Name = "tool")] public int tool { get; set; } = 0;
        [DataMember(Name = "collectItems")] public List<CollectItem> collectItemList = new List<CollectItem>();
        [DataMember(Name = "collectItemDataNum")]
        public int collectItemDataNum
        {
            get
            {
                if (collectItemList != null) return collectItemList.Count;
                else return 0;
            }
            set
            {

            }
        }
    }

    /// <summary>
    /// 設置物の情報。
    /// </summary>
    [DataContract]
    public class Terrain : Item
    {
        [DataMember(Name = "durable")] public int durable { get; set; } = 0;
        [DataMember(Name = "tool")] public int tool { get; set; } = 0;
        [DataMember(Name = "texture")] public string texFilePath { get; set; } = "";
        [DataMember(Name = "collectItems")] public List<CollectItem> collectItemList = new List<CollectItem>();
        [DataMember(Name = "collectItemDataNum")]
        public int collectItemDataNum
        {
            get
            {
                if (collectItemList != null) return collectItemList.Count;
                else return 0;
            }
            set
            {

            }
        }
    }

    /// <summary>
    /// 設置物からの採取情報。
    /// </summary>
    [DataContract]
    public class CollectItem
    {
        public CollectItem(Item _item,int _collectNum)
        {
            collectItem = _item;
            this.collectNum = _collectNum;
            collectItemID = _item.itemID;
        }
        /// <summary>
        /// アイテムIDから採取アイテムデータを構築し直す。
        /// </summary>
        /// <param name="itemList">アイテムリスト。</param>
        public void BuildCollectItemData(List<Item> itemList)
        {
            if(collectItemID != -1 && itemList.Count > collectItemID) collectItem = itemList[collectItemID];
        }

        public Item collectItem;                                         //採取するアイテム。
        private int collectItemID = -1;                                 //採取するアイテムのID。
        public string ItemName {
            get {
                if (collectItem == null
                    || collectItem.isRegist == false) return "NoData";
                else return collectItem.itemName; 
            }
        }

        [DataMember(Name = "corectItemID")] public int ItemID {
            get {
                if (collectItem == null
                    || collectItem.isRegist == false) return -1;
                else return collectItem.itemID;
            }
            set
            {
                collectItemID = value;
            }
        }
        [DataMember(Name = "corectionNum")] public int collectNum;       //採取量。
    }

    /// <summary>
    /// 食料や回復アイテム等の情報。
    /// </summary>
    [DataContract]
    public class FoodAndCure : Item
    {
        [DataMember(Name = "HP")] public int hp { get; set; } = 0;
        [DataMember(Name = "water")] public int water { get; set; } = 0;
        [DataMember(Name = "food")] public int food { get; set; } = 0;
        [DataMember(Name = "stamina")] public int stamina { get; set; } = 0;
    }

    [DataContract]
    public class Material : Item
    {
        [DataMember(Name = "MaterialType")] public int type = 0;
    }


}
