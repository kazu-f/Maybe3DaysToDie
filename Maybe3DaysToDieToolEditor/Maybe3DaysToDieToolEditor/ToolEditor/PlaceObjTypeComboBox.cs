using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    //オブジェクトタイプの表示データ。
    class PlaceObjTypeDataSource
    {
        public PlaceObjTypeDataSource(string str, int value)
        {
            this.objTypeStr = str;
            this.objTypeValue = value;
        }

        public string objTypeStr { get; set; }
        public int objTypeValue { get; set; }
    }

    class PlaceObjTypeComboBox
    {
        public List<PlaceObjTypeDataSource> objTypesData;     //コンボボックスの表示するリスト
        private ComboBox objTypeCB;                       //オブジェクトタイプを選ぶコンボボックス。

        //選択している値を取得する。
        public int SelectedValue
        {
            get
            {
                if (objTypeCB == null) return 0;
                var val = objTypeCB.SelectedValue;
                if (val.GetType() == typeof(int))
                {
                    return (int)val;
                }
                return 0;
            }
        }

        public PlaceObjTypeComboBox(ComboBox comboBox)
        {
            objTypeCB = comboBox;

            objTypesData = new List<PlaceObjTypeDataSource>();
            PlaceObjTypeDataSource none = new PlaceObjTypeDataSource("無し", (int)EnPlaceTypes.NonAccess);
            objTypesData.Add(none);
            PlaceObjTypeDataSource root = new PlaceObjTypeDataSource("ルート", (int)EnPlaceTypes.Root);
            objTypesData.Add(root);

            objTypeCB.DataSource = objTypesData;
            objTypeCB.DisplayMember = "objTypeStr";
            objTypeCB.ValueMember = "objTypeValue";
        }

        public void SelectValue(int objType)
        {
            objTypeCB.SelectedValue = objType;
        }
    }
}
