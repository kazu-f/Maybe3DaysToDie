using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    class LoadItemDataList
    {
        public string LoadJsonFile(out List<Item> list)
        {
            //SaveFileDialogクラスのインスタンスを作成
            OpenFileDialog ofd = new OpenFileDialog();

            //はじめのファイル名を指定する
            //はじめに「ファイル名」で表示される文字列を指定する
            //ofd.FileName = "新しいファイル.fmcr";
            //はじめに表示されるフォルダを指定する
            ofd.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            //[ファイルの種類]に表示される選択肢を指定する
            //指定しない（空の文字列）の時は、現在のディレクトリが表示される
            ofd.Filter = "JSONファイル(*.json)|*.json";
            //[ファイルの種類]ではじめに選択されるものを指定する
            ofd.FilterIndex = 1;
            //タイトルを設定する
            ofd.Title = "読み込むファイルを選択してください";
            //ダイアログボックスを閉じる前に現在のディレクトリを復元するようにする
            ofd.RestoreDirectory = true;
            //存在しないファイルパスを指定したとき警告する
            //デフォルトでTrueなので指定する必要はない
            ofd.CheckFileExists = true;
            //存在しないパスが指定されたとき警告を表示する
            //デフォルトでTrueなので指定する必要はない
            ofd.CheckPathExists = true;
            string ret = null;
            list = null;
            //ダイアログを表示する
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                ret = ofd.FileName;
                System.IO.Stream stream;
                stream = new System.IO.FileStream(ret, System.IO.FileMode.OpenOrCreate, System.IO.FileAccess.Read);
                DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(List<Item>));

                try
                {
                    list = (List<Item>)serializer.ReadObject(stream);
                }
                catch
                {
                    MessageBox.Show(
                        "ファイルが読み込めませんでした。",
                        "エラー",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                        );
                    ret = null;
                }
                finally
                {
                    stream.Close();
                }
            }

            return ret;
        }
    }
}
