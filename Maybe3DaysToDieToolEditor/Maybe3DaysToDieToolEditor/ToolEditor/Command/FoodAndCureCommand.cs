using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
        //HP回復量変更のコマンド。
        class ChangeFoodAndCureHP : ICommand
        {
            FoodAndCure m_food;
            int beforeVal;
            int afterVal;

            public ChangeFoodAndCureHP(FoodAndCure food, int hp)
            {
                m_food = food;
                beforeVal = food.hp;
                afterVal = hp;
            }
            public override void UnDo()
            {
                m_food.hp = beforeVal;
            }
            public override void ReDo()
            {
                m_food.hp = afterVal;
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }

        //水分量の変更コマンド。
        class ChangeFoodAndCureWater : ICommand
        {
            FoodAndCure m_food;
            int beforeVal;
            int afterVal;

            public ChangeFoodAndCureWater(FoodAndCure food, int water)
            {
                m_food = food;
                beforeVal = food.water;
                afterVal = water;
            }
            public override void UnDo()
            {
                m_food.water = beforeVal;
            }
            public override void ReDo()
            {
                m_food.water = afterVal;
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        //満腹度の回復量変更コマンド。
        class ChangeFoodAndCureFull : ICommand
        {
            FoodAndCure m_food;
            int beforeVal;
            int afterVal;

            public ChangeFoodAndCureFull(FoodAndCure food, int full)
            {
                m_food = food;
                beforeVal = food.food;
                afterVal = full;
            }
            public override void UnDo()
            {
                m_food.food = beforeVal;
            }
            public override void ReDo()
            {
                m_food.food = afterVal;
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
        //スタミナ回復量の変更コマンド。
        class ChangeFoodAndCureStamina : ICommand
        {
            FoodAndCure m_food;
            int beforeVal;
            int afterVal;

            public ChangeFoodAndCureStamina(FoodAndCure food, int stamina)
            {
                m_food = food;
                beforeVal = food.stamina;
                afterVal = stamina;
            }
            public override void UnDo()
            {
                m_food.stamina = beforeVal;
            }
            public override void ReDo()
            {
                m_food.stamina = afterVal;
            }
            public override bool IsChanged()
            {
                return beforeVal != afterVal;
            }
        }
    }
}
