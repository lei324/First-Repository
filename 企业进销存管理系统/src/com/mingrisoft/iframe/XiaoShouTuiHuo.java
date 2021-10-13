package com.mingrisoft.iframe;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import java.util.*;
import java.util.Date;
import java.util.List;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

import com.mingrisoft.*;
import com.mingrisoft.dao.Dao;
import com.mingrisoft.dao.model.*;

public class XiaoShouTuiHuo extends JInternalFrame {// 销售退货内部窗体
	
	private final JTable table;// 表格模型
	private final JTextField thsj = new JTextField();// “退货时间”文本框
	private JComboBox jsr = null;// “经手人”下拉列表
	private final JComboBox jsfs = new JComboBox();// “结算方式”下拉列表
	private final JTextField lian = new JTextField();// “联系人”文本框
	private final JComboBox kehu = new JComboBox();// “客户”下拉列表
	private final JTextField piaoHao = new JTextField();// “销退票号”文本框
	private final JTextField pzs = new JTextField("0");// “品种数量”文本框
	private final JTextField hpzs = new JTextField("0");// “货品总数”文本框
	private final JTextField hjje = new JTextField("0");// “合计金额”文本框
	private final JTextField ysjl = new JTextField();// “验收结论”文本框
	private final JTextField czy = new JTextField();// “操作员”文本框
	private Date thsjDate;// 退货日期
	private JComboBox sp;// “商品”下拉列表

