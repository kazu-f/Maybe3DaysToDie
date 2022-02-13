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
        class ChangeTerrainDurable : ICommand
        {
            Terrain m_terrain;
            int beforeVal;
            int afterVal;

            public ChangeTerrainDurable(Terrain terrain, int tDurable)
            {
                beforeVal = terrain.durable;
                afterVal = tDurable;
                m_terrain = terrain;
            }
            public override void UnDo()
            {
                m_terrain.durable = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_terrain.durable = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        //最適ツール変更のコマンド。
        class ChangeTerrainKinds : ICommand
        {
            Terrain m_terrain;
            int beforeVal;
            int afterVal;

            public ChangeTerrainKinds(Terrain terrain, int toolKind)
            {
                beforeVal = terrain.tool;
                afterVal = toolKind;
                m_terrain = terrain;
            }
            public override void UnDo()
            {
                m_terrain.tool = beforeVal;        //適性ツール変更。
            }
            public override void ReDo()
            {
                m_terrain.tool = afterVal;        //適性ツール変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        //最適ツール変更のコマンド。
        class ChangeTerrainTexture : ICommand
        {
            Terrain m_terrain;
            string beforeVal;
            string afterVal;

            public ChangeTerrainTexture(Terrain terrain, string texFilePath)
            {
                beforeVal = terrain.texFilePath;
                afterVal = texFilePath;
                m_terrain = terrain;
            }
            public override void UnDo()
            {
                m_terrain.texFilePath = beforeVal;        //ファイルパス変更。
            }
            public override void ReDo()
            {
                m_terrain.texFilePath = afterVal;        //ファイルパス変更。
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }

        //採取アイテム追加のコマンド。
        class AddTerrainCollectItem : ICommand
        {
            Terrain m_terrain;
            CollectItem m_addCollectItem = null;

            public AddTerrainCollectItem(Terrain terrain, CollectItem addItem)
            {
                m_addCollectItem = addItem;
                m_terrain = terrain;
            }
            public override void UnDo()
            {
                //リストから削除。
                m_terrain.collectItemList.Remove(m_addCollectItem);
            }
            public override void ReDo()
            {
                //リストに追加。
                m_terrain.collectItemList.Add(m_addCollectItem);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return !m_terrain.collectItemList.Contains(m_addCollectItem);
            }
        }
        //採取アイテム削除のコマンド。
        class RemoveTerrainCollectItem : ICommand
        {
            Terrain m_terrain;
            CollectItem m_removeCollectItem = null;
            int m_index = int.MaxValue;

            public RemoveTerrainCollectItem(Terrain terrain, int index)
            {
                m_terrain = terrain;
                m_removeCollectItem = terrain.collectItemList[index];
                m_index = index;
            }
            public override void UnDo()
            {
                //リストに戻す。
                m_terrain.collectItemList.Insert(m_index, m_removeCollectItem);
            }
            public override void ReDo()
            {
                //リストから削除。
                m_terrain.collectItemList.Remove(m_removeCollectItem);
            }
            public override bool IsChanged()
            {
                //リストに登録されているか。
                return m_terrain.collectItemList.Contains(m_removeCollectItem);
            }
        }

    }
}
