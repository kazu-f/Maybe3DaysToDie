﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
        /// <summary>
        /// ツールダメージを変更したときの処理。
        /// </summary>
        class ChangeToolDamage : ICommand
        {
            ToolData m_tool;
            int beforeVal;
            int afterVal;
            public ChangeToolDamage(ToolData toolData, int toolKind)
            {
                beforeVal = toolData.damage;
                afterVal = toolKind;
                m_tool = toolData;
            }
            public override void UnDo()
            {
                m_tool.damage = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_tool.damage = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
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

            public ChangeToolKinds(ToolData toolData, int toolKind)
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
