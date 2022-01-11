using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Maybe3DaysToDieToolEditor.Command;

namespace Maybe3DaysToDieToolEditor
{
    /// <summary>
    /// UnDo,ReDoのためのコマンドリスト。
    /// </summary>
    class EditorCommandList
    {
        private const int COMMAND_SIZE = 11;        //雑な実装だからコマンド範囲 + 1になってる。
        List<ICommand> commandList;                 //コマンドリスト。
        private int currentCommandNo = 0;           //現在のコマンド位置。
        private int currentCommandStart = 0;        //現在のコマンドの開始位置。
        private int currentCommandEnd = 0;          //現在のコマンドの終点。

        public EditorCommandList()
        {
            ResetCommandList();
        }

        /// <summary>
        /// コマンドの追加。
        /// </summary>
        /// <param name="command">実行するコマンド。</param>
        public void AddCommand(ICommand command)
        {
            //現在の番号を進める。
            currentCommandNo = (currentCommandNo + 1) % COMMAND_SIZE;
            commandList[currentCommandNo] = command;
            command.ReDo();     //コマンド実行。

            currentCommandEnd = currentCommandNo;

            //1週したらスタート位置をずらしていく。
            if(currentCommandEnd == currentCommandStart)
            {
                currentCommandStart = (currentCommandEnd + 1) % COMMAND_SIZE;
            }
        }

        /// <summary>
        /// UnDoの処理を実行する。
        /// </summary>
        public void CommandUnDo()
        {
            //リストがそもそもない。
            if (currentCommandNo < 0) return;
            //スタート位置まで戻った。
            if (currentCommandNo == currentCommandStart) return;
            //UnDoを行う。
            commandList[currentCommandNo].UnDo();
            //現在のコマンドを戻す。
            currentCommandNo--;
            currentCommandNo = (currentCommandNo + COMMAND_SIZE) % COMMAND_SIZE;
        }
        /// <summary>
        /// ReDoの処理を実行する。
        /// </summary>
        public void CommandReDo()
        {
            //リストがそもそもない。
            if (currentCommandNo < 0) return;
            //最終位置まで戻った。
            if (currentCommandNo == currentCommandEnd) return;
            //現在のコマンドを進める。
            currentCommandNo++;
            currentCommandNo = currentCommandNo % COMMAND_SIZE;
            //ReDoを行う。
            commandList[currentCommandNo].ReDo();
        }

        public void ResetCommandList()
        {
            commandList = new List<ICommand>();
            for (int i = 0; i < COMMAND_SIZE; i++)
            {
                commandList.Add(null);
            }
            currentCommandNo = 0;      //コマンドの中身がない。
            currentCommandStart = 0;
            currentCommandEnd = 0;
        }
    }
}
