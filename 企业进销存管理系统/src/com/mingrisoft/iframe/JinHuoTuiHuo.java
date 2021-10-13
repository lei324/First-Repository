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

public class JinHuoTuiHuo extends JInternalFrame {// 进货-退货内部窗体

	private final JTable table;// 表格模型
	private final JTextField thsj = new JTextField();// “退货时间”文本框
	private JComboBox jsr = null;// “经手人”下拉列表
	private final JComboBox jsfs = new JComboBox();// “结算方式”下拉列表
	private final JTextField lian = new JTextField();// “联系人”文本框
	private final JComboBox gys = new JComboBox();// “供应商”下拉列表
	private final JTextField piaoHao = new JTextField();// “退货票号”文本框
	private final JTextField pzs = new JTextField("0");// “品种数量”文本框
	private final JTextField hpzs = new JTextField("0");// “货品总数”文本框
	private final JTextField hjje = new JTextField("0");// “合计金额”文本框
	private final JTextField ysjl = new JTextField();// “退货原因”文本框
	private final JTextField czy = new JTextField();// “操作员”文本框
	private Date thsjDate;// “退货时间”
	private JComboBox sp;// “商品”下拉列表

	public JinHuoTuiHuo() {// 进货-退货内部窗体的构造方法
		super();// 调用父类JInternalFrame的构造器
		setMaximizable(true);// 可以最大化
		setIconifiable(true);// 可以图标化
		setClosable(true);// 进货-退货内部窗体可以关闭
		getContentPane().setLayout(new GridBagLayout());// 设置进货-退货内部窗体的布局为网格布局
		setTitle("进货-退货");// 设置进货-退货内部窗体的标题
		setBounds(50, 50, 700, 400);// 设置进货-退货内部窗体的位置和宽高
		// “退货票号”标签与“退货票号”文本框
		setupComponet(new JLabel("退货票号："), 0, 0, 1, 0, false);
		piaoHao.setFocusable(false);
		setupComponet(piaoHao, 1, 0, 1, 140, true);
		// “供应商”标签与“供应商”下拉列表
		setupComponet(new JLabel("供应商："), 2, 0, 1, 0, false);
		gys.setPreferredSize(new Dimension(160, 21));
		gys.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				doGysSelectAction();// “供应商”下拉列表的选择事件
			}
		});
		setupComponet(gys, 3, 0, 1, 1, true);
		// “联系人”标签与“联系人”文本框
		setupComponet(new JLabel("联系人："), 4, 0, 1, 0, false);
		lian.setFocusable(false);
		lian.setPreferredSize(new Dimension(80, 21));
		setupComponet(lian, 5, 0, 1, 0, true);
		// “结算方式”标签与“结算方式”下拉列表
		setupComponet(new JLabel("结算方式："), 0, 1, 1, 0, false);
		jsfs.addItem("现金");
		jsfs.addItem("支票");
		jsfs.setEditable(true);
		setupComponet(jsfs, 1, 1, 1, 1, true);
		// “退货时间”标签与“退货时间”文本框
		setupComponet(new JLabel("退货时间："), 2, 1, 1, 0, false);
		thsj.setFocusable(false);
		setupComponet(thsj, 3, 1, 1, 1, true);
		// “经手人”标签与“经手人”下拉列表
		setupComponet(new JLabel("经手人："), 4, 1, 1, 0, false);
		setupComponet(getJsrComboBox(), 5, 1, 1, 1, true);
		// “商品”下拉列表
		sp = new JComboBox();
		sp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				TbKucun info = (TbKucun) sp.getSelectedItem();
				if (info != null && info.getId() != null) {// 如果选择有效就更新表格
					updateTable();
				}
			}
		});
		// 表格模型
		table = new JTable();
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);// 不自动调整列的宽度，使用滚动条
		initTable();// 初始化表格
		table.addContainerListener(new computeInfo());// 添加事件完成品种数量、货品总数、合计金额的计算
		JScrollPane scrollPanel = new JScrollPane(table);
		scrollPanel.setPreferredSize(new Dimension(380, 200));
		setupComponet(scrollPanel, 0, 2, 6, 1, true);
		// “品种数量”标签与“品种数量”文本框
		setupComponet(new JLabel("品种数量："), 0, 3, 1, 0, false);
		pzs.setFocusable(false);
		setupComponet(pzs, 1, 3, 1, 1, true);
		// “货品总数”标签与“货品总数”文本框
		setupComponet(new JLabel("货品总数："), 2, 3, 1, 0, false);
		hpzs.setFocusable(false);
		setupComponet(hpzs, 3, 3, 1, 1, true);
		// “合计金额”标签与“合计金额”文本框
		setupComponet(new JLabel("合计金额："), 4, 3, 1, 0, false);
		hjje.setFocusable(false);
		setupComponet(hjje, 5, 3, 1, 1, true);
		// “退货原因”标签与“退货原因”文本框
		setupComponet(new JLabel("退货原因："), 0, 4, 1, 0, false);
		setupComponet(ysjl, 1, 4, 1, 1, true);
		// “操作人员”标签与“操作人员”文本框
		setupComponet(new JLabel("操作人员："), 2, 4, 1, 0, false);
		czy.setFocusable(false);
		czy.setText(MainFrame.getCzyStateLabel().getText());
		setupComponet(czy, 3, 4, 1, 1, true);
		// “添加”按钮
		JButton tjButton = new JButton("添加");
		tjButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 初始化退货票号
				initPiaoHao();
				// 停止表格单元的编辑
				stopTableCellEditing();
				// 如果表格中还包含空行，就不再添加新行
				for (int i = 0; i < table.getRowCount(); i++) {
					TbKucun info = (TbKucun) table.getValueAt(i, 0);
					if (info == null || info.getId().isEmpty())
						return;
				}
				DefaultTableModel model = (DefaultTableModel) table.getModel();// 创建默认的表格模型对象
				model.addRow(new Vector());// 向默认的表格模型对象添加空行
				initSpBox();// 初始化“商品”下拉列表
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
				String ysjlStr = ysjl.getText().trim();// 退货原因
				String id = piaoHao.getText();// 票号
				String gysName = gys.getSelectedItem().toString();// 供应商名字
				if (jsrStr == null || jsrStr.isEmpty()) {// “经手人”下拉列表不存在或“经手人”下拉列表为空
					JOptionPane.showMessageDialog(JinHuoTuiHuo.this, "请填写经手人");
					return;
				}
				if (ysjlStr == null || ysjlStr.isEmpty()) {// “退货原因”文本框不存在或“退货原因”文本框为空
					JOptionPane.showMessageDialog(JinHuoTuiHuo.this, "填写退货原因");
					return;
				}
				if (table.getRowCount() <= 0) {// 表格模型的行数小于等于0
					JOptionPane.showMessageDialog(JinHuoTuiHuo.this, "填加退货商品");
					return;
				}
				TbRkthMain rkthMain = new TbRkthMain(id, pzsStr, jeStr, ysjlStr, gysName, rkDate, czyStr, jsrStr, jsfsStr);// 进货退货主表
				Set<TbRkthDetail> set = rkthMain.getTbRkthDetails();// 存储进货退货详细信息的集合
				int rows = table.getRowCount();// 获得表格模型中的行数
				for (int i = 0; i < rows; i++) {
					TbKucun kucun = (TbKucun) table.getValueAt(i, 0);// 库存信息
					String djStr = (String) table.getValueAt(i, 6);// 单价
					String slStr = (String) table.getValueAt(i, 7);// 库存数量
					Double dj = Double.valueOf(djStr);// 将String型的单价转换为Double型
					Integer sl = Integer.valueOf(slStr);// 将String型的库存数量转换为Integer型
					TbRkthDetail detail = new TbRkthDetail();// 进货退货详细信息
					detail.setSpid(kucun.getId());// 进货退货编号
					detail.setTbRkthMain(rkthMain.getRkthId());// 进货退货主表
					detail.setDj(dj);// 单价
					detail.setSl(sl);// 数量
					set.add(detail);// 添加进货退货详细信息
				}
				boolean rs = Dao.insertRkthInfo(rkthMain);// 是否成功添加入库信息
				if (rs) {
					JOptionPane.showMessageDialog(JinHuoTuiHuo.this, "退货完成");// 弹出提示框
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
		addInternalFrameListener(new initTasks());// 添加窗体监听器，完成初始化
	}

	/**
	 * 获得“经手人”下拉列表的方法
	 * 
	 * @return “经手人”下拉列表
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

	private void initTable() {// 初始化表格
		String[] columnNames = { "商品名称", "商品编号", "产地", "单位", "规格", "包装", "单价", "数量" };// 表头
		((DefaultTableModel) table.getModel()).setColumnIdentifiers(columnNames);// 创建表格模型对象并向其中添加表头
		TableColumn column = table.getColumnModel().getColumn(0);// 以表格模型中索引为0的列作参照
		final DefaultCellEditor editor = new DefaultCellEditor(sp);// 创建单元格编辑器
		editor.setClickCountToStart(2);// 开始编辑单元格所需的单击次数为2次
		column.setCellEditor(editor);// 编辑参照列中单元格时所用的编辑器
	}

	private void initSpBox() {// 初始化“商品”下拉列表
		List list = new ArrayList();// 创建存储库存信息的集合
		ResultSet set = Dao.query("select * from tb_kucun where id in(select id from tb_spinfo where gysName='"
				+ gys.getSelectedItem() + "')");// 获得商品信息的结果集
		sp.removeAllItems();// 移除“商品”下拉列表中的选项
		sp.addItem(new TbKucun());// 向“商品”下拉列表中添加选项
		for (int i = 0; table != null && i < table.getRowCount(); i++) {
			TbKucun tmpInfo = (TbKucun) table.getValueAt(i, 0);// 获得库存信息
			if (tmpInfo != null && tmpInfo.getId() != null)// 如果库存信息和商品编号都不为空
				list.add(tmpInfo.getId());// 向库存信息的集合中添加商品编号
		}
		try {
			while (set.next()) {// 移动后的记录指针指向一条有效的记录
				TbKucun kucun = new TbKucun();// 库存信息
				kucun.setId(set.getString("id").trim());// 商品编号
				if (list.contains(kucun.getId()))// 如果表格中已存在同样商品，商品下拉框中就不再包含该商品
					continue;
				kucun.setSpname(set.getString("spname").trim());// 商品名称
				kucun.setCd(set.getString("cd").trim());// 产地
				kucun.setJc(set.getString("jc").trim());// 商品简称
				kucun.setDw(set.getString("dw").trim());// 商品计量单位
				kucun.setGg(set.getString("gg").trim());// 商品规格
				kucun.setBz(set.getString("bz").trim());// 包装
				kucun.setDj(Double.valueOf(set.getString("dj").trim()));// 单价
				kucun.setKcsl(Integer.valueOf(set.getString("kcsl").trim()));// 库存数量
				sp.addItem(kucun);// 向“商品”下拉列表中添加库存信息
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	private void setupComponet(JComponent component, int gridx, int gridy, int gridwidth, int ipadx, boolean fill) {// 设置组件位置并添加到容器中
		final GridBagConstraints gridBagConstrains = new GridBagConstraints();// 创建网格限制对象
		gridBagConstrains.gridx = gridx;// 设置组件位于网格的横向索引为gridx
		gridBagConstrains.gridy = gridy;// 设置组件位于网格的纵向索引为gridy
		gridBagConstrains.insets = new Insets(5, 1, 3, 1);// 组件彼此的间距
		if (gridwidth > 1)// 组件横跨网格数大于1
			gridBagConstrains.gridwidth = gridwidth;// 设置组件横跨网格数为gridwidth
		if (ipadx > 0)// 组件横向填充的大小大于0
			gridBagConstrains.ipadx = ipadx;// 设置组件横向填充的大小
		if (fill)// 组件占据空白区域
			gridBagConstrains.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
		getContentPane().add(component, gridBagConstrains);// 添加组件
	}

	private void doGysSelectAction() {// “供应商”下拉列表的选择事件
		Item item = (Item) gys.getSelectedItem();// 获得被选中的供应商
		TbGysinfo gysInfo = Dao.getGysInfo(item);// 读取指定供应商信息
		lian.setText(gysInfo.getLian());// 设置“联系人”文本框中的文本内容
	}

	private final class computeInfo implements ContainerListener {// 在事件中计算品种数量、货品总数、合计金额
		public void componentRemoved(ContainerEvent e) {
			// 清除空行
			clearEmptyRow();
			int rows = table.getRowCount();// 获得表格模型中的行数
			int count = 0;// “货品总数”
			double money = 0.0;// “合计金额”
			TbKucun column = null;// “库存信息”的实例
			if (rows > 0)// 表格模型中的行数大于0
				column = (TbKucun) table.getValueAt(rows - 1, 0);// 为“库存信息”的实例赋值
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

	private final class initTasks extends InternalFrameAdapter {// 窗体的初始化任务
		public void internalFrameActivated(InternalFrameEvent e) {
			super.internalFrameActivated(e);
			initTimeField();// 启动退货时间线程
			initGysField();// 初始化供应商字段
			initPiaoHao();// 初始化“退货票号”
			initSpBox();// 初始化“商品”下拉列表
		}

		private void initGysField() {// 初始化供应商字段
			List gysInfos = Dao.getGysInfos();// 获得所有供应商信息的集合
			for (Iterator iter = gysInfos.iterator(); iter.hasNext();) {// 遍历所有供应商信息的集合
				List list = (List) iter.next();// 获得迭代的下一个集合
				Item item = new Item();// 数据表公共类
				item.setId(list.get(0).toString().trim());// 编号属性
				item.setName(list.get(1).toString().trim());// 名称信息
				gys.addItem(item);// 向“供应商”下拉列表中添加选项
			}
			doGysSelectAction();
		}

		private void initTimeField() {// 启动退货时间线程
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
			}).start();// 启动线程
		}
	}

	private void initPiaoHao() {// 初始化“退货票号”
		java.sql.Date date = new java.sql.Date(System.currentTimeMillis());// 使用系统时间值构造一个日期对象
		String maxId = Dao.getRkthMainMaxId(date);// 获取退货最大ID
		piaoHao.setText(maxId);// 设置“退货票号”文本框中的文本内容
	}

	private synchronized void updateTable() {// 根据商品下拉框的选择，更新表格当前行的内容
		TbKucun kucun = (TbKucun) sp.getSelectedItem();// 获得“商品”下拉列表中被选中的选项
		int row = table.getSelectedRow();// 获得表格模型中被选中的行
		if (row >= 0 && kucun != null) {// 表格模型中被选中的行大于等于0且“商品”下拉列表中被选中的选项不为空
			table.setValueAt(kucun.getId(), row, 1);// 商品编号
			table.setValueAt(kucun.getCd(), row, 2);// 产地
			table.setValueAt(kucun.getDw(), row, 3);// 商品计量单位
			table.setValueAt(kucun.getGg(), row, 4);// 商品规格
			table.setValueAt(kucun.getBz(), row, 5);// 包装
			table.setValueAt(kucun.getDj().toString(), row, 6);// 单价
			table.setValueAt(kucun.getKcsl().toString(), row, 7);// 库存数量
			table.editCellAt(row, 7);// 库存数量可编辑
		}
	}

	private synchronized void clearEmptyRow() {// 清除空行
		DefaultTableModel dftm = (DefaultTableModel) table.getModel();// 获得默认的表格模型
		for (int i = 0; i < table.getRowCount(); i++) {
			TbKucun kucun = (TbKucun) table.getValueAt(i, 0);// 获得库存信息
			// 库存信息为空
			if (kucun == null || kucun.getId() == null || kucun.getId().isEmpty()) {
				dftm.removeRow(i);// 移除默认的表格模型中的该行
			}
		}
	}
	/**
	 * 该方法用于停止表格单元的编辑
	 */
	private void stopTableCellEditing() {
		TableCellEditor cellEditor = table.getCellEditor();// 创建表格单元编辑器
		if (cellEditor != null)// 表格单元编辑器存在
			cellEditor.stopCellEditing();// 停止表格单元的编辑
	}
}
