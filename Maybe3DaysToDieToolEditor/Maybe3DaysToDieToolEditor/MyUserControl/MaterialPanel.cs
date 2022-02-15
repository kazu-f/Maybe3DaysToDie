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
    public partial class MaterialPanel : UserControl
    {
        public DeFocusCommand deFocus = null;

        public MaterialPanel()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 素材アイテムのデータを表示する。
        /// </summary>
        /// <param name="material"></param>
        public void DispMaterialItem(Material material)
        {

        }

        private void activeControlNull(object sender, EventArgs e)
        {
            deFocus();
        }
    }
}
