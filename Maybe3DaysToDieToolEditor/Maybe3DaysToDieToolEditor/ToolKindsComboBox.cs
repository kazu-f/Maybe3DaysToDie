using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    //適性ツールの表示データ。
    class ToolKindsDataSource
    {
        public ToolKindsDataSource(string str, int value)
        {
            this.toolKindsStr = str;
            this.toolKindsValue = value;
        }

        public string toolKindsStr { get; set; }
        public int toolKindsValue { get; set; }
    }


    class ToolKindsComboBox
    {
        public List<ToolKindsDataSource> toolKindsData;
        private ComboBox toolKindsCB;
        
        public ToolKindsComboBox(ComboBox comboBox)
        {
            //コンボボックスの参照を取る。
            toolKindsCB = comboBox;
            //データリストを作る。
            toolKindsData = new List<ToolKindsDataSource>();
            ToolKindsDataSource hand = new ToolKindsDataSource("素手", (int)ToolKinds.hand);
            toolKindsData.Add(hand);
            ToolKindsDataSource axe = new ToolKindsDataSource("斧", (int)ToolKinds.axe);
            toolKindsData.Add(axe);
            ToolKindsDataSource Pickaxe = new ToolKindsDataSource("つるはし", (int)ToolKinds.Pickaxe);
            toolKindsData.Add(Pickaxe);
            ToolKindsDataSource shovel = new ToolKindsDataSource("シャベル", (int)ToolKinds.shovel);
            toolKindsData.Add(shovel);
            ToolKindsDataSource others = new ToolKindsDataSource("その他", (int)ToolKinds.others);
            toolKindsData.Add(others);
            ToolKindsDataSource DebugTool = new ToolKindsDataSource("デバッグツール", -1);
            toolKindsData.Add(DebugTool);
            //リスト設定。
            toolKindsCB.DataSource = toolKindsData;
            toolKindsCB.DisplayMember = "toolKindsStr";
            toolKindsCB.ValueMember = "toolKindsValue";
        }

        public void SelectValue(int toolKinds)
        {
            toolKindsCB.SelectedValue = toolKinds;
        }
    }
}
