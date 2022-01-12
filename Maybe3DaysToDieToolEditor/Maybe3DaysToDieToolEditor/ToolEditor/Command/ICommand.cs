using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
        abstract class ICommand
        {
            public abstract void UnDo();
            public abstract void ReDo();
            public abstract bool IsChanged();
        }

        /// <summary>
        /// アイテムの名前を変更するコマンド。
        /// </summary>
        class RenameItemCommand : ICommand
        {
            Item m_Item;
            string beforeStr;
            string afterStr;

            public RenameItemCommand(Item item, string after)
            {
                beforeStr = item.itemName;    //変更前の文字列。
                afterStr = after;               //変更後の文字列。
                m_Item = item;                  //変更のあったアイテムを記録。
            }
            public override void UnDo()
            {
                m_Item.itemName = beforeStr;        //名前変更。
            }
            public override void ReDo()
            {
                m_Item.itemName = afterStr;        //名前変更。
            }
            public override bool IsChanged()
            {
                return afterStr != beforeStr;
            }
        }

        /// <summary>
        /// アイテムのモデルファイルを変更するコマンド。
        /// </summary>
        class ChangeItemModel : ICommand
        {
            Item m_item;
            string beforeStr;
            string afterStr;

            public ChangeItemModel(Item itemData, string itemTkm)
            {
                beforeStr = itemData.tkmFile;
                afterStr = itemTkm;
                m_item = itemData;
            }

            public override void UnDo()
            {
                m_item.tkmFile = beforeStr;        //モデルファイル変更。
            }
            public override void ReDo()
            {
                m_item.tkmFile = afterStr;        //モデルファイル変更。。
            }
            public override bool IsChanged()
            {
                return beforeStr != afterStr;
            }
        }

        /// <summary>
        /// アイテムのアイコンファイルを変更するコマンド。
        /// </summary>
        class ChangeItemIcon : ICommand
        {
            Item m_item;
            string beforeStr;
            string afterStr;

            public ChangeItemIcon(Item itemData, string itemIcon)
            {
                beforeStr = itemData.iconData;
                afterStr = itemIcon;
                m_item = itemData;
            }

            public override void UnDo()
            {
                m_item.iconData = beforeStr;        //モデルファイル変更。
            }
            public override void ReDo()
            {
                m_item.iconData = afterStr;        //モデルファイル変更。。
            }
            public override bool IsChanged()
            {
                return beforeStr != afterStr;
            }
        }
    }
}
