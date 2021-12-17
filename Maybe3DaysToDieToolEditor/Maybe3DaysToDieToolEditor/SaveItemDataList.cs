﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    class SaveItemDataList
    {
        private string filePath = null;

        /// <summary>
        /// 名前を付けて保存。
        /// </summary>
        /// <param name="list"></param>
        public void SaveAsJsonFile(List<Item> list)
        {
            //SaveFileDialogクラスのインスタンスを作成
            SaveFileDialog sfd = new SaveFileDialog();

            //はじめのファイル名を指定する
            //はじめに「ファイル名」で表示される文字列を指定する
            sfd.FileName = "新しいファイル.json";
            //はじめに表示されるフォルダを指定する
            sfd.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            //[ファイルの種類]に表示される選択肢を指定する
            //指定しない（空の文字列）の時は、現在のディレクトリが表示される
            sfd.Filter = "JSONファイル(*.json)|*.json";
            //[ファイルの種類]ではじめに選択されるものを指定する
            //2番目の「すべてのファイル」が選択されているようにする
            sfd.FilterIndex = 1;
            //タイトルを設定する
            sfd.Title = "保存先のファイルを選択してください";
            //ダイアログボックスを閉じる前に現在のディレクトリを復元するようにする
            sfd.RestoreDirectory = true;
            //既に存在するファイル名を指定したとき警告する
            //デフォルトでTrueなので指定する必要はない
            sfd.OverwritePrompt = true;
            //存在しないパスが指定されたとき警告を表示する
            //デフォルトでTrueなので指定する必要はない
            sfd.CheckPathExists = true;

            //ダイアログを表示する
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                //OKボタンがクリックされたとき、
                //選択された名前で新しいファイルを作成し、
                //読み書きアクセス許可でそのファイルを開く。
                //既存のファイルが選択されたときはデータが消える恐れあり。
                System.IO.Stream stream;
                stream = sfd.OpenFile();
                if (stream != null)
                {
                    DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(Item[]));
                    try
                    {
                        serializer.WriteObject(stream, list.ToArray());
                        ////リストの中身を回す。
                        //foreach (var item in list)
                        //{
                        //    serializer.WriteObject(stream, item);
                        //}
                    }
                    finally
                    {
                        stream.Close();
                    }
                }
                filePath = sfd.FileName;
            }
        }

        private void OverwriteSaveJsonFile(List<Item> list)
        {
            System.IO.Stream stream;
            stream = new System.IO.FileStream(filePath, System.IO.FileMode.OpenOrCreate, System.IO.FileAccess.Write);
            if (stream != null)
            {
                DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(Item[]));
                try
                {
                    serializer.WriteObject(stream, list);
                }
                finally
                {
                    stream.Close();
                }
            }
        }

        /// <summary>
        /// セーブコマンド。
        /// </summary>
        /// <param name="list"></param>
        public void SaveJsonFile(List<Item>list, bool isSaveAs = false)
        {
            if (list.Count() <= 0)
            {
                //メッセージボックスを表示する
                MessageBox.Show("データありません。",
                    "エラー",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);

                return;
            }
            if (filePath == null || isSaveAs)
            {
                //名前を付けて保存。
                SaveAsJsonFile(list);
                return;
            }
            else
            {
                OverwriteSaveJsonFile(list);
            }
        }
    }
}