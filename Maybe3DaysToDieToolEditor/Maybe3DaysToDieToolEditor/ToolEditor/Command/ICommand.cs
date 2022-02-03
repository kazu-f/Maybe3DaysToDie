﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
        public abstract class ICommand
        {
            public abstract void UnDo();
            public abstract void ReDo();
            public abstract bool IsChanged();
        }

        /// <summary>
        /// アイテムの名前を変更するコマンド。
        /// </summary>
        public class RenameItemCommand : ICommand
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
        /// アイテムの名前を変更するコマンド。
        /// </summary>
        public class ItemStackChangeCommand : ICommand
        {
            Item m_Item;
            int beforeStr;
            int afterStr;

            public ItemStackChangeCommand(Item item, int after)
            {
                beforeStr = item.itemStackNum;    //変更前の文字列。
                afterStr = after;               //変更後の文字列。
                m_Item = item;                  //変更のあったアイテムを記録。
            }
            public override void UnDo()
            {
                m_Item.itemStackNum = beforeStr;        //名前変更。
            }
            public override void ReDo()
            {
                m_Item.itemStackNum = afterStr;        //名前変更。
            }
            public override bool IsChanged()
            {
                return afterStr != beforeStr;
            }
        }

        /// <summary>
        /// アイテムのモデルファイルを変更するコマンド。
        /// </summary>
        public class ChangeItemModel : ICommand
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
        public class ChangeItemIcon : ICommand
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

        //素材アイテム追加のコマンド。
        class AddCraftMaterialItem : ICommand
        {
            Item m_item;
            ItemCraftMaterial m_addCraftMaterial = null;

            public AddCraftMaterialItem(Item place, ItemCraftMaterial addItem)
            {
                m_addCraftMaterial = addItem;
                m_item = place;
            }
            public override void UnDo()
            {
                //リストから削除。
                m_item.itemCraftMaterials.Remove(m_addCraftMaterial);
            }
            public override void ReDo()
            {
                //リストに追加。
                m_item.itemCraftMaterials.Add(m_addCraftMaterial);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return !m_item.itemCraftMaterials.Contains(m_addCraftMaterial);
            }
        }

        //素材アイテム削除のコマンド。
        class RemoveCraftMaterialItem : ICommand
        {
            Item m_item;
            ItemCraftMaterial m_removeCraftMaterial = null;
            int m_index = int.MaxValue;

            public RemoveCraftMaterialItem(Item item, int index)
            {
                m_item = item;
                m_removeCraftMaterial = item.itemCraftMaterials[index];
                m_index = index;
            }
            public override void UnDo()
            {
                //リストに戻す。
                m_item.itemCraftMaterials.Insert(m_index, m_removeCraftMaterial);
            }
            public override void ReDo()
            {
                //リストから削除。
                m_item.itemCraftMaterials.Remove(m_removeCraftMaterial);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return m_item.itemCraftMaterials.Contains(m_removeCraftMaterial);
            }
        }
    }
}
