using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
        //耐久値変更のコマンド。
        class ChangePlacementObjectDurable : ICommand
        {
            PlacementObject m_place;
            int beforeVal;
            int afterVal;

            public ChangePlacementObjectDurable(PlacementObject place, int tDurable)
            {
                beforeVal = place.durable;
                afterVal = tDurable;
                m_place = place;
            }
            public override void UnDo()
            {
                m_place.durable = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_place.durable = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        //最適ツール変更のコマンド。
        class ChangePlacementObjKinds : ICommand
        {
            PlacementObject m_place;
            int beforeVal;
            int afterVal;

            public ChangePlacementObjKinds(PlacementObject place, int toolKind)
            {
                beforeVal = place.tool;
                afterVal = toolKind;
                m_place = place;
            }
            public override void UnDo()
            {
                m_place.tool = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_place.tool = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        
        //設置物のアクセスタグ変更のコマンド。
        class ChangePlacementObjTypes : ICommand
        {
            PlacementObject m_place;
            EnPlaceTypes beforeVal;
            EnPlaceTypes afterVal;

            public ChangePlacementObjTypes(PlacementObject place, EnPlaceTypes toolKind)
            {
                beforeVal = place.placeType;
                afterVal = toolKind;
                m_place = place;
            }
            public override void UnDo()
            {
                m_place.placeType = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_place.placeType = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }


        //採取アイテム追加のコマンド。
        class AddPlacementObjCollectItem : ICommand
        {
            PlacementObject m_place;
            CollectItem m_addCollectItem = null;

            public AddPlacementObjCollectItem(PlacementObject place, CollectItem addItem)
            {
                m_addCollectItem = addItem;
                m_place = place;
            }
            public override void UnDo()
            {
                //リストから削除。
                m_place.collectItemList.Remove(m_addCollectItem);
            }
            public override void ReDo()
            {
                //リストに追加。
                m_place.collectItemList.Add(m_addCollectItem);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return !m_place.collectItemList.Contains(m_addCollectItem);
            }
        }
        //採取アイテム削除のコマンド。
        class RemovePlacementObjCollectItem : ICommand
        {
            PlacementObject m_place;
            CollectItem m_removeCollectItem = null;
            int m_index = int.MaxValue;

            public RemovePlacementObjCollectItem(PlacementObject place, int index)
            {
                m_place = place;
                m_removeCollectItem = place.collectItemList[index];
                m_index = index;
            }
            public override void UnDo()
            {
                //リストに戻す。
                m_place.collectItemList.Insert(m_index, m_removeCollectItem);
            }
            public override void ReDo()
            {
                //リストから削除。
                m_place.collectItemList.Remove(m_removeCollectItem);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return m_place.collectItemList.Contains(m_removeCollectItem);
            }
        }
        //設置物のオブジェクトタイプ変更のコマンド。
        class ChangePlacementObjType : ICommand
        {
            PlacementObject m_place;
            EnPlaceTypes beforeVal;
            EnPlaceTypes afterVal;

            public ChangePlacementObjType(PlacementObject place, EnPlaceTypes val)
            {
                m_place = place;
                beforeVal = place.placeType;
                afterVal = val;
            }
            public override void UnDo()
            {
                m_place.placeType = beforeVal;
            }
            public override void ReDo()
            {
                m_place.placeType = afterVal;
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
    }
}
