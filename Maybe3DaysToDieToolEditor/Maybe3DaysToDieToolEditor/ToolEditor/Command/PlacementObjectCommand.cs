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
    }
}
