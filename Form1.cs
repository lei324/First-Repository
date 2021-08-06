using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.IO;
using System.Drawing.Printing;
using System.Text.RegularExpressions;
using System.Xml;
//using Microsoft.Office.Interop.Word;



namespace 文档编辑器01
{
    public partial class Form1 : Form
    {
        string str;
        string s_FileName = "";//打开文件名
        int FindPosition = 0;//查找位置
        bool bSave = false;//文件是否保存
        StringReader streamToprint = null;//打印文件
        Font printFont;//打印所使用的字体
        int count = 0;
        String title = "Untitled";//保存打开文件的标题
        Encoding ec = Encoding.UTF8;//设置文本的格式
        public Form1()
        {
            InitializeComponent();
            pictureBox1.MouseWheel+=pictureBox1_MouseWheel;
        }
        /// <summary>
        /// 判断文件是否需要保存
        /// </summary>
        /// <returns></returns>
        public bool IfSaveOldFile()
        {
            bool ReturnValue = true;
            if (bSave)
            {
                System.Windows.Forms.DialogResult dr;
                string[] str = this.Text.Split('-');//划分字符串
                dr = MessageBox.Show("保存当前更改吗?","保存更改吗",MessageBoxButtons.YesNoCancel,MessageBoxIcon.Question);
                switch (dr)
                {
                    case System.Windows.Forms.DialogResult.Yes:
                        bSave = false;
                        if (s_FileName.Length != 0)
                        {
                            richTextBox1.SaveFile(s_FileName, RichTextBoxStreamType.PlainText);
                        }
                        else
                        {
                            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                            {
                                s_FileName = saveFileDialog1.FileName;
                                richTextBox1.SaveFile(s_FileName, RichTextBoxStreamType.PlainText);
                            }
                        }
                        ReturnValue = true;
                        break;
                    case System.Windows.Forms.DialogResult.No:
                        bSave = false;
                        ReturnValue = true;
                        break;
                    case System.Windows.Forms.DialogResult.Cancel:
                        ReturnValue = false;
                        break;

                }

            }
            return ReturnValue;
        }
        /// <summary>
        /// 查找字符串
        /// </summary>
        /// <param name="FindString">待查找的字符串</param>
        public void FindRichTextBoxString(string FindString)
        {
            //int count1 = 0;
            if (FindPosition >= richTextBox1.Text.Length)
            {
                MessageBox.Show(FindString+"共计" + count+"个");
                MessageBox.Show("已到文本底部,再次查找将从文本开始处查找","提示",MessageBoxButtons.OK);
                FindPosition = 0;
                return;
            }
            FindPosition = richTextBox1.Find(FindString, FindPosition, RichTextBoxFinds.MatchCase);
            if (FindPosition == -1)
            {
                MessageBox.Show(FindString + "共计" + count+ "个");
                MessageBox.Show("未匹配到字符串,再次查找将从文本开始处查找", "提示", MessageBoxButtons.OK);
                FindPosition = 0;
            }
            else
            {
                count++;
                richTextBox1.Focus();
                FindPosition += FindString.Length;
            }
            //MessageBox.Show(FindString + "共计" + count + "个");
        }
        /// <summary>
        ///替换字符串
        /// </summary>
        /// <param name="ReplaceString">待替换的字符串参数</param>
        public void ReplaceRichTextBoxString(string ReplaceString)
        {
            if (richTextBox1.SelectedText.Length != 0)
                richTextBox1.SelectedText = ReplaceString;
        }
        /// <summary>
        /// 自动换行
        /// </summary>
        public void WrapLine()
        {
           // if(Count()%8==0)
           // if (Count() % 80 == 0)
            {
                this.richTextBox1.WordWrap = !(this.richTextBox1.WordWrap);
            }
        }
        /// <summary>
        /// 如果启用自动换行则状态栏不可用
        /// </summary>
        public void Cleation()
        {
            if(自动换行ToolStripMenuItem.Checked==false)
                {
                    状态栏ToolStripMenuItem.Enabled=true;
                }
            else
            {
                状态栏ToolStripMenuItem.Enabled=false;
            }
        }
       
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void 自动换行ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            自动换行ToolStripMenuItem.Checked = !自动换行ToolStripMenuItem.Checked;
            this.Cleation();
            this.WrapLine();
        }
        /// <summary>
        /// 选中内容则激活相应按钮
        /// 否则保持不可用
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void richTextBox1_SelectionChanged(object sender, EventArgs e)
        {
            if (richTextBox1.SelectedText == string.Empty)
            {
                //没有选择文字
                //编辑下的复制,粘贴,删除不可用
                复制CToolStripMenuItem.Enabled = false;
                剪切TToolStripMenuItem.Enabled = false;
                删除ToolStripMenuItem.Enabled = false;
                //工具栏下的复制,剪切不可用
                CutToolStripButton.Enabled = false;
                CopyToolStripButton.Enabled = false;
                //弹出菜单下的复制,粘贴,删除不可用
                CutToolStripMenuItem.Enabled = false;
                CopyToolStripMenuItem.Enabled = false;
                DelToolStripMenuItem.Enabled = false;
            }
            else
            {
                复制CToolStripMenuItem.Enabled = true;
                剪切TToolStripMenuItem.Enabled = true;
                删除ToolStripMenuItem.Enabled = true;
                //工具栏下的复制,剪切可用
                CutToolStripButton.Enabled = true;
                CopyToolStripButton.Enabled = true;
                //弹出菜单下的复制,粘贴,删除可用
                CutToolStripMenuItem.Enabled = true;
                CopyToolStripMenuItem.Enabled = true;
                DelToolStripMenuItem.Enabled = true;
            }
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            bSave = true;
            //内容更改后激发撤销和重复两按钮
            撤消UToolStripMenuItem.Enabled = true;
            重复RToolStripMenuItem.Enabled = true;

        }