	public XiaoShouTuiHuo() {// 销售退货内部窗体的构造方法
		super();// 调用父类JInternalFrame的构造器
		setMaximizable(true);// 可以最大化
		setIconifiable(true);// 可以图标化
		setClosable(true);// 可以关闭销售单内部窗体
		getContentPane().setLayout(new GridBagLayout());// 设置销售退货内部窗体的布局为网格布局
		setTitle("销售退货");// 设置销售退货内部窗体的标题
		setBounds(50, 50, 700, 400);// 设置销售退货内部窗体的位置和宽高
		// “销退票号”标签和“销退票号”文本框
		setupComponet(new JLabel("销退票号："), 0, 0, 1, 0, false);
		piaoHao.setFocusable(false);
		setupComponet(piaoHao, 1, 0, 1, 140, true);
		// “客户”标签和“客户”下拉列表
		setupComponet(new JLabel("客户："), 2, 0, 1, 0, false);
		kehu.setPreferredSize(new Dimension(160, 21));
		kehu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				doKhSelectAction();// “客户”下拉列表的选择事件
			}
		});
		setupComponet(kehu, 3, 0, 1, 1, true);
		// “联系人”标签和“联系人”文本框
		setupComponet(new JLabel("联系人："), 4, 0, 1, 0, false);
		lian.setFocusable(false);
		lian.setPreferredSize(new Dimension(80, 21));
		setupComponet(lian, 5, 0, 1, 0, true);
		// “结算方式”标签和“结算方式”下拉列表
		setupComponet(new JLabel("结算方式："), 0, 1, 1, 0, false);
		jsfs.addItem("现金");
		jsfs.addItem("支票");
		jsfs.setEditable(true);
		setupComponet(jsfs, 1, 1, 1, 1, true);
		// “退货时间”标签和“退货时间”文本框
		setupComponet(new JLabel("退货时间："), 2, 1, 1, 0, false);
		thsj.setFocusable(false);
		setupComponet(thsj, 3, 1, 1, 1, true);
		// “经手人”标签和“经手人”下拉列表
		setupComponet(new JLabel("经手人："), 4, 1, 1, 0, false);
		setupComponet(getJsrComboBox(), 5, 1, 1, 1, true);
		// “商品”下拉列表
		sp = new JComboBox();
		sp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				TbSpinfo info = (TbSpinfo) sp.getSelectedItem();// 获得被选中的商品信息
				if (info != null && info.getId() != null) {
					updateTable();// 如果选择有效就更新表格
				}
			}
		});
		// 表格模型
		table = new JTable();
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);// 不自动调整列的宽度，使用滚动条
		initTable();// 初始化表格模型
		// 添加事件完成品种数量、货品总数、合计金额的计算
		table.addContainerListener(new computeInfo());
		JScrollPane scrollPanel = new JScrollPane(table);
		scrollPanel.setPreferredSize(new Dimension(380, 200));
		setupComponet(scrollPanel, 0, 2, 6, 1, true);
		// “品种数量”标签和“品种数量”文本框
		setupComponet(new JLabel("品种数量："), 0, 3, 1, 0, false);
		pzs.setFocusable(false);
		setupComponet(pzs, 1, 3, 1, 1, true);
		// “货品总数”标签和“货品总数”文本框
		setupComponet(new JLabel("货品总数："), 2, 3, 1, 0, false);
		hpzs.setFocusable(false);
		setupComponet(hpzs, 3, 3, 1, 1, true);
		// “合计金额”标签和“合计金额”文本框
		setupComponet(new JLabel("合计金额："), 4, 3, 1, 0, false);
		hjje.setFocusable(false);
		setupComponet(hjje, 5, 3, 1, 1, true);
		// “验收结论”标签和“验收结论”文本框
		setupComponet(new JLabel("验收结论："), 0, 4, 1, 0, false);
		setupComponet(ysjl, 1, 4, 1, 1, true);
		// “操作人员”标签和“操作人员”文本框
		setupComponet(new JLabel("操作人员："), 2, 4, 1, 0, false);
		czy.setFocusable(false);
		czy.setText(MainFrame.getCzyStateLabel().getText());
		setupComponet(czy, 3, 4, 1, 1, true);
		// “添加”按钮
		JButton tjButton = new JButton("添加");
		tjButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 初始化票号
				initPiaoHao();
				// 停止表格单元的编辑
				stopTableCellEditing();
				// 如果表格中还包含空行，就不再添加新行
				for (int i = 0; i < table.getRowCount(); i++) {
					TbSpinfo info = (TbSpinfo) table.getValueAt(i, 0);
					if (info == null || info.getId().isEmpty())
						return;
				}
				DefaultTableModel model = (DefaultTableModel) table.getModel();// 创建默认的表格模型对象
				model.addRow(new Vector());// 向默认的表格模型对象添加空行
				initSpBox();// 初始化商品下拉列表
			}
		});
		setupComponet(tjButton, 4, 4, 1, 1, false);

		// “退货”按钮
		JButton rkButton = new JButton("退货");
		rkButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 停止表格单元的编辑
				stopTableCellEditing();
				// 清除空行
				clearEmptyRow();
				String hpzsStr = hpzs.getText();// 货品总数
				String pzsStr = pzs.getText();// 品种数
				String jeStr = hjje.getText();// 合计金额
				String jsfsStr = jsfs.getSelectedItem().toString();// 结算方式
				String jsrStr = jsr.getSelectedItem() + "";// 经手人
				String czyStr = czy.getText();// 操作员
				String rkDate = thsjDate.toLocaleString();// 入库时间
				String ysjlStr = ysjl.getText().trim();// 验收结论
				String id = piaoHao.getText();// 票号
				String gysName = kehu.getSelectedItem().toString();// 供应商名字
				if (jsrStr == null || jsrStr.isEmpty()) {// “经手人”为空
					JOptionPane.showMessageDialog(XiaoShouTuiHuo.this, "请填写经手人");
					return;
				}
				if (ysjlStr == null || ysjlStr.isEmpty()) {// “验收结论”为空
					JOptionPane.showMessageDialog(XiaoShouTuiHuo.this, "填写验收结论");
					return;
				}
				if (table.getRowCount() <= 0) {// 表格模型的行数小于等于0
					JOptionPane.showMessageDialog(XiaoShouTuiHuo.this, "填加退货商品");
					return;
				}
				TbXsthMain xsthMain = new TbXsthMain(id, pzsStr, jeStr, ysjlStr, gysName, rkDate, czyStr, jsrStr, jsfsStr);// 销售退货主表
				Set<TbXsthDetail> set = xsthMain.getTbXsthDetails();// 获得销售退货详细信息的集合
				int rows = table.getRowCount();// 获得表格模型中的行数
				for (int i = 0; i < rows; i++) {
					TbSpinfo spinfo = (TbSpinfo) table.getValueAt(i, 0);// 商品信息
					String djStr = (String) table.getValueAt(i, 6);// 单价
					String slStr = (String) table.getValueAt(i, 7);// 库存数量
					Double dj = Double.valueOf(djStr);// 将String型的单价转换为Double型
					Integer sl = Integer.valueOf(slStr);// 将String型的库存数量转换为Integer型
					TbXsthDetail detail = new TbXsthDetail();// 销售退货详细信息
					detail.setSpid(spinfo.getId());// 销售退货编号
					detail.setTbXsthMain(xsthMain.getXsthId());// 销售退货主表
					detail.setDj(dj);// 单价
					detail.setSl(sl);// 数量
					set.add(detail);// 把销售退货详细信息添加到销售退货详细信息的集合
				}
				boolean rs = Dao.insertXsthInfo(xsthMain);// 添加销售退货信息
				if (rs) {
					JOptionPane.showMessageDialog(XiaoShouTuiHuo.this, "退货完成");// 弹出提示框
					DefaultTableModel dftm = new DefaultTableModel();// 创建默认的表格模型对象
					table.setModel(dftm);// 将表格的数据模型设置为dftm
					initTable();// 初始化表格
					pzs.setText("0");// 设置“品种数量”文本框中的内容为0
					hpzs.setText("0");// 设置“货品总数”文本框中的内容为0
					hjje.setText("0");// 设置“合计金额”文本框中的内容为0
				}
			}
		});
		setupComponet(rkButton, 5, 4, 1, 1, false);
		// 添加窗体监听器，完成初始化
		addInternalFrameListener(new initTasks());
	}

	/**
	 * 初始化"经手人"下拉列表的方法
	 * 
	 * @return "经手人"下拉列表
	 */
	private JComboBox getJsrComboBox() {
		if (jsr == null) {// 如果“经手人”下拉列表不存在
			jsr = new JComboBox();// 创建“经手人”下拉列表
			List<List> czyList = Dao.getJsrs();// 获得被启用的经手人集合
			for (List<String> list : czyList) {// 遍历被启用的经手人集合
				String id = list.get(0);// 经手人编号
				String name = list.get(1);// 经手人姓名
				Item item = new Item(id, name);// 数据表公共类
				item.setId(id + "");// 编号属性
				item.setName(name);// 名称信息
				jsr.addItem(item);// 向“经手人”下拉列表中添加经手人
			}
		}
		return jsr;
	}

	// 初始化表格模型
	private void initTable() {
		String[] columnNames = { "商品名称", "商品编号", "供应商", "产地", "单位", "规格", "单价", "数量", "包装", "批号", "批准文号" };// 表头
		((DefaultTableModel) table.getModel()).setColumnIdentifiers(columnNames);// 创建表格模型对象并向其中添加表头
		TableColumn column = table.getColumnModel().getColumn(0);// 以表格模型中索引为0的列作参照
		final DefaultCellEditor editor = new DefaultCellEditor(sp);// 创建单元格编辑器
		editor.setClickCountToStart(2);// 开始编辑单元格所需的单击次数为2次
		column.setCellEditor(editor);// 编辑参照列中单元格时所用的编辑器
	}

	// 初始化商品下拉列表
	private void initSpBox() {
		List list = new ArrayList();// 创建商品信息的集合
		ResultSet set = Dao.query("select * from tb_spinfo where id in (select id from tb_kucun)");// 获得有库存的商品信息的结果集
		sp.removeAllItems();// 移除“商品”下拉列表中的选项
		sp.addItem(new TbSpinfo());// 向“商品”下拉列表中添加商品信息
		for (int i = 0; table != null && i < table.getRowCount(); i++) {
			TbSpinfo tmpInfo = (TbSpinfo) table.getValueAt(i, 0);// 获得商品信息
			if (tmpInfo != null && tmpInfo.getId() != null)// 如果商品信息和商品编号都不为空
				list.add(tmpInfo.getId());// 向商品信息的集合中添加商品编号
		}
		try {
			while (set.next()) {// 移动后的记录指针指向一条有效的记录
				TbSpinfo spinfo = new TbSpinfo();// 商品信息
				spinfo.setId(set.getString("id").trim());// 商品编号
				// 如果表格中已存在同样商品，商品下拉框中就不再包含该商品
				if (list.contains(spinfo.getId()))
					continue;
				spinfo.setSpname(set.getString("spname").trim());// 商品名称
				spinfo.setCd(set.getString("cd").trim());// 产地
				spinfo.setJc(set.getString("jc").trim());// 商品简称
				spinfo.setDw(set.getString("dw").trim());// 商品计量单位
				spinfo.setGg(set.getString("gg").trim());// 商品规格
				spinfo.setBz(set.getString("bz").trim());// 包装
				spinfo.setPh(set.getString("ph").trim());// 批号
				spinfo.setPzwh(set.getString("pzwh").trim());// 批准文号
				spinfo.setMemo(set.getString("memo").trim());// 备注
				spinfo.setGysname(set.getString("gysname").trim());// 供应商名称
				sp.addItem(spinfo);// 向“商品”下拉列表中添加商品信息
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	// 设置组件位置并添加到容器中
	private void setupComponet(JComponent component, int gridx, int gridy, int gridwidth, int ipadx, boolean fill) {
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

	// 客户选择时更新联系人字段
	private void doKhSelectAction() {
		Item item = (Item) kehu.getSelectedItem();// 获得被选中的客户
		TbKhinfo khInfo = Dao.getKhInfo(item);// 读取指定客户信息
		lian.setText(khInfo.getLian());// 设置“联系人”文本框中的文本内容
	}

	// 计算品种数量、货品总数、合计金额
	private final class computeInfo implements ContainerListener {
		public void componentRemoved(ContainerEvent e) {
			// 清除空行
			clearEmptyRow();
			int rows = table.getRowCount();// 获得表格模型中的行数
			int count = 0;// “货品总数”
			double money = 0.0;// “合计金额”
			TbSpinfo column = null;// 商品信息的实例
			if (rows > 0)
				column = (TbSpinfo) table.getValueAt(rows - 1, 0);// 为“商品信息”的实例赋值
			if (rows > 0 && (column == null || column.getId().isEmpty()))// 表格模型中的行数大于0且“商品信息”的实例不存在或商品编号为空
				rows--;// 表格模型中的行数减一
			// 计算货品总数和金额
			for (int i = 0; i < rows; i++) {
				String column7 = (String) table.getValueAt(i, 7);// 获得表格中“数量”
				String column6 = (String) table.getValueAt(i, 6);// 获得表格中“单价”
				int c7 = (column7 == null || column7.isEmpty()) ? 0 : Integer.parseInt(column7);// 将String类型的“数量”转换为int型
				Double c6 = (column6 == null || column6.isEmpty()) ? 0 : Double.valueOf(column6);// 将String类型的“单价”转换为Double型
				count += c7;// 计算货品总数
				money += c6 * c7;// 计算合计金额
			}
			pzs.setText(rows + "");// 设置“品种数量”文本框中的文本内容
			hpzs.setText(count + "");// 设置“货品总数”文本框中的文本内容
			hjje.setText(money + "");// 设置“合计金额”文本框中的文本内容
		}

		public void componentAdded(ContainerEvent e) {
		}
	}

	// 窗体的初始化任务
	private final class initTasks extends InternalFrameAdapter {
		public void internalFrameActivated(InternalFrameEvent e) {
			super.internalFrameActivated(e);
			initTimeField();// 启动退货时间线程
			initKehuField();// 初始化客户字段
			initPiaoHao();// 初始化“销售票号”
			initSpBox();// 初始化商品下拉列表
		}

		private void initKehuField() {// 初始化客户字段
			List keHuInfo = Dao.getKhInfos();// 获得所有客户信息的集合
			for (Iterator iter = keHuInfo.iterator(); iter.hasNext();) {// 遍历所有客户信息的集合
				List list = (List) iter.next();// 获得迭代的下一个集合
				Item item = new Item();// 数据表公共类
				item.setId(list.get(0).toString().trim());// 编号属性
				item.setName(list.get(1).toString().trim());// 名称信息
				kehu.addItem(item);// 向“客户”下拉列表中添加选项
			}
			doKhSelectAction();
		}
		// 启动退货时间线程
		private void initTimeField() {
			new Thread(new Runnable() {
				public void run() {
					try {
						while (true) {
							thsjDate = new Date();// 创建日期对象
							thsj.setText(thsjDate.toLocaleString());// 设置“退货时间”文本框中的文本内容
							Thread.sleep(1000);// 线程休眠1秒
						}
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}).start();
		}
	}
	// 初始化销退票号
	private void initPiaoHao() {
		java.sql.Date date = new java.sql.Date(System.currentTimeMillis());// 使用系统时间值构造一个日期对象
		String maxId = Dao.getXsthMainMaxId(date);// 获取最大的销售退货编号
		piaoHao.setText(maxId);// 设置“销售票号”文本框中的文本内容
	}

	// 根据商品下拉框的选择，更新表格当前行的内容
	private synchronized void updateTable() {
		TbSpinfo spinfo = (TbSpinfo) sp.getSelectedItem();// 获得“商品”下拉列表中被选中的选项
		Item item = new Item();// 数据表公共类
		item.setId(spinfo.getId());// 编号属性
		TbKucun kucun = Dao.getKucun(item);// 获取库存商品信息
		int row = table.getSelectedRow();// 获得表格模型中被选中的行
		if (row >= 0 && spinfo != null) {
			table.setValueAt(spinfo.getId(), row, 1);// 商品编号
			table.setValueAt(spinfo.getGysname(), row, 2);// 供应商名称
			table.setValueAt(spinfo.getCd(), row, 3);// 产地
			table.setValueAt(spinfo.getDw(), row, 4);// 商品计量单位
			table.setValueAt(spinfo.getGg(), row, 5);// 商品规格
			table.setValueAt(kucun.getDj() + "", row, 6);// 单价
			table.setValueAt(kucun.getKcsl() + "", row, 7);// 库存数量
			table.setValueAt(spinfo.getBz(), row, 8);// 包装
			table.setValueAt(spinfo.getPh(), row, 9);// 批号
			table.setValueAt(spinfo.getPzwh(), row, 10);// 批准文号
			table.editCellAt(row, 7);// 库存数量可编辑
		}
	}

	// 清除空行
	private synchronized void clearEmptyRow() {
		DefaultTableModel dftm = (DefaultTableModel) table.getModel();// 获得默认的表格模型
		for (int i = 0; i < table.getRowCount(); i++) {
			TbSpinfo spinfo = (TbSpinfo) table.getValueAt(i, 0);// 获得商品信息
			if (spinfo == null || spinfo.getId() == null || spinfo.getId().isEmpty()) {// 商品信息为空
				dftm.removeRow(i);// 移除默认的表格模型中的该行
			}
		}
	}

	// 停止表格单元的编辑
	private void stopTableCellEditing() {
		TableCellEditor cellEditor = table.getCellEditor();// 创建表格单元编辑器
		if (cellEditor != null)// 表格单元编辑器存在
			cellEditor.stopCellEditing();// 停止表格单元的编辑
	}
}
