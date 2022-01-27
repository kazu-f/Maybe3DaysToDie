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
        [DataMember(Name = "collect")] public CollectItem collectItem;
    }

    /// <summary>
    /// 設置物からの採取情報。
    /// </summary>
    [DataContract]
    public struct CollectItem
    {
        public Item corectItem;                                         //採取するアイテム。
        [DataMember(Name = "corectItemID")] public int ItemID {
            get {
                if (corectItem == null) return 0;
                else return corectItem.itemID;
            }
            set
            {
                corectItem.itemID = value;
            }
        }
        [DataMember(Name = "corectionNum")] public int corectNum;       //採取量。
    }

}
