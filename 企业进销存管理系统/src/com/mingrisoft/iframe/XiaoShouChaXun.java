package com.mingrisoft.iframe;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.DefaultTableModel;

import com.mingrisoft.dao.Dao;
import com.mingrisoft.dao.model.TbJsr;

public class XiaoShouChaXun extends JInternalFrame{// 销售查询内部窗体
	
	private JButton queryButton;// “查询”按钮
	private JTextField endDate;// “终止日期”文本框
	private JTextField startDate;// “起始日期”文本框
	private JTable table;// 表格模型
	private JTextField content;// “条件内容”文本框
	private JComboBox operation;// “条件运算”下拉列表
	private JComboBox condition;// “条件名称”下拉列表
	private TbJsr user;// 经手人信息
	private DefaultTableModel dftm;// 表格模型的实例化对象
	private JCheckBox selectDate;// “指定查询日期”复选框
	
	public XiaoShouChaXun() {// 销售查询内部窗体的构造方法
		// 打开销售查询内部窗体时，设置“起始日期”和“终止日期”
		addInternalFrameListener(new InternalFrameAdapter() {
			public void internalFrameActivated(final InternalFrameEvent e) {
				java.sql.Date date=new java.sql.Date(System.currentTimeMillis());// 创建以系统当前时间为参数的日期对象
				endDate.setText(date.toString());// 设置“终止日期”文本框中的文本内容
				date.setMonth(0);// 设置月份为1月
				date.setDate(1);// 设置日期为当前年份的当前月份的第一天
				startDate.setText(date.toString());// 设置“起始日期”文本框中的文本内容
			}
		});
		setIconifiable(true);// 可以图标化
		setClosable(true);// 可以关闭
		setTitle("销售信息查询");// 设置销售查询内部窗体的标题
		getContentPane().setLayout(new GridBagLayout());// 设置销售查询内部窗体的布局是网格布局
		setBounds(100, 100, 680, 375);// 设置销售查询内部窗体的位置和宽高
		// “选择查询条件”标签和“条件名称”下拉列表
		setupComponet(new JLabel(" 选择查询条件："), 0, 0, 1, 1, false);
		condition = new JComboBox();
		condition.setModel(new DefaultComboBoxModel(new String[] {"客户全称", "销售票号"}));
		setupComponet(condition, 1, 0, 1, 30, true);
		// “条件运算”下拉列表
		operation = new JComboBox();
		operation.setModel(new DefaultComboBoxModel(new String[]{"等于", "包含"}));
		setupComponet(operation, 4, 0, 1, 30, true);
		// “条件内容”文本框
		content = new JTextField();
		content.addKeyListener(new KeyAdapter() {// 为“条件内容”文本框添加键盘事件的监听
			public void keyReleased(final KeyEvent e) {
				if(e.getKeyCode()==10) {// 当按下“回车”键时
					queryButton.doClick();// “查询”按钮执行“单击”操作
				}
			}
		});
		setupComponet(content, 5, 0, 2, 240, true);
		// “查询”按钮
		queryButton = new JButton();
		queryButton.addActionListener(new QueryAction());// 为“查询”按钮添加动作事件的监听
		setupComponet(queryButton, 7, 0, 1, 1, false);
		queryButton.setText("查询");
		// “指定查询日期”复选框
		selectDate = new JCheckBox();
		final GridBagConstraints gridBagConstraints_7 = new GridBagConstraints();
		gridBagConstraints_7.anchor = GridBagConstraints.EAST;
		gridBagConstraints_7.insets = new Insets(0, 10, 0, 0);
		gridBagConstraints_7.gridy = 1;
		gridBagConstraints_7.gridx = 0;
		getContentPane().add(selectDate, gridBagConstraints_7);
		// “指定查询日期    从”标签
		final JLabel label_1 = new JLabel();
		label_1.setText("指定查询日期    从");
		final GridBagConstraints gridBagConstraints_8 = new GridBagConstraints();
		gridBagConstraints_8.anchor = GridBagConstraints.EAST;
		gridBagConstraints_8.gridy = 1;
		gridBagConstraints_8.gridx = 1;
		getContentPane().add(label_1, gridBagConstraints_8);
		// “起始日期”文本框
		startDate = new JTextField();
		startDate.setPreferredSize(new Dimension(100,21));
		setupComponet(startDate, 2, 1, 3, 1, true);
		// “到”文本框
		setupComponet(new JLabel("到"), 5, 1, 1, 1, false);
		// “终止日期”文本框
		endDate = new JTextField();
		endDate.addKeyListener(content.getKeyListeners()[0]);// “条件内容”文本框获得键盘事件的监听(当按下“回车”键时，“查询”按钮执行“单击”操作)
		endDate.setPreferredSize(new Dimension(100,21));
		final GridBagConstraints gridBagConstraints_11 = new GridBagConstraints();
		gridBagConstraints_11.ipadx = 90;
		gridBagConstraints_11.anchor = GridBagConstraints.WEST;
		gridBagConstraints_11.insets = new Insets(0, 0, 0, 0);
		gridBagConstraints_11.gridy = 1;
		gridBagConstraints_11.gridx = 6;
		getContentPane().add(endDate, gridBagConstraints_11);
		// “显示全部数据”按钮
		final JButton showAllButton = new JButton();
		showAllButton.addActionListener(new ActionListener() {// 为“显示全部数据”按钮添加动作事件的监听
			public void actionPerformed(final ActionEvent e) {
				content.setText("");// 设置“条件内容”文本框为空
				List list=Dao.findForList("select * from v_sellView");// 获得销售信息的集合
				Iterator iterator=list.iterator();// 创建销售信息集合的迭代器
				updateTable(iterator);// 更新表格数据
			}
		});
		final GridBagConstraints gridBagConstraints_5 = new GridBagConstraints();
		gridBagConstraints_5.insets = new Insets(0, 0, 0, 10);
		gridBagConstraints_5.gridy = 1;
		gridBagConstraints_5.gridx = 7;
		getContentPane().add(showAllButton, gridBagConstraints_5);
		showAllButton.setFont(new Font("", Font.PLAIN, 12));
		showAllButton.setText("显示全部数据");
		// 滚动面板
		final JScrollPane scrollPane = new JScrollPane();
		final GridBagConstraints gridBagConstraints_6 = new GridBagConstraints();
		gridBagConstraints_6.weighty = 1.0;
		gridBagConstraints_6.anchor = GridBagConstraints.NORTH;
		gridBagConstraints_6.insets = new Insets(0, 10, 5, 10);
		gridBagConstraints_6.fill = GridBagConstraints.BOTH;
		gridBagConstraints_6.gridwidth = 9;
		gridBagConstraints_6.gridy = 2;
		gridBagConstraints_6.gridx = 0;
		getContentPane().add(scrollPane, gridBagConstraints_6);
		// 表格模型
		table = new JTable();
		table.setEnabled(false);// 设置表格模型无法响应用户输入
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);// 不自动调整列的宽度；使用滚动条
		dftm = (DefaultTableModel)table.getModel();// 获得默认的表格模型
		String[] tableHeads = new String[]{"销售票号", "商品名称", "商品编号", "规格", "单价",
				"数量", "金额", "客户全称", "销售日期", "操作员", "经手人", "结算方式"};// 表头
		dftm.setColumnIdentifiers(tableHeads);// 设置默认表格模型的表头
		scrollPane.setViewportView(table);// 把表格模型添加到滚动面板中
	}
	// 更新表格数据
	private void updateTable(Iterator iterator) {
		int rowCount=dftm.getRowCount();// 获得默认的表格模型中的行数
		for(int i=0;i<rowCount;i++) {
			dftm.removeRow(0);// 移除表格模型中的第一行
		}
		while(iterator.hasNext()) {// 销售信息的集合中仍有元素可以迭代
			Vector vector=new Vector();// 创建向量
			List view=(List) iterator.next();// 获得迭代的下一个集合
			vector.addAll(view);// 将迭代后集合中所有的元素添加到此向量中
			dftm.addRow(vector);// 向默认的表格模型中添加行数据
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
	// 条件查询
	private final class QueryAction implements ActionListener {// “查询”按钮添加动作事件的监听
		public void actionPerformed(final ActionEvent e) {
			boolean selDate = selectDate.isSelected();// “指定查询日期”复选框是否被选中
			if(content.getText().equals("")) {// “条件内容”文本框为空
				JOptionPane.showMessageDialog(getContentPane(), "请输入查询内容！");// 弹出提示框
				return;
			}
			if(selDate) {// “指定查询日期”复选框被选中
				if(startDate.getText()==null||startDate.getText().equals("")) {// “起始日期”文本框为空
					JOptionPane.showMessageDialog(getContentPane(), "请输入查询的开始日期！");// 弹出提示框
					return;
				}
				if(endDate.getText()==null||endDate.getText().equals("")) {// “终止日期”文本框为空
					JOptionPane.showMessageDialog(getContentPane(), "请输入查询的结束日期！");// 弹出提示框
					return;
				}
			}
			List list=null;// 结果集
			String con = condition.getSelectedIndex() == 0 ? "khname " : "sellId ";// 判断“条件名称”下拉列表中被选中的是“客户全称”还是“销售票号”
			int oper = operation.getSelectedIndex();// 获得“条件运算”下拉列表被选中的选项
			String opstr = oper == 0 ? "= " : "like ";// 根据“条件运算”下拉列表被选中的选项判断应该是直接查询还是模糊查询
			String cont = content.getText();// 获得“条件内容”文本框中的文本内容
			list = Dao.findForList("select * from v_sellView where "
					+ con
					+ opstr
					+ (oper == 0 ? "'"+cont+"'" : "'%" + cont + "%'")
					+ (selDate ? " and xsdate>'" + startDate.getText()
							+ "' and xsdate<='" + endDate.getText()+" 23:59:59'" : ""));// 执行拼接的SQL语句后，获得的销售信息结果集
			Iterator iterator = list.iterator();// 创建销售信息结果集的迭代器
			updateTable(iterator);// 更新表格数据
		}
	}
}