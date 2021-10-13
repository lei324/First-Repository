package com.mingrisoft.iframe;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;

import com.mingrisoft.dao.Dao;
import com.mingrisoft.dao.model.TbJsr;

public class XiaoShouPaiHang extends JInternalFrame {// 销售排行内部窗体
	
	private JButton okButton;// “确定”按钮
	private JComboBox month;// “月”下拉列表
	private JComboBox year;// “年”下拉列表
	private JTable table;// 表格模型
	private JComboBox operation;// “条件运算”下拉列表
	private JComboBox condition;// “条件内容”下拉列表
	private TbJsr user;// 经手人信息
	private DefaultTableModel dftm;// 默认表格模型的实例对象
	private Calendar date = Calendar.getInstance();// “日期”对象
	
	public XiaoShouPaiHang() {// 销售排行内部窗体的构造方法
		setIconifiable(true);// 可以图标化
		setClosable(true);// 可以关闭窗体
		setTitle("销售排行");// 设置销售排行内部窗体的标题
		getContentPane().setLayout(new GridBagLayout());// 设置销售排行内部窗体的布局为网格布局
		setBounds(100, 100, 700, 375);// 设置销售排行内部窗体的位置和宽高
		// “对”标签
		final JLabel label_1 = new JLabel();
		label_1.setText("对");
		final GridBagConstraints gridBagConstraints_8 = new GridBagConstraints();
		gridBagConstraints_8.anchor = GridBagConstraints.EAST;
		gridBagConstraints_8.gridy = 0;
		gridBagConstraints_8.gridx = 0;
		getContentPane().add(label_1, gridBagConstraints_8);
		// “年”下拉列表
		year = new JComboBox();
		for (int i = 1981, j = 0; i <= date.get(Calendar.YEAR) + 1; i++, j++) {// 利用循环，向“年”下拉列表中添加1981~(当前时间年份+1)选项
			year.addItem(i);
			if (i == date.get(Calendar.YEAR))// 当前时间年份
				year.setSelectedIndex(j);// 选择索引 j 处的列表项
		}
		year.setPreferredSize(new Dimension(100, 21));
		setupComponet(year, 1, 0, 1, 90, true);
		// “年”标签
		setupComponet(new JLabel("年"), 2, 0, 1, 1, false);
		// “月”下拉列表
		month = new JComboBox();
		for (int i = 1; i <= 12; i++) {// 利用循环，向“月”下拉列表中添加1~12
			month.addItem(String.format("%02d", i));// 格式化月份
			if (date.get(Calendar.MONTH) == i)// 当前时间月份
				month.setSelectedIndex(i - 1);// 选择索引 (i - 1) 处的列表项
		}
		month.setPreferredSize(new Dimension(100, 21));
		setupComponet(month, 3, 0, 1, 30, true);
		// “月份的销售信息，按”标签
		setupComponet(new JLabel(" 月份的销售信息，按"), 4, 0, 1, 1, false);
		condition = new JComboBox();
		condition.setModel(new DefaultComboBoxModel(new String[]{"金额", "数量"}));
		setupComponet(condition, 5, 0, 1, 30, true);
		// “进行”标签
		setupComponet(new JLabel(" 进行"), 6, 0, 1, 1, false);
		// “条件运算”下拉列表
		operation = new JComboBox();
		operation.setModel(new DefaultComboBoxModel(new String[]{"升序排列", "降序排列"}));
		setupComponet(operation, 7, 0, 1, 30, true);
		// “确定”按钮
		okButton = new JButton();
		okButton.addActionListener(new OkAction());// 点击“确定”按钮后，发生的事件
		setupComponet(okButton, 8, 0, 1, 1, false);
		okButton.setText("确定");
		// 滚动面板
		final JScrollPane scrollPane = new JScrollPane();
		final GridBagConstraints gridBagConstraints_6 = new GridBagConstraints();
		gridBagConstraints_6.weighty = 1.0;
		gridBagConstraints_6.anchor = GridBagConstraints.NORTH;
		gridBagConstraints_6.insets = new Insets(0, 10, 5, 10);
		gridBagConstraints_6.fill = GridBagConstraints.BOTH;
		gridBagConstraints_6.gridwidth = 9;
		gridBagConstraints_6.gridy = 1;
		gridBagConstraints_6.gridx = 0;
		getContentPane().add(scrollPane, gridBagConstraints_6);
		// 表格模型
		table = new JTable();
		table.setEnabled(false);// 设置表格模型无法响应用户输入
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);// 不自动调整列的宽度，使用滚动条
		dftm = (DefaultTableModel) table.getModel();// 获得默认的表格模型
		String[] tableHeads = new String[]{"商品编号", "商品名称", "销售金额", "销售数量",
				"简称", "产地", "单位", "规格", "包装", "批号", "批准文号","简介","供应商"};// 表头
		dftm.setColumnIdentifiers(tableHeads);// 设置默认表格模型的表头
		scrollPane.setViewportView(table);// 把表格模型添加到滚动面板中
	}
	// 更改表格数据
	private void updateTable(Iterator iterator) {
		int rowCount = dftm.getRowCount();// 获得默认的表格模型中的行数
		for (int i = 0; i < rowCount; i++) {
			dftm.removeRow(0);// 移除表格模型中的第一行
		}
		while (iterator.hasNext()) {// 销售信息的集合中仍有元素可以迭代
			Vector vector = new Vector();// 创建向量
			List view = (List) iterator.next();// 获得迭代的下一个集合
			Vector row = new Vector(view);// 构造一个包含指定集合view中的元素的向量
			int rowSize = row.size();// 获得向量中的元素个数
			for(int i = rowSize - 2; i < rowSize; i++){// 通过循环获得向量中最后两个元素的索引
				Object colValue = row.get(i);// 获得向量中指定索引处的元素
				row.remove(i);// 移除此向量中指定索引处的元素
				row.insertElementAt(colValue, 2);// 将向量中指定索引处的元素插入到指定的索引为2的位置上
			}
			vector.addAll(row);// 将迭代后集合中所有的元素添加到此向量中
			dftm.addRow(vector);// 向默认的表格模型中添加行数据
		}
	}
	// 设置组件位置并添加到容器中
	private void setupComponet(JComponent component, int gridx, int gridy,
			int gridwidth, int ipadx, boolean fill) {
		final GridBagConstraints gridBagConstrains = new GridBagConstraints();// 创建网格限制对象
		gridBagConstrains.gridx = gridx;// 设置组件位于网格的横向索引为gridx
		gridBagConstrains.gridy = gridy;// 设置组件位于网格的纵向索引为gridy
		gridBagConstrains.insets = new Insets(5, 1, 3, 1);// 组件彼此的间距
		if (gridwidth > 1)// 组件横跨网格数大于1
			gridBagConstrains.gridwidth = gridwidth;// 设置组件横跨网格数为gridwidth
		if (ipadx > 0)// 组件横向填充的大小大于0
			gridBagConstrains.ipadx = ipadx;// 设置组件横向填充的大小
		if (fill)
			gridBagConstrains.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
		getContentPane().add(component, gridBagConstrains);// 添加组件
	}
	// 点击“确定”按钮后，发生的事件
	private final class OkAction implements ActionListener {
		public void actionPerformed(final ActionEvent e) {
			List list = null;// 声明符合条件的“商品信息”集合
			String strMonth = (String) month.getSelectedItem();// 获得被选中的月份
			String date = year.getSelectedItem() + "-" + strMonth;// 获得含有年、月的日期
			String con = condition.getSelectedIndex() == 0 ? "sumje " : "sl ";// 判断“条件内容”下拉列表被选中的是“金额”还是“数量”
			int oper = operation.getSelectedIndex();// 获得“条件运算”下拉列表被选中的选项索引
			String opstr = oper == 0 ? " asc" : " desc";// 判断“条件运算”下拉列表被选中的是“升序排列”还是“降序排列”
			String sql1 = "select spid,sum(sl)as sl,sum(sl*dj) as sumje from v_sellView "
						+ "where left (xsdate,7)='" + date + "' group by spid";// 获得符合年、月的销售商品信息的SQL语句
			String queryStr = "select * from tb_spinfo s inner join (" + sql1
							+ ") as sp on s.id=sp.spid order by " + con + opstr;// 获得销售排行的SQL语句
			list = Dao.findForList(queryStr);// 获得符合条件的“商品信息”集合
			Iterator iterator = list.iterator();// 获得符合条件的“商品信息”集合的迭代器
			updateTable(iterator);// 更改表格数据
		}
	}
}
