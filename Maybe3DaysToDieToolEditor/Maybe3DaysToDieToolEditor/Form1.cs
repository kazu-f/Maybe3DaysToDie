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
    public partial class Maybe3DaysToDie_ToolEditor : Form
    {

        #region フォーム関連の変数。
        string filePath = null;
        List<Item> m_itemList = new List<Item>();
        ItemDataList m_itemDataList = new ItemDataList();
        BindingSource listBoxBS = new BindingSource();
        BindingSource itemDataBS = new BindingSource();
        EditorCommandList commandList = new EditorCommandList();
        //ToolKindsComboBox toolKinds;
        SaveItemDataList saveData;
        LoadItemDataList loadData;
        #endregion

        public Maybe3DaysToDie_ToolEditor()
        {
            InitializeComponent();
            listBoxBS.DataSource = m_itemList;
            itemDataBS.DataSource = m_itemList;
            m_itemDataList.ItemList = m_itemList;

            ItemList.DisplayMember = "itemName";
            ItemList.ValueMember = "itemName";
            ItemList.DataSource = listBoxBS;

            itemDataPanel1.commandList = commandList;
            itemDataPanel1.listBox = ItemList;
            itemDataPanel1.ItemDataBS = itemDataBS;
            itemDataPanel1.updateBSMethod = UpdateBS;

            toolDataPanel1.commandList = commandList;
            toolDataPanel1.listBox = ItemList;

            placementObjectPanel1.commandList = commandList;
            placementObjectPanel1.listBox = ItemList;
            placementObjectPanel1.ItemDataBS = itemDataBS;

            terrainPanel1.commandList = commandList;
            terrainPanel1.listBox = ItemList;
            terrainPanel1.ItemDataBS = itemDataBS;

            foodAndCurePanel1.commandList = commandList;
            foodAndCurePanel1.listBox = ItemList;

            GroupBoxPanelDisable();
            toolDataPanel1.Visible = true;

            //設定を行う。
            saveData = new SaveItemDataList();
            loadData = new LoadItemDataList();
        }

        private void UpdateBS()
        {
            listBoxBS.ResetBindings(false);
            itemDataBS.ResetBindings(false);
        }
        /// <summary>
        /// アイテムリストに更新が入ったら呼ぶ処理。
        /// </summary>
        private void UpdateItemList()
        {
            m_itemDataList.UpdateItemListID();

            UpdateBS();
        }
        /// <summary>
        /// ユーザコントロールをすべて非表示にする。
        /// </summary>
        private void GroupBoxPanelDisable()
        {
            toolDataPanel1.Visible = false;
            placementObjectPanel1.Visible = false;
            terrainPanel1.Visible = false;
            foodAndCurePanel1.Visible = false;
            materialPanel1.Visible = false;
        }

        #region リスト操作の処理。
        /// <summary>
        /// リストからデータを削除する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var select = ItemList.SelectedItem;
            if (select == null) return;       //選択がなければ処理しない。
            //アイテムデータならばリストから削除。
            if (select is Item)
            {
                var item = (Item)select;
                Command.DeleteItem command = new Command.DeleteItem(item, m_itemList, UpdateItemList);

                if (command.IsChanged())
                {
                    commandList.AddCommand(command);
                    //登録が外れたら。
                    if (!item.isRegist)
                    {
                        var reDisp = ItemList.SelectedItem;
                        if (reDisp is Item) DispItemData((Item)reDisp);
                    }
                }
            }
        }
        /// <summary>
        /// リストに新しいツールデータを追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ToolDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var newTool = new ToolData { itemName = "ToolData" };

            Command.AddNewItem command = new Command.AddNewItem(newTool, m_itemList, UpdateItemList);

            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }

        /// <summary>
        /// リストに新しい設置物データを追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void PlaceObjDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var newPlace = new PlacementObject { itemName = "PlacementObject" };

            Command.AddNewItem command = new Command.AddNewItem(newPlace, m_itemList, UpdateItemList);

            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }

        private void TerrainToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var newTerrain = new Terrain { itemName = "Terrain" };

            Command.AddNewItem command = new Command.AddNewItem(newTerrain, m_itemList, UpdateItemList);

            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// リストに食料等のアイテムを追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FoodAndCureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var newFood = new FoodAndCure { itemName = "FoodAndCure" };

            Command.AddNewItem command = new Command.AddNewItem(newFood, m_itemList, UpdateItemList);

            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }

        }
        /// <summary>
        /// リストに素材アイテムを追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MaterialDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var material = new Material { itemName = "Material" };

            Command.AddNewItem command = new Command.AddNewItem(material, m_itemList, UpdateItemList);

            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        #endregion

        #region データを表示する処理。
        /// <summary>
        /// リストの選択が変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ItemList_SelectedIndexChanged(object sender, EventArgs e)
        {
            var item = ItemList.SelectedItem;
            //アイテムデータならばテキストボックスに表記。
            if (item is Item) DispItemData((Item)item);
        }

        /// <summary>
        /// アイテムの情報を表示する。
        /// </summary>
        /// <param name="item"></param>
        private void DispItemData(Item item)
        {
            if (item == null)
            {
                return;
            }
            //アイテムデータを表示。
            itemDataPanel1.DispItemData(item);
            //データタイプに応じて処理を分岐。
            if (typeof(ToolData) == item.GetType())
            {
                GroupBoxPanelDisable();
                toolDataPanel1.Visible = true;
                toolDataPanel1.DispToolData((ToolData)item);
            }
            else if (typeof(PlacementObject) == item.GetType())
            {
                GroupBoxPanelDisable();
                placementObjectPanel1.Visible = true;
                placementObjectPanel1.DispPlacementObject((PlacementObject)item);
            }
            else if (typeof(Terrain) == item.GetType())
            {
                GroupBoxPanelDisable();
                terrainPanel1.Visible = true;
                terrainPanel1.DispTerrain((Terrain)item);
            }
            else if(typeof(FoodAndCure) == item.GetType())
            {
                GroupBoxPanelDisable();
                foodAndCurePanel1.Visible = true;
                foodAndCurePanel1.DispFoodAndCureItem((FoodAndCure)item);
            }
            else if(typeof(Material) == item.GetType())
            {
                GroupBoxPanelDisable();
                materialPanel1.Visible = true;
                materialPanel1.DispMaterialItem((Material)item);
            }
            else
            {
                GroupBoxPanelDisable();

            }
        }
        #endregion

        #region UnDo、ReDo処理。
        /// <summary>
        /// UnDo処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void UnDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandUnDo();
            var item = ItemList.SelectedItem;
            if (item != null)
            {
                //アイテムデータならばテキストボックスに表記。
                if (item is Item) DispItemData((Item)item);
                UpdateBS();
            }
        }

        /// <summary>
        /// ReDo処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void reDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandReDo();
            var item = ItemList.SelectedItem;
            if (item != null)
            {
                //アイテムデータならばテキストボックスに表記。
                if (item is Item) DispItemData((Item)item);
                UpdateBS();
            }
        }
        #endregion

        //フォーカスを外す。
        private void DeFocus()
        {
            this.ActiveControl = null;
        }

        private void MouseCapture(object sender, EventArgs e)
        {
            DeFocus();
        }

        #region ファイル保存関係。
        /// <summary>
        /// 名前を付けて保存。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            filePath = saveData.SaveJsonFile(m_itemList);
        }
        /// <summary>
        /// 上書き保存。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            filePath = saveData.SaveJsonFile(m_itemList, filePath);
        }
        /// <summary>
        /// 読み込み。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenFileOToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<Item> list;
            filePath = loadData.LoadJsonFile(out list);
            if(list != null)
            {
                m_itemList = list;
                m_itemDataList.ItemList = m_itemList;
                m_itemDataList.UpdateItemListID();
                //データの構築を行う。
                BuildOpenFileItemData(list);
                //コマンドリストをリセット。
                commandList.ResetCommandList();
                //アイテムのリストを読み込んだものに変更。
                listBoxBS.DataSource = m_itemList;
                itemDataBS.DataSource = m_itemList;
                //表記を変更。
                ItemList.SelectedItem = m_itemList[0];
                DispItemData(m_itemList[0]);
                UpdateBS();
            }
            DeFocus();
        }

        /// <summary>
        /// ファイルから開いたデータから構築を行う。
        /// </summary>
        /// <param name="list">開いたアイテムのリスト。</param>
        private void BuildOpenFileItemData(List<Item> list)
        {
            foreach (var item in list)
            {
                item.isRegist = true;
                //クラフト可能先アイテムを登録し直す。
                item.craftableItems.BuildCraftableData(list);
                //素材アイテムを登録し直す。
                foreach (var material in item.itemCraftMaterials)
                {
                    material.BuildCollectItemData(list);
                }
                //設置物。
                if (item.GetType() == typeof(PlacementObject))
                {
                    //採取アイテムを登録し直す。
                    var place = (PlacementObject)item;
                    foreach (var collect in place.collectItemList)
                    {
                        collect.BuildCollectItemData(list);
                    }
                }
            }
        }
        #endregion ファイル保存関係。
    }
}
