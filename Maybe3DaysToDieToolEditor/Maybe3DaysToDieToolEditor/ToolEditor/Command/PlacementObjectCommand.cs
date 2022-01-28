using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maybe3DaysToDieToolEditor
{
    namespace Command
    {
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
    }
}
