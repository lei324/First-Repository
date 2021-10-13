package com.mingrisoft.iframe;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

import javax.swing.*;
import javax.swing.table.*;

import com.mingrisoft.*;
import com.mingrisoft.dao.Dao;
import com.mingrisoft.dao.model.TbSpinfo;

public class KuCunPanDian extends JInternalFrame {// 库存盘点内部窗体

	private final JTable table;// 表格模型
	private final JTextField pdsj = new JTextField();// “盘点时间”文本框
	private final JTextField pzs = new JTextField("0");// “品种数”文本框
	private JTextField czy = new JTextField();// “操作员”文本框
	private Date pdDate = new Date();// 盘点日期

	public KuCunPanDian() {// 库存盘点内部窗体的构造方法
		super();// 调用父类JInternalFrame的构造器
		setMaximizable(true);// 可以最大化
		setIconifiable(true);// 可以图标化
		setClosable(true);// 可以关闭
		getContentPane().setLayout(new GridBagLayout());// 设置库存盘点内部窗体的布局为网格布局
		setTitle("库存盘点");// 设置库存盘点内部窗体的标题
		setBounds(50, 50, 750, 400);// 设置设置库存盘点内部窗体的位置和宽高
		// “操作员”标签与“操作员”文本框
		setupComponet(new JLabel("操 作 员："), 0, 0, 1, 0, false);
		czy.setFocusable(false);
		czy.setText(MainFrame.getCzyStateLabel().getText());
		czy.setPreferredSize(new Dimension(120, 21));
		setupComponet(czy, 1, 0, 1, 0, true);
		// “盘点时间”标签与“盘点时间”文本框
		setupComponet(new JLabel("盘点时间："), 2, 0, 1, 0, false);
		pdsj.setFocusable(false);
		pdsj.setText(pdDate.toLocaleString());
		pdsj.setPreferredSize(new Dimension(180, 21));
		setupComponet(pdsj, 3, 0, 1, 1, true);
		// “品种数”标签与“品种数”文本框
		setupComponet(new JLabel("品 种 数："), 4, 0, 1, 0, false);
		pzs.setFocusable(false);
		pzs.setPreferredSize(new Dimension(80, 21));
		setupComponet(pzs, 5, 0, 1, 20, true);
		// 表格模型
		table = new JTable();
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		initTable();
		// 滚动面板
		JScrollPane scrollPanel = new JScrollPane(table);
		scrollPanel.setPreferredSize(new Dimension(700, 300));
		setupComponet(scrollPanel, 0, 2, 6, 1, true);
	}

	private void initTable() {// 初始化表格
		String[] columnNames = { "商品名称", "商品编号", "供应商", "产地", "单位", "规格", "单价", "数量", "包装", "盘点数量", "损益数量" };// 表头
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();// 获得表格默认模型
		tableModel.setColumnIdentifiers(columnNames);// 替换模型中的表头
		// 设置盘点字段只接收数字输入
		final JTextField pdField = new JTextField(0);// “盘点”文本框
		pdField.setEditable(false);// 设置“盘点”文本框不可编辑
		pdField.addKeyListener(new PanDianKeyAdapter(pdField));// 为“盘点”文本框添加盘点字段的按键监听器
		JTextField readOnlyField = new JTextField(0);// “只读”文本框
		readOnlyField.setEditable(false);// 设置“只读”文本框不可编辑

		DefaultCellEditor pdEditor = new DefaultCellEditor(pdField);// 构造使用“盘点”文本框为参数的盘点编辑器
		DefaultCellEditor readOnlyEditor = new DefaultCellEditor(readOnlyField);// 构造使用“只读”文本框为参数的只读编辑器
		for (int i = 0; i < columnNames.length; i++) {
			TableColumn column = table.getColumnModel().getColumn(i);// 获得表格中的每一列
			column.setCellEditor(readOnlyEditor);// 设置表格单元为只读格式
		}
		TableColumn pdColumn = table.getColumnModel().getColumn(9);// 盘点数量
		TableColumn syColumn = table.getColumnModel().getColumn(10);// 损益数量
		pdColumn.setCellEditor(pdEditor);// 为盘点数量设置盘点编辑器
		syColumn.setCellEditor(readOnlyEditor);// 为损益数量设置只读编辑器
		// 初始化表格内容
		List kcInfos = Dao.getKucunInfos();// 获得库存信息的集合
		for (int i = 0; i < kcInfos.size(); i++) {// 遍历库存信息的集合
			List info = (List) kcInfos.get(i);// 获得库存信息集合中的元素
			Item item = new Item();// 数据表公共类
			item.setId((String) info.get(0));// 经手人编号
			item.setName((String) info.get(1));// 经手人姓名
			TbSpinfo spinfo = Dao.getSpInfo(item);// 读取商品信息
			Object[] row = new Object[columnNames.length];// 创建长度为表头数组长度的数组
			if (spinfo.getId() != null && !spinfo.getId().isEmpty()) {// 如果商品编号不为空
				row[0] = spinfo.getSpname();// 添加行数据之“商品名称”
				row[1] = spinfo.getId();// 添加行数据之“商品编号”
				row[2] = spinfo.getGysname();// 添加行数据之“供应商名称”
				row[3] = spinfo.getCd();// 添加行数据之“产地”
				row[4] = spinfo.getDw();// 添加行数据之“商品计量单位”
				row[5] = spinfo.getGg();// 添加行数据之“商品规格”
				row[6] = info.get(2).toString();// 添加行数据之“单价”
				row[7] = info.get(3).toString();// 添加行数据之“数量”
				row[8] = spinfo.getBz();// 添加行数据之“包装”
				row[9] = 0;// 添加行数据之“盘点数量”
				row[10] = 0;// 添加行数据之“损益数量”
				tableModel.addRow(row);// 向表格默认模型中添加行数据
				String pzsStr = pzs.getText();// 获得“品种数”文本框中的文本内容
				int pzsInt = Integer.parseInt(pzsStr);// 将String型的“品种数”转换为int型
				pzsInt++;// “品种数”加1
				pzs.setText(pzsInt + "");// 设置“品种数”文本框中的文本内容
			}
		}
	}

