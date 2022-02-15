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

        /// <summary>
        /// 確率を変更するコマンド。
        /// </summary>
        class ChangeInsideProbility : ICommand
        {
            InsideItem m_insideItem;
            int beforeVal;
            int afterVal;

            public ChangeInsideProbility(InsideItem insideItem,int value)
            {
                m_insideItem = insideItem;
                beforeVal = m_insideItem.probability;
                afterVal = value;
            }

            public override void UnDo()
            {
                //確率を元に戻す。
                m_insideItem.probability = beforeVal;
            }
            public override void ReDo()
            {
                //確率を変更する。
                m_insideItem.probability = afterVal;
            }
            public override bool IsChanged()
            {
                //変更があるか。
                return beforeVal != afterVal;
            }
        }
        /// <summary>
        /// 最大値を変更するコマンド。
        /// </summary>
        class ChangeInsideMaxNum : ICommand
        {
            InsideItem m_insideItem;
            int beforeVal;
            int afterVal;

            public ChangeInsideMaxNum(InsideItem insideItem,int value)
            {
                m_insideItem = insideItem;
                beforeVal = m_insideItem.maxNum;
                afterVal = value;
            }

            public override void UnDo()
            {
                //最大値を元に戻す。
                m_insideItem.maxNum = beforeVal;
            }
            public override void ReDo()
            {
                //最小値を変更する。
                m_insideItem.maxNum = afterVal;
            }
            public override bool IsChanged()
            {
                //変更があるか。
                return beforeVal != afterVal;
            }
        }
        /// <summary>
        /// 最小値を変更するコマンド。
        /// </summary>
        class ChangeInsideMinNum : ICommand
        {
            InsideItem m_insideItem;
            int beforeVal;
            int afterVal;

            public ChangeInsideMinNum(InsideItem insideItem,int value)
            {
                m_insideItem = insideItem;
                beforeVal = m_insideItem.minNum;
                afterVal = value;
            }

            public override void UnDo()
            {
                //最小値を元に戻す。
                m_insideItem.minNum = beforeVal;
            }
            public override void ReDo()
            {
                //最小値を変更する。
                m_insideItem.minNum = afterVal;
            }
            public override bool IsChanged()
            {
                //変更があるか。
                return beforeVal != afterVal;
            }
        }

    }
}
