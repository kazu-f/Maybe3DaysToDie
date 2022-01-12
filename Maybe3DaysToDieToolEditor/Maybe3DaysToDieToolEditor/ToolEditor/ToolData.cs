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
    [DataContract]
    abstract class Item 
    {
        [DataMember(Name = "name")] public string itemName { get; set; }
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
    class ToolData : Item
    {
        [DataMember(Name = "damage")] public int damage { get; set; } = 0;
        [DataMember(Name = "durable")] public int durable { get; set; } = 0;
        [DataMember(Name = "useStamina")] public int useStamina { get; set; } = 0;
        [DataMember(Name = "tool")] public int tool { get; set; } = 0;
    }
}
