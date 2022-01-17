using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    public partial class ToolDataPanel : UserControl
    {
        public EditorCommandList commandList { private get; set; } = null;
        public ListBox listBox { private get; set; } = null;
        ToolKindsComboBox toolKinds;

        public ToolDataPanel()
        {
            InitializeComponent();
            //設定を行う。
            toolKinds = new ToolKindsComboBox(ToolComboBox);
        }

        /// <summary>
        /// ツールデータを表示する。
        /// </summary>
        /// <param name="tool"></param>
        public void DispToolData(ToolData tool)
        {
            //ツールの情報を表示する。
            DamageNumeric.Value = tool.damage;
            DurableNumeric.Value = tool.durable;
            UseStaminaNumeric.Value = tool.useStamina;
            toolKinds.SelectValue(tool.tool);
        }

        #region ツールデータの変更コマンド。
        /// <summary>
        /// ツールダメージを変更したとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeaveDamageValue(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(DamageNumeric.Text, out value))
            {
                DamageNumeric.Text = DamageNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;

            Command.ChangeToolDamage command = new Command.ChangeToolDamage((ToolData)item, (int)DamageNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// ツールの耐久を変更。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeaveDurableValue(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(DurableNumeric.Text, out value))
            {
                DurableNumeric.Text = DurableNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;

            Command.ChangeToolDurable command = new Command.ChangeToolDurable((ToolData)item, (int)DurableNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// ツールのスタミナを変更。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeaveUseStaminaValue(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(UseStaminaNumeric.Text, out value))
            {
                UseStaminaNumeric.Text = DurableNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;

            Command.ChangeToolUseStamina command = new Command.ChangeToolUseStamina((ToolData)item, (int)UseStaminaNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// 適性ツールのコンボボックスが変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ToolComboBox_SelectionChangeCommitted(object sender, EventArgs e)
        {
            if (listBox == null) return;
            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;
            Command.ChangeToolKinds command = new Command.ChangeToolKinds((ToolData)item, toolKinds.SelectedValue);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        #endregion
    }
}
