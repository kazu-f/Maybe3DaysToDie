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
    public partial class FoodAndCurePanel : UserControl
    {
        public DeFocusCommand deFocus = null;

        public EditorCommandList commandList { private get; set; } = null;
        public ListBox listBox { private get; set; } = null;

        public FoodAndCurePanel()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 食料等を表示する。
        /// </summary>
        /// <param name="food">食料</param>
        public void DispFoodAndCureItem(FoodAndCure food)
        {
            HPNumeric.Value = food.hp;
            WaterNumeric.Value = food.water;
            FoodNumeric.Value = food.food;
            StaminaNumeric.Value = food.stamina;
        }

        #region 食料等のデータ変更処理。

        /// <summary>
        /// HPが変更された。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void HPNumericLeave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(HPNumeric.Text, out value))
            {
                HPNumeric.Text = HPNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(FoodAndCure)) return;

            var food = (FoodAndCure)item;

            Command.ChangeFoodAndCureHP command = new Command.ChangeFoodAndCureHP(food, (int)HPNumeric.Value);

            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }

            DispFoodAndCureItem(food);
        }

        /// <summary>
        /// 水分量が変更された。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WaterNumericLeave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(WaterNumeric.Text, out value))
            {
                WaterNumeric.Text = WaterNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(FoodAndCure)) return;

            var food = (FoodAndCure)item;

            Command.ChangeFoodAndCureWater command = new Command.ChangeFoodAndCureWater(food, (int)WaterNumeric.Value);

            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }

            DispFoodAndCureItem(food);
        }

        /// <summary>
        /// 満腹度が変更された。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FoodNumericLeave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(FoodNumeric.Text, out value))
            {
                FoodNumeric.Text = FoodNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(FoodAndCure)) return;

            var food = (FoodAndCure)item;

            Command.ChangeFoodAndCureFull command = new Command.ChangeFoodAndCureFull(food, (int)FoodNumeric.Value);

            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }

            DispFoodAndCureItem(food);
        }

        /// <summary>
        /// スタミナが変更された。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void StaminaNumericLeave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(StaminaNumeric.Text, out value))
            {
                StaminaNumeric.Text = StaminaNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(FoodAndCure)) return;

            var food = (FoodAndCure)item;

            Command.ChangeFoodAndCureStamina command = new Command.ChangeFoodAndCureStamina(food, (int)StaminaNumeric.Value);

            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }

            DispFoodAndCureItem(food);
        }

        #endregion  //食料等のデータ変更処理。

        private void activeControlNull(object sender, EventArgs e)
        {
            deFocus();
        }
    }
}
