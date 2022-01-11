using System;
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
            public ChangeToolDamage(ToolData toolData, int tDamage)
            {
                beforeVal = toolData.damage;
                afterVal = tDamage;
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
        /// ツール耐久を変更したときの処理。
        /// </summary>
        class ChangeToolDurable : ICommand
        {
            ToolData m_tool;
            int beforeVal;
            int afterVal;
            public ChangeToolDurable(ToolData toolData, int tDurable)
            {
                beforeVal = toolData.durable;
                afterVal = tDurable;
                m_tool = toolData;
            }
            public override void UnDo()
            {
                m_tool.durable = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_tool.durable = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        /// <summary>
        /// ツールの消費スタミナを変更したときの処理。
        /// </summary>
        class ChangeToolUseStamina : ICommand
        {
            ToolData m_tool;
            int beforeVal;
            int afterVal;
            public ChangeToolUseStamina(ToolData toolData, int tUseStamina)
            {
                beforeVal = toolData.useStamina;
                afterVal = tUseStamina;
                m_tool = toolData;
            }
            public override void UnDo()
            {
                m_tool.useStamina = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_tool.useStamina = afterVal;        //適性ツール変更。
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

        class ChangeToolTKM : ICommand
        {
            ToolData m_tool;
            string beforeStr;
            string afterStr;

            public ChangeToolTKM(ToolData toolData, string toolTkm)
            {
                beforeStr = toolData.tkmFile;
                afterStr = toolTkm;
                m_tool = toolData;
            }

            public override void UnDo()
            {
                m_tool.tkmFile = beforeStr;        //モデルファイル変更。
            }
            public override void ReDo()
            {
                m_tool.tkmFile = afterStr;        //モデルファイル変更。。
            }
            public override bool IsChanged()
            {
                return beforeStr != afterStr;
            }
        }

    }
}