	// 盘点字段的按键监听器
	private class PanDianKeyAdapter extends KeyAdapter {
		private final JTextField field;// “盘点”文本框

		private PanDianKeyAdapter(JTextField field) {// 区分同名变量，并为同名变量赋值
			this.field = field;
		}

		public void keyTyped(KeyEvent e) {// 键入某个键时
			if (("0123456789" + (char) 8).indexOf(e.getKeyChar() + "") < 0) {// 当前按下的按键没在0123456789的范围里
				e.consume();// 销毁当前没在key列表里的按键
			}
			field.setEditable(true);// 设置“盘点”文本框可编辑
		}

		public void keyReleased(KeyEvent e) {// 释放某个键时
			String pdStr = field.getText();// 获得“盘点”文本框的文本内容
			String kcStr = "0";// 声明String型的“库存数量”
			int row = table.getSelectedRow();// 获得被选中的行
			if (row >= 0) {// 如果表格模型中存在被选中的行
				kcStr = (String) table.getValueAt(row, 7);// 获得库存数量
			}
			try {
				int pdNum = Integer.parseInt(pdStr);// 将String型的“盘点数量”转换为int型
				int kcNum = Integer.parseInt(kcStr);// 将String型的“库存数量”转换为int型
				if (row >= 0) {// 如果表格模型中存在被选中的行
					table.setValueAt(kcNum - pdNum, row, 10);// 为表格中的“损益数量”赋值
				}
				if (e.getKeyChar() != 8)// 当前按下的按键没在0123456789的范围里
					field.setEditable(false);// “盘点”文本框不可编辑
			} catch (NumberFormatException e1) {
				field.setText("0");// 设置“盘点”文本框中的文本内容为0
			}
		}
	}

	// 设置组件位置并添加到容器中
	private void setupComponet(JComponent component, int gridx, int gridy, int gridwidth, int ipadx, boolean fill) {
		final GridBagConstraints gridBagConstrains = new GridBagConstraints();// 创建网格限制对象
		gridBagConstrains.gridx = gridx;// 设置组件位于网格的横向索引为gridx
		gridBagConstrains.gridy = gridy;// 设置组件位于网格的纵向索引为gridy
		gridBagConstrains.insets = new Insets(5, 1, 3, 5);// 组件彼此的间距
		if (gridwidth > 1)// 组件横跨网格数大于1
			gridBagConstrains.gridwidth = gridwidth;// 设置组件横跨网格数为gridwidth
		if (ipadx > 0)// 组件横向填充的大小大于0
			gridBagConstrains.ipadx = ipadx;// 设置组件横向填充的大小
		if (fill)// 组件占据空白区域
			gridBagConstrains.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
		getContentPane().add(component, gridBagConstrains);// 添加组件
	}
}
