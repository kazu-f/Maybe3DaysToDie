﻿using System;
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
        /// 適性ツール変数を変更するコマンド。
        /// </summary>
        class ChangeToolKinds : ICommand
        {
            ToolData m_tool;
            int beforeVal;
            int afterVal;

            public ChangeToolKinds(ToolData toolData,int toolKind)
            {
                beforeVal = toolData.tool;
                afterVal = toolKind;
                m_tool = toolData;
            }

            public override void UnDo()
            {
                m_tool.tool = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_tool.tool = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }

    }
}
