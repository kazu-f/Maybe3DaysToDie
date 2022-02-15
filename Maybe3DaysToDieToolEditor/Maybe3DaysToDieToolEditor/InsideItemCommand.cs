using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
        class AddInsideItem : ICommand
        {
            PlacementObject m_place;
            InsideItem m_addInsideData = null;
            int m_insideIndex = -1;

            public AddInsideItem(PlacementObject _place, InsideItem addItem)
            {
                m_addInsideData = addItem;
                m_place = _place;
                m_insideIndex = m_place.insideItemData.Count;                  //クラフト可能先リストのインデックス。
            }
            public override void UnDo()
            {
                //リストから削除。
                m_place.insideItemData.Remove(m_addInsideData);
            }
            public override void ReDo()
            {
                //リストに追加。
                m_place.insideItemData.Insert(m_insideIndex,m_addInsideData);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return !m_place.insideItemData.Contains(m_addInsideData);
            }
        }

        class RemoveInsideItem : ICommand
        {
            PlacementObject m_place;
            InsideItem m_removeInsideData = null;
            int m_insideIndex = -1;

            public RemoveInsideItem(PlacementObject _place, InsideItem removeItem)
            {
                m_removeInsideData = removeItem;
                m_place = _place;
                m_insideIndex = m_place.insideItemData.IndexOf(removeItem);                  //クラフト可能先リストのインデックス。
            }
            public override void UnDo()
            {
                //リストに追加。
                m_place.insideItemData.Insert(m_insideIndex,m_removeInsideData);
            }
            public override void ReDo()
            {
                //リストから削除。
                m_place.insideItemData.Remove(m_removeInsideData);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return m_place.insideItemData.Contains(m_removeInsideData);
            }
        }
    }
}
