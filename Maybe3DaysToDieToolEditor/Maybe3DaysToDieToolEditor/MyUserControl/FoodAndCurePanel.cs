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
    }
}
