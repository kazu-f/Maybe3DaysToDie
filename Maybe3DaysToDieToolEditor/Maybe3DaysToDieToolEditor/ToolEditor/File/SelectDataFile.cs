using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    delegate void FileCommand();
    class SelectDataFile
    {
        private OpenFileDialog openFile = new OpenFileDialog();
        private FileCommand ChangeMethod = null;
        private Button openFileButton = null;
        private TextBox filePathTextBox = null;
        private string fileExtension = null;

        /// <summary>
        /// ファイルを選択するためのダイアログを表示するボタンの処理をつける。
        /// </summary>
        /// <param name="button">ボタン</param>
        /// <param name="extension">選択するファイルの拡張子</param>
        public SelectDataFile(Button button, TextBox textBox, string extension, FileCommand method)
        {
            ChangeMethod = method;

            fileExtension = extension;
            //はじめのファイル名を指定する
            //はじめに「ファイル名」で表示される文字列を指定する
            //ofd.FileName = "新しいファイル.fmcr";
            //はじめに表示されるフォルダを指定する
            openFile.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            //[ファイルの種類]に表示される選択肢を指定する
            //指定しない（空の文字列）の時は、現在のディレクトリが表示される
            openFile.Filter = fileExtension + "ファイル(*." + fileExtension + ")|*." + fileExtension;
            //[ファイルの種類]ではじめに選択されるものを指定する
            openFile.FilterIndex = 1;
            //タイトルを設定する
            openFile.Title = "ファイルを選択してください";
            //ダイアログボックスを閉じる前に現在のディレクトリを復元するようにする
            openFile.RestoreDirectory = true;
            //存在しないファイルパスを指定したとき警告する
            //デフォルトでTrueなので指定する必要はない
            openFile.CheckFileExists = true;
            //存在しないパスが指定されたとき警告を表示する
            //デフォルトでTrueなので指定する必要はない
            openFile.CheckPathExists = true;

            //ファイル選択するボタンを設定。
            openFileButton = button;
            openFileButton.Click += new EventHandler(this.OpenFileDialog);
            //テキストボックスをセット。
            filePathTextBox = textBox;
        }

        private void OpenFileDialog(object sender, EventArgs e)
        {
            //ダイアログを表示する
            if (openFile.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFile.FileName;
                int index = filePath.IndexOf("Assets\\");
                //Assetsフォルダ内ではない。
                if (index == -1)
                {
                    MessageBox.Show(
                        "選択したファイルがAssetsフォルダ内ではありません。\n" +
                        "Assetsフォルダ内に存在するファイルを選択してください。",
                        "エラー",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                        );
                    return;
                }

                string fileName = filePath.Substring(index);
                filePathTextBox.Text = fileName;
                //コマンドを実行する。
                ChangeMethod();
            }
        }
    }
}