        private void richTextBox1_Click(object sender, EventArgs e)
        {
            int ln = richTextBox1.GetLineFromCharIndex(richTextBox1.SelectionStart);
            int col = richTextBox1.SelectionStart - richTextBox1.GetFirstCharIndexFromLine(ln);
            this.toolStripStatusLabel1.Text = "第" +(ln + 1) +"行"+",第" + col+"列";
        }

        /// <summary>
        /// 打印的BeginPrint事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void printDocument1_BeginPrint(object sender, PrintEventArgs e)
        {
            printFont = richTextBox1.Font;
            streamToprint = new StringReader(richTextBox1.Text);
        }

        private void printDocument1_EndPrint(object sender, PrintEventArgs e)
        {
            if (streamToprint != null)
                streamToprint.Close();
        }

        private void printDocument1_PrintPage(object sender, PrintPageEventArgs e)
        {
            float linesPerpage = 0;
            float yPos = 0;
            int count = 0;
            float leftMargin = e.MarginBounds.Left;
            float topMargin = e.MarginBounds.Top;
            string line = null;
            linesPerpage = e.MarginBounds.Height / printFont.GetHeight(e.Graphics);
            while (count < linesPerpage && ((line = streamToprint.ReadLine()) != null))
            {
                yPos = topMargin + (count * printFont.GetHeight(e.Graphics));
                e.Graphics.DrawString(line, printFont, Brushes.Black, leftMargin, yPos, new StringFormat());
                count++;
            }
            if (line != null)
                e.HasMorePages = true;
            else
                e.HasMorePages = false;

        }
        //菜单事件
        /// <summary>
        /// 是否选中,判读是否控件可用
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            if (richTextBox1.SelectionLength > 0)//文本选中
            {
                CutToolStripMenuItem.Enabled = true;
                CopyToolStripMenuItem.Enabled = true;
                DelToolStripMenuItem.Enabled = true;
            }
            else
            {
                CutToolStripMenuItem.Enabled = false;
                CopyToolStripMenuItem.Enabled = false;
                DelToolStripMenuItem.Enabled = false;
            }
            if (Clipboard.ContainsText())//剪切板中有内容
            {
                粘贴PToolStripMenuItem.Enabled = true;
                PasteToolStripButton.Enabled = true;
                PasteToolStripMenuItem.Enabled = true;
            }
            else
            {
                粘贴PToolStripMenuItem.Enabled = false;
                PasteToolStripButton.Enabled = false;
                PasteToolStripMenuItem.Enabled = false;
            }
        }

        private void CutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Cut();
        }

        private void CopyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Copy();
        }

        private void PasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Paste();
        }

        private void DelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectedText = "";
        }

        private void 新建NToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!IfSaveOldFile())
                return;
            richTextBox1.Text = "";//清空面板
            s_FileName = "";//清空文件名
            
        }
        /// <summary>
        /// 打开已有的文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 打开OToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!IfSaveOldFile())
                return;
            OpenFileDialog saveFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "文本文档(*.txt)|*.txt|所有文件(*.*)|*.*|docx文档(*.docx)|*.docx|RTF文件|*.rtf";
           /* openFileDialog1.FilterIndex = 1;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                s_FileName = openFileDialog1.FileName;
                richTextBox1.LoadFile(openFileDialog1.FileName,RichTextBoxStreamType.PlainText);
            }
            
          /*  openFileDialog1.Filter = "文本文件|*.txt;*.html;*.docx;*.doc;*.rtf|所有文件|*.*"; //文件打开的过滤器
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                title = openFileDialog1.FileName;
                this.Text = title;                  //显示打开的文件名
                richTextBox1.Modified = false;
                string ext = title.Substring(title.LastIndexOf(".") + 1);//获取文件格式
                ext = ext.ToLower();
                FileStream fs = new FileStream(title, FileMode.Open, FileAccess.Read);
                StreamReader sr = new StreamReader(fs, ec);
                if (ext == "rtf")  //如果后缀是 rtf 加载文件进来
                {
                    richTextBox1.LoadFile(title, RichTextBoxStreamType.RichText);
                }
                else
                {
                    richTextBox1.Text = sr.ReadToEnd();
                }
                fs.Close();
                sr.Close();
            }
            */
           /*openFileDialog1.Filter = "文本文件(*.txt)|*.txt|RTF文件|*.rtf|所有文件(*.*)|*.*";*/
            openFileDialog1.FilterIndex = 1;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                s_FileName = openFileDialog1.FileName;
                try
                {
                    string filename = openFileDialog1.FileName;
                    string fileext = new System.IO.FileInfo(filename).Extension;
                    switch (fileext.ToLower())
                    {
                        case ".txt":
                            this.richTextBox1.LoadFile(filename, RichTextBoxStreamType.PlainText);
                            break;
                        case ".rtf":
                            this.richTextBox1.LoadFile(filename, RichTextBoxStreamType.RichText);
                            break;
                    }
                }
                catch (Exception)
                {
                    MessageBox.Show("Oh，您的打开不成功！");
                }
            }

        }

        private void 保存SToolStripMenuItem_Click(object sender, EventArgs e)
        {
           if (s_FileName.Length != 0)
            {
                bSave = false;
                richTextBox1.SaveFile(s_FileName, RichTextBoxStreamType.PlainText);
            }//文件已经保存过
            else
            {
                另存为AToolStripMenuItem_Click(sender,e);//调用另存为函数
            }
            
            /*if (title == "Untitled")//如果是不是打开文件然后编辑的话 点击保存就相当于另存为咯
                另存为AToolStripMenuItem_Click(sender, e);//这个另存为的按钮是在顶部的菜单栏
            else
            {
                string ext = title.Substring(title.LastIndexOf(".") + 1);
                ext = ext.ToLower();
                if (ext == "rtf")//按照不同的格式保存文件
                    richTextBox1.SaveFile(title, RichTextBoxStreamType.RichText);
                else if (ext == "doc" || ext == "txt")
                    richTextBox1.SaveFile(title, RichTextBoxStreamType.PlainText);
                else if (ext == "uni")
                    richTextBox1.SaveFile(title, RichTextBoxStreamType.UnicodePlainText);
                else
                    richTextBox1.SaveFile(title, RichTextBoxStreamType.PlainText);
                richTextBox1.Modified = false;
            }
             */
        }

        private void 另存为AToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            openFileDialog1.Filter = "文本文档(*.txt)|*.txt|所有文件(*.*)|*.*|docx文档(*.docx)|*.docx";
            openFileDialog1.FilterIndex = 1;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                s_FileName = saveFileDialog1.FileName;
                richTextBox1.SaveFile(saveFileDialog1.FileName, RichTextBoxStreamType.PlainText);
                bSave = false;
            }
             
             /*if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                title = saveFileDialog1.FileName;
                this.Text = title;
                switch (saveFileDialog1.FilterIndex)
                {
                    case 1:
                        richTextBox1.SaveFile(title, RichTextBoxStreamType.RichText);
                        break;
                    case 2:
                        richTextBox1.SaveFile(title, RichTextBoxStreamType.PlainText);
                        break;
                    case 3:
                        richTextBox1.SaveFile(title, RichTextBoxStreamType.UnicodePlainText);
                        break;
                    default:
                        richTextBox1.SaveFile(title, RichTextBoxStreamType.PlainText);
                        break;
                }
                richTextBox1.Modified = false;
            }
              */
        }

        private void 页面设置UToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pageSetupDialog1.Document = printDocument1;
            pageSetupDialog1.ShowDialog();
        }

        private void 打印预览VToolStripMenuItem_Click(object sender, EventArgs e)
        {
            printPreviewDialog1.Document = printDocument1;
            printPreviewDialog1.ShowDialog();
        }

        private void 打印PToolStripMenuItem_Click(object sender, EventArgs e)
        {
            printDialog1.Document = printDocument1;
            if (printDialog1.ShowDialog(this) == DialogResult.OK)
                printDocument1.Print();
        }

        private void 退出XToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void 撤消UToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Undo();
        }

        private void 重复RToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Redo();
        }

        private void 剪切TToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Cut();
        }

        private void 复制CToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Copy();
        }

        private void 粘贴PToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Paste();
        }

        private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectedText = "";
        }
        private void 查找ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FindPosition = 0;
            count = 0;
            FormFindReplace FindReplaceDialog = new FormFindReplace(this);
            FindReplaceDialog.Show();
           

        }


        private void 全选AToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
        }

        private void 替换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FindPosition = 0;
            FormFindReplace FindReplaceDialog = new FormFindReplace(this);
            FindReplaceDialog.Show();
        }

        private void 字体ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fontDialog1.ShowDialog() == DialogResult.OK)
                richTextBox1.SelectionFont = fontDialog1.Font;
        }

        /// <summary>
        /// 选中时状态栏可见,否则不可见
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 状态栏ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            状态栏ToolStripMenuItem.Checked = !状态栏ToolStripMenuItem.Checked;
            if (状态栏ToolStripMenuItem.Checked)
                statusStrip1.Visible = true;
            else
                statusStrip1.Visible = false;
        }

      /*  private void 图片CToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PictureBox pb = new PictureBox();
           // this.richTextBox1.Controls.Add(pb);
           // string path[]=Directory.GetFiles();
            openFileDialog1.Filter = "bmp文件(*.bmp)|*.bmp|jpg文件(*.jpg)|*.jpg|ico文件(*.ico)|*.ico|png文件(*.png)|*.png";
            openFileDialog1.Title = "插入图片";
            openFileDialog1.FilterIndex = 2;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
               
                Bitmap bmp = new Bitmap(openFileDialog1.FileName);
                Clipboard.SetDataObject(bmp, false);
                if (richTextBox1.CanPaste(DataFormats.GetFormat(DataFormats.Bitmap)))
                    richTextBox1.Paste();
            }

        }
        /*public static Bitmap GetThumbnail(Bitmap bmp, int width, int height)
        {
            if (width == 0)
            {
                width = height * bmp.Width / bmp.Height;
            }
            if (height == 0)
            {
                height = width * bmp.Height / bmp.Width;
            }
            Image imgSource = bmp;
            Bitmap outBmp = new Bitmap(width, height);
            Graphics g = Graphics.FromImage(outBmp);
            g.Clear(Color.Transparent);
            // 设置画布的描绘质量   
            g.CompositingQuality = CompositingQuality.HighQuality;
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            g.DrawImage(imgSource, new Rectangle(0, 0, width, height + 1), 0, 0, imgSource.Width, imgSource.Height, GraphicsUnit.Pixel);

            g.Dispose();
            imgSource.Dispose();
            bmp.Dispose();
            return outBmp;
        }*/


        private void NewToolStripButton_Click(object sender, EventArgs e)
        {
            if (!IfSaveOldFile())
                return;
            richTextBox1.Text = "";//清空面板
            s_FileName = "";//清空文件名
        }

        private void OpenToolStripButton_Click(object sender, EventArgs e)
        {
            if (!IfSaveOldFile())
                return;
            OpenFileDialog saveFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "文本文档(*.txt)|*.txt|所有文件(*.*)|*.*";
            openFileDialog1.FilterIndex = 1;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                s_FileName = openFileDialog1.FileName;
                richTextBox1.LoadFile(openFileDialog1.FileName, RichTextBoxStreamType.PlainText);
            }
        }

        private void SaveToolStripButton_Click(object sender, EventArgs e)
        {
            保存SToolStripMenuItem_Click(sender, e);
        }

        private void PrintToolStripButton_Click(object sender, EventArgs e)
        {
            打印PToolStripMenuItem_Click(sender,e);
        }

        private void CutToolStripButton_Click(object sender, EventArgs e)
        {
            剪切TToolStripMenuItem_Click(sender,e);
        }

        private void CopyToolStripButton_Click(object sender, EventArgs e)
        {
            复制CToolStripMenuItem_Click(sender,e);
        }

        private void PasteToolStripButton_Click(object sender, EventArgs e)
        {
            粘贴PToolStripMenuItem_Click(sender,e);
        }

        private void HelpToolStripButton_Click(object sender, EventArgs e)
        {

        }

        private void BoldToolStripButton_Click(object sender, EventArgs e)
        {
            Font oldFont;
            Font newFont;
            oldFont = richTextBox1.SelectionFont;
            if (oldFont.Bold)
                newFont = new Font(oldFont,oldFont.Style&~FontStyle.Bold);
            else
                newFont=new Font(oldFont,oldFont.Style|FontStyle.Bold);
            richTextBox1.SelectionFont = newFont;
            richTextBox1.Focus();
        }

        private void ItalicToolStripButton_Click(object sender, EventArgs e)
        {
            Font oldFont;
            Font newFont;
            oldFont = richTextBox1.SelectionFont;
            if (oldFont.Italic)
                newFont = new Font(oldFont, oldFont.Style & ~FontStyle.Italic);
            else
                newFont = new Font(oldFont,oldFont.Style|FontStyle.Italic);
            richTextBox1.SelectionFont = newFont;
            richTextBox1.Focus();
        }

        private void UnderLineToolStripButton_Click(object sender, EventArgs e)
        {
            Font oldFont;
            Font newFont;
            oldFont = richTextBox1.SelectionFont;
            if (oldFont.Underline)
                newFont = new Font(oldFont, oldFont.Style & ~FontStyle.Underline);
            else
                newFont = new Font(oldFont, oldFont.Style | FontStyle.Underline);
            richTextBox1.SelectionFont = newFont;
            richTextBox1.Focus();
        }

        private void FontColorToolStripButton_Click(object sender, EventArgs e)
        {
            ColorDialog colorDialog1 = new ColorDialog();
            colorDialog1.ShowDialog();
            richTextBox1.SelectionColor = colorDialog1.Color;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!IfSaveOldFile())
                e.Cancel = true;
        }

        private void toolStripStatusLabel2_Click(object sender, EventArgs e)
        {
            String s;
            int a1=0;
            int a2=0;
            int a3=0;
            int a4=0;
            int a5=0;
            s = richTextBox1.Text ;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] <= '9' && s[i] >= '0')
                    a4++;
                if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'z')
                    a1++;
                if (s[i] == ' ')
                    a2++;
                else
                    a5++;
            }
            a3 = ChineseCount(s);
            this.toolStripStatusLabel2.Text=("字数:"+Count()+"字母数:"+a1+" 空格数:"+a2+"汉字数:"+a3);
        }
        public int ChineseCount(string strText)
        {
            byte[] byts = System.Text.Encoding.GetEncoding("gb2312").GetBytes(strText);
            return byts.Length - strText.Length;
        }
        public int Count()
        {
            String s;
            int a1 = 0;
            int a2 = 0;
            int a3 = 0;
            int a4 = 0;
            int a5 = 0;
            s = richTextBox1.Text;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] <= '9' && s[i] >= '0')
                    a4++;
                if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'z')
                    a1++;
                if (s[i] == ' ')
                    a2++;
                else
                    a5++;
            }
            int a = a1 + a2 + a3 + a4 + a5;
            return a;
        }

        private void pdfCToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void xmlSToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 索引IToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 左对齐ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.richTextBox1.SelectionAlignment = HorizontalAlignment.Left;
        }

        private void 右对齐ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.richTextBox1.SelectionAlignment = HorizontalAlignment.Right;
        }

        private void 居中对齐ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.richTextBox1.SelectionAlignment = HorizontalAlignment.Center;
        }

        private void 选项OToolStripMenuItem_Click(object sender, EventArgs e)
        {
          /*  Document document = new Document();

            //添加section到文档
            Section section = document.AddSection();
            //添加段落section
            Paragraph paragraph = section.AddParagraph();

            //添加指定大小的文本框到段落
            TextBox textbox = paragraph.AppendTextBox(300, 100);

            //添加文本到文本，设置文本格式
            Paragraph textboxParagraph = textbox.Body.AddParagraph();
            TextRange textboxRange = textboxParagraph.AppendText("Sample Report 1");
            textboxRange.CharacterFormat.FontName = "Arial";

            //插入表格到文本框
            Table table = textbox.Body.AddTable(true);
            //指定表格行数、列数
            table.ResetCells(4, 4);
            //实例化数组内容
            string[,] data = new string[,]  
            {  
               {"Name","Age","Gender","ID" },  
               {"John","28","Male","0023" },  
               {"Steve","30","Male","0024" },  
               {"Lucy","26","female","0025" }  
            };

            //将数组内容添加到表格 
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    TextRange tableRange = table[i, j].AddParagraph().AppendText(data[i, j]);
                    tableRange.CharacterFormat.FontName = "Arial";
                }
            }

            //应用表格样式
            table.ApplyStyle(DefaultTableStyle.MediumGrid3Accent1);

            //保存并打开文档
            document.SaveToFile("Output.docx", FileFormat.Docx2013);
            System.Diagnostics.Process.Start("Output.docx");*/
        
        }


        private void AddPicControl()
        {
            PictureBox pictureBox1 = new PictureBox();
            string name;
            name = pictureBox1.Name;
            pictureBox1.BorderStyle = BorderStyle.FixedSingle;//边框样式：单线边
            pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;//设置图像SizeMode=Zoom
            pictureBox1.Cursor = Cursors.Hand;//鼠标悬浮样式：小手
            //向容器中添加一个图像控件
            //pic.Visible = false;
            
            this.richTextBox1.Controls.Add(pictureBox1);
            
        }

        private void 添加图片ToolStripMenuItem_Click(object sender, EventArgs e)
        {

           
            OpenFileDialog OpenFileDialog = new OpenFileDialog();
            OpenFileDialog.Filter = "jpg文件(*.jpg)|*.jpg|bmp文件(*.bmp)|*.bmp|png文件(*.png)|*.png";
            if (OpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                this.pictureBox1.Image = System.Drawing.Image.FromFile(OpenFileDialog.FileName);
                str = OpenFileDialog.FileName;
                
            }
        }

       /* private void 图片ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PictureBox pb = new PictureBox();
            // this.richTextBox1.Controls.Add(pb);
            // string path[]=Directory.GetFiles();
            openFileDialog1.Filter = "bmp文件(*.bmp)|*.bmp|jpg文件(*.jpg)|*.jpg|ico文件(*.ico)|*.ico|png文件(*.png)|*.png";
            openFileDialog1.Title = "插入图片";
            openFileDialog1.FilterIndex = 2;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {

                Bitmap bmp = new Bitmap(openFileDialog1.FileName);
                Clipboard.SetDataObject(bmp, false);
                if (richTextBox1.CanPaste(DataFormats.GetFormat(DataFormats.Bitmap)))
                    richTextBox1.Paste();
                
            }
        }
        */
        private void 图片翻转ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                Color c;
                int red, green, blue;
                Bitmap before = new Bitmap(pictureBox1.Image);
                Bitmap after = new Bitmap(before);
                for (int i = 0; i < before.Width; i++)
                {
                    for (int j = 0; j < before.Height; j++)
                    {
                        c = before.GetPixel(i, j);
                        red = c.R;
                        green = c.G;
                        blue = c.B;
                        Color cc = Color.FromArgb(red, green, blue);
                        after.SetPixel(i, before.Height - j - 1, cc);
                    }
                }
                this.pictureBox1.Image = after;
            }
            catch
            {
                MessageBox.Show("未加载图片","警告",MessageBoxButtons.OK);
            }
        }

        private void 图片还原ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                Color c;
                int red, green, blue;
                Bitmap before = new Bitmap(pictureBox1.Image);
                Bitmap after = new Bitmap(before);
                for (int i = 0; i < before.Width; i++)
                {
                    for (int j = 0; j < before.Height; j++)
                    {
                        c = before.GetPixel(i, j);
                        red = c.R;
                        green = c.G;
                        blue = c.B;
                        Color cc = Color.FromArgb(red, green, blue);
                        after.SetPixel(i, before.Height - j - 1, cc);
                    }
                }
                this.pictureBox1.Image = after;
            }
            catch
            {
                MessageBox.Show("未加载图片", "警告", MessageBoxButtons.OK);
            }
        }
        int x;
        int y;
        bool MoveFlag;
        private void pictureBox1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta >= 0)
            {
                pictureBox1.Width = (int)(pictureBox1.Width * 1.1);//因为Widthh和Height都是int类型，所以要强制转换一下-_-||
                pictureBox1.Height = (int)(pictureBox1.Height * 1.1);
            }
            else
            {
                pictureBox1.Width = (int)(pictureBox1.Width * 0.9);
                pictureBox1.Height = (int)(pictureBox1.Height * 0.9);
            }
        }

        private void pictureBox1_MouseDown_1(object sender, MouseEventArgs e)
        {
            MoveFlag = true;
            x = e.X;
            y = e.Y;
        }

        private void pictureBox1_MouseMove_1(object sender, MouseEventArgs e)
        {
            if (MoveFlag)
            {
                pictureBox1.Left += Convert.ToInt16(e.X - x);
                pictureBox1.Top += Convert.ToInt16(e.Y - y);
            }
        }

        private void pictureBox1_MouseUp_1(object sender, MouseEventArgs e)
        {
            MoveFlag = false;
        }

        private void pictureBox1_MouseEnter_1(object sender, EventArgs e)
        {
            pictureBox1.Focus();
        }

       

        private void richTextBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

       
    }
}
