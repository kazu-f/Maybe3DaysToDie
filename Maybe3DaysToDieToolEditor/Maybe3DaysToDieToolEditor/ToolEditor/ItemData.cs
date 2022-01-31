using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace Maybe3DaysToDieToolEditor
{
    /// <summary>
    /// アイテムの基本的な情報。
    /// </summary>
    [KnownType(typeof(ToolData))]
    [KnownType(typeof(PlacementObject))]
    [DataContract]
    public abstract class Item 
    {
        [DataMember(Name = "itemID")] public int itemID { get; set; } = 0;
        [DataMember(Name = "name")] public string itemName { get; set; } = "";
        [DataMember(Name = "tkmFile")] public string tkmFile { get; set; } = "";
        [DataMember(Name = "iconData")] public string iconData { get; set; } = "";
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
        [DataMember(Name = "collectItems")] public List<CollectItem> collectItemList = new List<CollectItem>();
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
                if (collectItem == null) return "NoData";
                else return collectItem.itemName; 
            }
        }

        [DataMember(Name = "corectItemID")] public int ItemID {
            get {
                if (collectItem == null) return 0;
                else return collectItem.itemID;
            }
            set
            {
                collectItemID = value;
            }
        }
        [DataMember(Name = "corectionNum")] public int collectNum;       //採取量。
    }

}
