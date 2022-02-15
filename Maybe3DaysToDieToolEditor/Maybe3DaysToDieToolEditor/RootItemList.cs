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
    public partial class RootItemList : Form
    {
        private EditorCommandList m_commandList;
        private BindingSource m_insideBS = new BindingSource();
        public PlacementObject placementObject {
            set {
                currentPlaceObj = value;
                m_insideBS.DataSource = currentPlaceObj.insideItemData;
            }
        }
        public PlacementObject currentPlaceObj { private get; set; } = null;

        public RootItemList(EditorCommandList commandList)
        {
            m_commandList = commandList;
            InitializeComponent();

            insideItemListBox.DisplayMember = "ItemName";
            insideItemListBox.ValueMember = "ItemName";
            insideItemListBox.DataSource = m_insideBS;
        }

    }
}
