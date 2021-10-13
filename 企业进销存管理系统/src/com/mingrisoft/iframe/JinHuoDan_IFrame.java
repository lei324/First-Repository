package com.mingrisoft.iframe;

import java.awt.*;
import java.awt.event.*;
import java.beans.PropertyChangeListener;
import java.sql.*;
import java.util.*;
import java.util.Date;
import java.util.List;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import javax.swing.table.*;

import com.mingrisoft.*;
import com.mingrisoft.dao.Dao;
import com.mingrisoft.dao.model.*;

public class JinHuoDan_IFrame extends JInternalFrame {// 进货单窗体

	private JPanel jContentPane = null;// 内容面板
	private JPanel topPanel = null;// 顶部面板
	private JLabel idLabel = null;// “进货票号”标签
	private JTextField idField = null;// “进货票号”文本框
	private JLabel gysLabel = null;// “供应商”标签
	private JLabel lxrLabel = null;// “联系人”标签
	private JTextField lxrField = null;// “联系人”文本框
	private JLabel jsfsLabel = null;// “结算方式”标签
	private JComboBox jsfsComboBox = null;// “结算方式”下拉列表
	private JLabel jhsjLabel = null;// “进货时间”标签
	private JTextField jhsjField = null;// “进货时间”文本框
	private JLabel jsrLabel = null;// “经手人”标签
	private JTextField czyField = null;// “操作员”文本框
	private JPanel bottomPanel = null;// 底部面板
	private JLabel pzslLabel = null;// “品种数量”标签
	private JTextField pzslField = null;// “品种数量”文本框
	private JLabel hpzsLabel = null;// “货品总数”标签
	private JTextField hpzsField = null;// “货品总数”文本框
	private JLabel hjjeLabel = null;// “合计金额”标签
	private JTextField hjjeField = null;// “合计金额”文本框
	private JLabel ysjlLabel = null;// “验收结论”标签
	private JTextField ysjlField = null;// “验收结论”文本框
	private JLabel czyLabel = null;// “操作员”标签
	private JButton tjButton = null;// “添加”按钮
	private JButton rukuButton = null;// “入库”按钮
	private JScrollPane tablePane = null;// 表格面板
	private JTable table = null;// 表格模型
	private JComboBox spComboBox = null;// 商品下拉列表
	private JComboBox gysComboBox = null;// “供应商”下拉列表
	private JComboBox jsrComboBox = null;// “经手人”下拉列表

	private Date jhsjDate = new Date();// 创建日期对象之“进货时间”

	/**
	 * 进货单窗体的构造方法
	 */
	public JinHuoDan_IFrame() {
		super();// 调用父类JInternalFrame的构造方法
		initialize();// 初始化进货单窗体
	}

	/**
	 * 初始化进货单窗体的方法
	 */
	private void initialize() {
		this.setSize(600, 320);// 设置进货单窗体的宽高
		this.setIconifiable(true);// 设置进货单窗体可以图标化
		this.setResizable(true);// 可以调整进货单窗体的大小
		this.setMaximizable(true);// 设置进货单窗体可以最大化
		this.setTitle("进货单");// 设置进货单窗体的标题
		this.setClosable(true);// 设置进货单窗体可以关闭
		this.setContentPane(getJContentPane());// 加载内容面板
	}

	/**
	 * 获得内容面板的方法
	 * 
	 * @return 内容面板
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {// 内容面板不存在
			jContentPane = new JPanel();// 创建内容面板
			jContentPane.setLayout(new BorderLayout());// 创建边界布局
			jContentPane.add(getTopPanel(), java.awt.BorderLayout.NORTH);// 把顶部面板置于内容面板的北部
			jContentPane.add(getBottomPanel(), java.awt.BorderLayout.SOUTH);// 把底部面板置于内容面板的南部
			jContentPane.add(getTablePane(), java.awt.BorderLayout.CENTER);// 把表格面板置于内容面板的中间
		}
		return jContentPane;
	}

	/**
	 * 获得顶部面板的方法（内含组件）
	 * 
	 * @return 顶部面板（内含组件）
	 */
	private JPanel getTopPanel() {
		if (topPanel == null) {// 如果顶部面板不存在
			GridBagConstraints gridBagConstraints21 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints21.fill = GridBagConstraints.BOTH;// 组件水平、垂直同时扩大以占据空白区域
			gridBagConstraints21.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints21.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints21.gridx = 9;// 组件位于网格的横向索引为9
			GridBagConstraints gridBagConstraints = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints.fill = GridBagConstraints.BOTH;// 组件水平、垂直同时扩大以占据空白区域
			gridBagConstraints.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints.gridx = 5;// 组件位于网格的横向索引为5
			GridBagConstraints gridBagConstraints101 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints101.gridx = 8;// 组件位于网格的横向索引为8
			gridBagConstraints101.gridy = 1;// 组件位于网格的纵向索引为1
			jsrLabel = new JLabel();// “经手人：”标签
			jsrLabel.setText("\u7ecf\u624b\u4eba\uff1a");// 设置“经手人：”标签中的文本内容
			GridBagConstraints gridBagConstraints91 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints91.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints91.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints91.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints91.gridx = 5;// 组件位于网格的横向索引为5
			GridBagConstraints gridBagConstraints81 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints81.gridx = 4;// 组件位于网格的横向索引为4
			gridBagConstraints81.gridy = 1;// 组件位于网格的纵向索引为1
			jhsjLabel = new JLabel();// “进货时间：”标签
			jhsjLabel.setText("进货时间：");// 设置“进货时间：”标签中的文本内容
			GridBagConstraints gridBagConstraints71 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints71.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints71.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints71.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints71.gridx = 1;// 组件位于网格的横向索引为1
			GridBagConstraints gridBagConstraints61 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints61.gridx = 0;// 组件位于网格的横向索引为0
			gridBagConstraints61.gridy = 1;// 组件位于网格的纵向索引为1
			jsfsLabel = new JLabel();// “结算方式：”标签
			jsfsLabel.setText("\u7ed3\u7b97\u65b9\u5f0f\uff1a");// 设置“结算方式：”标签中的文本内容
			GridBagConstraints gridBagConstraints51 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints51.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints51.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints51.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints51.gridx = 9;// 组件位于网格的横向索引为9
			GridBagConstraints gridBagConstraints41 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints41.fill = GridBagConstraints.NONE;// 组件不扩大
			gridBagConstraints41.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints41.gridx = 8;// 组件位于网格的横向索引为8
			lxrLabel = new JLabel();// “联系人：”标签
			lxrLabel.setText("\u8054\u7cfb\u4eba\uff1a");// 设置“联系人：”标签中的文本内容
			GridBagConstraints gridBagConstraints25 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints25.gridx = 4;// 组件位于网格的横向索引为4
			gridBagConstraints25.gridy = 0;// 组件位于网格的纵向索引为0
			gysLabel = new JLabel();// “供应商：”标签
			gysLabel.setText("\u4f9b\u5e94\u5546\uff1a");// 设置“供应商：”标签中的文本内容
			GridBagConstraints gridBagConstraints110 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints110.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints110.gridx = 1;// 组件位于网格的横向索引为1
			gridBagConstraints110.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints110.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints110.insets = new Insets(0, 0, 0, 1);// 组件彼此的间距
			GridBagConstraints gridBagConstraints24 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints24.gridx = 0;// 组件位于网格的横向索引为0
			gridBagConstraints24.gridy = 0;// 组件位于网格的纵向索引为0
			idLabel = new JLabel();// “进货票号：”标签
			idLabel.setText("进货票号：");// 设置“进货票号：”标签中的文本内容
			topPanel = new JPanel();// 创建顶部面板
			topPanel.setLayout(new GridBagLayout());// 设置顶部面板的布局为网格布局
			topPanel.add(idLabel, gridBagConstraints24);// 把“进货票号”标签置于网格布局中相应的网格限制对象中
			topPanel.add(getIdField(), gridBagConstraints110);// 把“进货票号”文本框置于网格布局中相应的网格限制对象中
			topPanel.add(gysLabel, gridBagConstraints25);// 把“供应商”标签置于网格布局中相应的网格限制对象中
			topPanel.add(getGysComboBox(), gridBagConstraints);// 把“供应商”下拉列表置于网格布局中相应的网格限制对象中
			topPanel.add(lxrLabel, gridBagConstraints41);// 把“联系人”标签置于网格布局中相应的网格限制对象中
			topPanel.add(getLxrField(), gridBagConstraints51);// 把“联系人”文本框置于网格布局中相应的网格限制对象中
			topPanel.add(jsfsLabel, gridBagConstraints61);// 把“结算方式”标签置于网格布局中相应的网格限制对象中
			topPanel.add(getJsfsComboBox(), gridBagConstraints71);// 把“结算方式”下拉列表置于网格布局中相应的网格限制对象中
			topPanel.add(jhsjLabel, gridBagConstraints81);// 把“进货时间”标签置于网格布局中相应的网格限制对象中
			topPanel.add(getJhsjField(), gridBagConstraints91);// 把“进货时间”文本框置于网格布局中相应的网格限制对象中
			topPanel.add(jsrLabel, gridBagConstraints101);// 把“经手人”标签置于网格布局中相应的网格限制对象中
			topPanel.add(getJsrComboBox(), gridBagConstraints21);// 把“经手人”下拉列表置于网格布局中相应的网格限制对象中
		}
		return topPanel;// 返回顶部面板
	}

	/**
	 * 获得“进货票号”文本框的方法
	 * 
	 * @return “进货票号”文本框
	 */
	private JTextField getIdField() {
		if (idField == null) {// 如果“进货票号”文本框不存在
			idField = new JTextField();// 创建“进货票号”文本框
			idField.setEditable(false);// 设置“进货票号”文本框不可编辑
		}
		return idField;
	}

	/**
	 * 获得“联系人”文本框的方法
	 * 
	 * @return “联系人”文本框
	 */
	private JTextField getLxrField() {
		if (lxrField == null) {// 如果“联系人”文本框不存在
			lxrField = new JTextField();// 创建“联系人”文本框
		}
		return lxrField;
	}

	/**
	 * 获得“计算方式”文本框的方法
	 * 
	 * @return “计算方式”文本框
	 */
	private JComboBox getJsfsComboBox() {
		if (jsfsComboBox == null) {// “结算方式”下拉列表不存在
			jsfsComboBox = new JComboBox();// 创建“结算方式”下拉列表
			jsfsComboBox.addItem("现金结款");// 向“结算方式”下拉列表中添加“现金结款”选项
			jsfsComboBox.addItem("支票结款");// 向“结算方式”下拉列表中添加“支票结款”选项
		}
		return jsfsComboBox;
	}

	/**
	 * 获得“进货时间”文本框的方法
	 * 
	 * @return “进货时间”文本框
	 */
	private JTextField getJhsjField() {
		if (jhsjField == null) {// “进货时间”文本框不存在
			jhsjField = new JTextField();// 创建“进货时间”文本框
		}
		return jhsjField;
	}

	/**
	 * 获得“操作员”文本框的方法
	 * 
	 * @return “操作员”文本框
	 */
	private JTextField getCzyField() {
		if (czyField == null) {// “操作员”文本框不存在
			czyField = new JTextField();// 创建“操作员”文本框
			czyField.setEditable(false);// 设置“操作员”文本框不可编辑
			czyField.setText(MainFrame.getCzyStateLabel().getText());// 设置“操作员”文本框中的文本内容
		}
		return czyField;
	}

	/**
	 * 获得底部面板的方法（内含组件）
	 * 
	 * @return 底部面板（内含组件）
	 */
	private JPanel getBottomPanel() {
		if (bottomPanel == null) {// 如果底部面板不存在
			GridBagConstraints gridBagConstraints2 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints2.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints2.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints2.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints2.gridx = 3;// 组件位于网格的横向索引为3
			GridBagConstraints gridBagConstraints1 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints1.fill = GridBagConstraints.BOTH;// 组件水平、垂直同时扩大以占据空白区域
			gridBagConstraints1.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints1.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints1.gridx = 9;// 组件位于网格的横向索引为9
			GridBagConstraints gridBagConstraints231 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints231.fill = GridBagConstraints.NONE;// 组件不扩大
			gridBagConstraints231.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints231.weightx = 0.3;// 组件横向扩大的权重是0.3
			gridBagConstraints231.gridx = 6;// 组件位于网格的横向索引为6
			GridBagConstraints gridBagConstraints221 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints221.gridx = 5;// 组件位于网格的横向索引为5
			gridBagConstraints221.weightx = 0.3;// 组件横向扩大的权重是0.3
			gridBagConstraints221.gridy = 1;// 组件位于网格的纵向索引为1
			GridBagConstraints gridBagConstraints201 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints201.gridx = 2;// 组件位于网格的横向索引为2
			gridBagConstraints201.gridy = 1;// 组件位于网格的纵向索引为1
			czyLabel = new JLabel();// “操作员”标签
			czyLabel.setText("\u64cd\u4f5c\u5458\uff1a");// 设置“操作员”标签中的文本内容
			GridBagConstraints gridBagConstraints191 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints191.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints191.gridy = 1;// 组件位于网格的纵向索引为1
			gridBagConstraints191.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints191.gridx = 1;// 组件位于网格的横向索引为1
			GridBagConstraints gridBagConstraints181 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints181.gridx = 0;// 组件位于网格的横向索引为0
			gridBagConstraints181.gridy = 1;// 组件位于网格的纵向索引为1
			ysjlLabel = new JLabel();// “验收结论：”标签
			ysjlLabel.setText("\u9a8c\u6536\u7ed3\u8bba\uff1a");// 设置“验收结论：”标签中的文本内容
			GridBagConstraints gridBagConstraints171 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints171.anchor = GridBagConstraints.WEST;// 组件在其显示区域的左中
			gridBagConstraints171.gridwidth = 2;// 组件横跨2个网格
			gridBagConstraints171.gridx = 5;// 组件位于网格的横向索引为5
			gridBagConstraints171.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints171.weightx = 0.6;// 组件横向扩大的权重是0.6
			gridBagConstraints171.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			GridBagConstraints gridBagConstraints161 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints161.gridx = 4;// 组件位于网格的横向索引为4
			gridBagConstraints161.gridy = 0;// 组件位于网格的纵向索引为0
			hjjeLabel = new JLabel();// “合计金额：”标签
			hjjeLabel.setText("\u5408\u8ba1\u91d1\u989d\uff1a");// 设置“合计金额：”标签中的文本内容
			GridBagConstraints gridBagConstraints151 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints151.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints151.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints151.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints151.gridx = 3;// 组件位于网格的横向索引为3
			GridBagConstraints gridBagConstraints141 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints141.gridx = 2;// 组件位于网格的横向索引为2
			gridBagConstraints141.gridy = 0;// 组件位于网格的纵向索引为0
			hpzsLabel = new JLabel();// “货品总数：”标签
			hpzsLabel.setText("\u8d27\u54c1\u603b\u6570\uff1a");// 设置“货品总数：”标签中的文本内容
			GridBagConstraints gridBagConstraints131 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints131.fill = GridBagConstraints.HORIZONTAL;// 组件水平扩大以占据空白区域
			gridBagConstraints131.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints131.weightx = 1.0;// 组件横向扩大的权重是1.0
			gridBagConstraints131.gridx = 1;// 组件位于网格的横向索引为1
			GridBagConstraints gridBagConstraints121 = new GridBagConstraints();// 创建网格限制对象
			gridBagConstraints121.anchor = GridBagConstraints.WEST;// 组件在其显示区域的左中
			gridBagConstraints121.gridy = 0;// 组件位于网格的纵向索引为0
			gridBagConstraints121.gridx = 0;// 组件位于网格的横向索引为0
			pzslLabel = new JLabel();// “品种数量：”标签
			pzslLabel.setText("\u54c1\u79cd\u6570\u91cf\uff1a");// 设置“品种数量：”标签中的文本内容
			bottomPanel = new JPanel();// 创建底部面板
			bottomPanel.setLayout(new GridBagLayout());// 设置底部面板的布局为网格布局
			bottomPanel.add(pzslLabel, gridBagConstraints121);// 把“品种数量”标签置于网格布局中相应的网格限制对象中
			bottomPanel.add(getPzslField(), gridBagConstraints131);// 把“品种数量”文本框置于网格布局中相应的网格限制对象中
			bottomPanel.add(hpzsLabel, gridBagConstraints141);// 把“货品总数：”标签置于网格布局中相应的网格限制对象中
			bottomPanel.add(getHpzsField(), gridBagConstraints151);// 把“货品总数”文本框置于网格布局中相应的网格限制对象中
			bottomPanel.add(hjjeLabel, gridBagConstraints161);// 把“合计金额：”标签置于网格布局中相应的网格限制对象中
			bottomPanel.add(getHjjeField(), gridBagConstraints171);// 把“合计金额”文本框置于网格布局中相应的网格限制对象中
			bottomPanel.add(ysjlLabel, gridBagConstraints181);// 把“验收结论：”标签置于网格布局中相应的网格限制对象中
			bottomPanel.add(getYsjlField(), gridBagConstraints191);// 把“验收结论”文本框置于网格布局中相应的网格限制对象中
			bottomPanel.add(czyLabel, gridBagConstraints201);// 把“操作员：”标签置于网格布局中相应的网格限制对象中
			bottomPanel.add(getCzyField(), gridBagConstraints2);// 把“操作员”文本框置于网格布局中相应的网格限制对象中
			bottomPanel.add(getTjButton(), gridBagConstraints221);// 把“添加”按钮置于网格布局中相应的网格限制对象中
			bottomPanel.add(getRukuButton(), gridBagConstraints231);// 把“入库”按钮置于网格布局中相应的网格限制对象中
		}
		return bottomPanel;// 返回底部面板
	}

	/**
	 * 获得“品种数量”文本框的方法
	 * 
	 * @return “品种数量”文本框
	 */
	private JTextField getPzslField() {
		if (pzslField == null) {// 如果“品种数量”文本框不存在
			pzslField = new JTextField();// 创建“品种数量”文本框
			pzslField.setEditable(false);// 设置“品种数量”文本框不可编辑
		}
		return pzslField;
	}

	/**
	 * 获得“货品总数”文本框的方法
	 * 
	 * @return “货品总数”文本框
	 */
	private JTextField getHpzsField() {
		if (hpzsField == null) {// 如果“货品总数”文本框不存在
			hpzsField = new JTextField();// 创建“货品总数”文本框
			hpzsField.setEditable(false);// 设置“货品总数”文本框不可编辑
		}
		return hpzsField;
	}

	/**
	 * 获得“合计金额”文本框的方法
	 * 
	 * @return “合计金额”文本框
	 */
	private JTextField getHjjeField() {
		if (hjjeField == null) {// 如果“合计金额”文本框不存在
			hjjeField = new JTextField();// 创建“合计金额”文本框
			hjjeField.setEditable(false);// 设置“合计金额”文本框不可编辑
		}
		return hjjeField;
	}

	/**
	 * 获得“验收结论”文本框的方法
	 * 
	 * @return “验收结论”文本框
	 */
	private JTextField getYsjlField() {
		if (ysjlField == null) {// 如果“验收结论”文本框不存在
			ysjlField = new JTextField();// 创建“验收结论”文本框
		}
		return ysjlField;
	}

	/**
	 * 获得“添加”按钮的方法
	 * 
	 * @return “添加”按钮
	 */
	private JButton getTjButton() {
		if (tjButton == null) {// 如果“添加”按钮不存在
			tjButton = new JButton();// 创建“添加”按钮
			tjButton.setText("添加");// 设置“添加”按钮中的文本内容
			tjButton.addActionListener(new ActionListener() {// 为“添加”按钮添加动作事件的监听
				public void actionPerformed(ActionEvent e) {
					java.sql.Date date = new java.sql.Date(jhsjDate.getTime());// 创建日期对象
					jhsjField.setText(date.toString());// 设置“进货时间”文本框中的文本内容
					String maxId = Dao.getRuKuMainMaxId(date);// 获取最大的“进货票号”
					idField.setText(maxId);// 设置“进货票号”文本框中的文本内容
					// 结束表格中没有编写的单元
					stopTableCellEditing();
					// 如果表格中不包含空行，就添加新行
					for (int i = 0; i <= table.getRowCount() - 1; i++) {
						if (table.getValueAt(i, 0) == null)
							return;
					}
					DefaultTableModel model = (DefaultTableModel) table.getModel();// 创建表格对象
					model.addRow(new Vector());// 向表格添加空行
				}
			});
		}
		return tjButton;
	}

	/**
	 * 获得“入库”按钮的方法
	 * 
	 * @return “入库”按钮
	 */
	private JButton getRukuButton() {
		if (rukuButton == null) {// 如果“入库”按钮不存在
			rukuButton = new JButton();// 创建“入库”按钮
			rukuButton.setText("入库");// 设置“入库”按钮中的文本内容
			rukuButton.addActionListener(new java.awt.event.ActionListener() {// 为“入库”按钮添加动作事件的监听
				public void actionPerformed(java.awt.event.ActionEvent e) {
					// 停止表格单元的编辑
					stopTableCellEditing();
					// 清除空行
					clearEmptyRow();
					String pzsStr = pzslField.getText();// 品种数
					String jeStr = hjjeField.getText();// 合计金额
					String jsfsStr = jsfsComboBox.getSelectedItem().toString();// 结算方式
					String jsrStr = jsrComboBox.getSelectedItem() + "";// 经手人
					String czyStr = jsrComboBox.getSelectedItem() + "";// 操作员
					String rkDate = jhsjField.getText();// 入库时间
					String ysjlStr = ysjlField.getText().trim();// 验收结论
					String id = idField.getText();// 票号
					String gysName = gysComboBox.getSelectedItem() + "";// 供应商名字
					if (jsrStr == null || jsrStr.isEmpty()) {// 如果“经手人”下拉列表不存在或“经手人”下拉列表为空
						JOptionPane.showMessageDialog(JinHuoDan_IFrame.this, "请填写经手人");
						return;
					}
					if (ysjlStr == null || ysjlStr.isEmpty()) {// 如果“验收结论”文本框不存在或“验收结论”文本框为空
						JOptionPane.showMessageDialog(JinHuoDan_IFrame.this, "填写验收结论");
						return;
					}
					if (table.getRowCount() <= 0) {// 如果表格模型的行数小于等于0
						JOptionPane.showMessageDialog(JinHuoDan_IFrame.this, "填加入库商品");
						return;
					}
					TbRukuMain ruMain = new TbRukuMain(id, pzsStr, jeStr, ysjlStr, gysName, rkDate, czyStr, jsrStr,
							jsfsStr);// 入库主表
					Set<TbRukuDetail> set = ruMain.getTabRukuDetails();// 入库明细
					int rows = table.getRowCount();// 获得表格模型中的行数
					for (int i = 0; i < rows; i++) {
						TbSpinfo spinfo = (TbSpinfo) table.getValueAt(i, 0);// 商品信息
						if (spinfo == null || spinfo.getId() == null || spinfo.getId().isEmpty())// 商品信息不存在、商品编号不存在或商品编号为空
							continue;// 跳过本次循环，执行下一次循环
						String djStr = (String) table.getValueAt(i, 6);// 单价
						String slStr = (String) table.getValueAt(i, 7);// 数量
						Double dj = Double.valueOf(djStr);// 将String类型的“单价”转换为int型
						Integer sl = Integer.valueOf(slStr);// 将String类型的“数量”转换为int型
						TbRukuDetail detail = new TbRukuDetail();// 入库明细
						detail.setTabSpinfo(spinfo.getId());// 商品信息
						detail.setTabRukuMain(ruMain.getRkId());// 入库主表(入库编号)
						detail.setDj(dj);// 单价
						detail.setSl(sl);// 数量
						set.add(detail);// 添加入库明细
					}
					boolean rs = Dao.insertRukuInfo(ruMain);// 是否成功添加入库信息
					if (rs) {// 成功添加入库信息
						JOptionPane.showMessageDialog(JinHuoDan_IFrame.this, "入库完成");// 弹出提示框
						DefaultTableModel dftm = new DefaultTableModel();// 创建表格默认模型对象
						table.setModel(dftm);// 将表格的数据模型设置为dftm
						pzslField.setText("0");// 设置“品种数量”文本框中的内容为0
						hpzsField.setText("0");// 设置“货品总数”文本框中的内容为0
						hjjeField.setText("0");// 设置“合计金额”文本框中的内容为0
					}
				}
			});
		}
		return rukuButton;
	}

	/**
	 * 获得表格面板的方法
	 * 
	 * @return 表格面板
	 */
	private JScrollPane getTablePane() {
		if (tablePane == null) {// 如果表格面板不存在
			tablePane = new JScrollPane();// 创建表格面板
			tablePane.setViewportView(getTable());// 创建表格模型窗口
		}
		return tablePane;
	}

	/**
	 * 获得表格模型的方法
	 * 
	 * @return 表格模型
	 */
	private JTable getTable() {
		if (table == null) {// 如果表格模型不存在
			String[] columnNames = { "商品名称", "商品编号", "产地", "单位", "规格", "包装", "单价", "数量", "批号", "批准文号" };// 表头
			table = new JTable();// 创建表格模型
			table.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));// 设置表格模型的边框样式
			table.setShowGrid(true);// 绘制网格线
			table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);// 不自动调整列的宽度，使用滚动条
			// 添加事件完成品种数量、货品总数、合计金额的计算
			table.addContainerListener(new computeInfo());
			((DefaultTableModel) table.getModel()).setColumnIdentifiers(columnNames);// 创建表格模型对象并向其中添加表头
			TableColumn column = table.getColumnModel().getColumn(0);// 以表格模型中索引为0的列作参照
			final DefaultCellEditor editor = new DefaultCellEditor(getSpComboBox());// 创建单元格编辑器
			column.setCellEditor(editor);// 编辑参照列中单元格时所用的编辑器
			table.addPropertyChangeListener(new PropertyChangeListener() {
				public void propertyChange(java.beans.PropertyChangeEvent e) {// 为表格添加更改属性的监听事件
					if ((e.getPropertyName().equals("tableCellEditor"))) {
						new computeInfo();// 事件处理器，该处理器用于计算货品总数、合计金额等信息
					}
				}
			});
		}
		return table;
	}

	/**
	 * 获得“商品”下拉列表的方法
	 * 
	 * @return “商品”下拉列表
	 */
	private JComboBox getSpComboBox() {
		if (spComboBox == null) {// 如果“商品”下拉列表不存在
			spComboBox = new JComboBox();// 创建“商品”下拉列表
			spComboBox.addItem(new TbSpinfo());// 向“商品”下拉列表中添加商品信息
			spComboBox.addActionListener(new ActionListener() {// 为“商品”下拉列表添加动作事件的监听
				public void actionPerformed(ActionEvent e) {
					ResultSet set = Dao
							.query("select * from tb_spinfo where gysName='" + getGysComboBox().getSelectedItem() + "'");// 获得供应商信息的集合
					updateSpComboBox(set);// 更新商品下拉列表
				}
			});
			spComboBox.addItemListener(new java.awt.event.ItemListener() {// 为“商品”下拉列表添加选项事件的监听
				public void itemStateChanged(java.awt.event.ItemEvent e) {
					TbSpinfo info = (TbSpinfo) spComboBox.getSelectedItem();// 获得“商品”下拉列表中被选中的商品信息
					// 如果选择有效就更新表格
					if (info != null && info.getId() != null) {
						updateTable();// 更新表格当前行的内容
					}
				}
			});
		}
		return spComboBox;
	}

	/**
	 * 更新商品下拉列表的方法
	 * 
	 * @param set：JDBC返回的ResultSet结果集
	 */
	private void updateSpComboBox(ResultSet set) {
		try {
			while (set.next()) {// 移动后的记录指针指向一条有效的记录
				TbSpinfo spinfo = new TbSpinfo();// 商品信息
				spinfo.setId(set.getString("id").trim());// 商品编号
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
				DefaultComboBoxModel model = (DefaultComboBoxModel) spComboBox.getModel();// “商品”下拉列表的默认模型
				if (model.getIndexOf(spinfo) < 0)// “商品”下拉列表不包含该商品
					spComboBox.addItem(spinfo);// 则添加选项
			}
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}

	/**
	 * 根据商品下拉列表的选择，更新表格当前行的内容
	 */
	private synchronized void updateTable() {
		TbSpinfo spinfo = (TbSpinfo) spComboBox.getSelectedItem();// 获得“商品”下拉列表中被选中的选项
		int row = table.getSelectedRow();// 获得表格模型中被选中的行
		if (row >= 0 && spinfo != null) {// 表格模型中被选中的行大于等于0且“商品”下拉列表中被选中的选项不为空
			// 设置表模型中单元格的值
			table.setValueAt(spinfo.getId(), row, 1);// 商品编号
			table.setValueAt(spinfo.getCd(), row, 2);// 产地
			table.setValueAt(spinfo.getDw(), row, 3);// 商品计量单位
			table.setValueAt(spinfo.getGg(), row, 4);// 商品规格
			table.setValueAt(spinfo.getBz(), row, 5);// 包装
			table.setValueAt("0", row, 6);// 单价
			table.setValueAt("0", row, 7);// 数量
			table.setValueAt(spinfo.getPh(), row, 8);// 批号
			table.setValueAt(spinfo.getPzwh(), row, 9);// 批准文号
			table.editCellAt(row, 6);// 单价可编辑
		}
	}

	/**
	 * 获得“供应商”下拉列表的方法
	 * 
	 * @return “供应商”下拉列表
	 */
	private JComboBox getGysComboBox() {
		if (gysComboBox == null) {// 如果“供应商”下拉列表不存在
			gysComboBox = new JComboBox();// 创建“供应商”下拉列表
			List gysInfos = Dao.getGysInfos();// 获得供应商信息的集合
			for (Iterator iter = gysInfos.iterator(); iter.hasNext();) {// 遍历供应商信息的集合
				List list = (List) iter.next();// 获得迭代的下一个集合
				Item item = new Item();// 数据表公共类
				item.setId(list.get(0).toString().trim());// 编号属性
				item.setName(list.get(1).toString().trim());// 名称信息
				gysComboBox.addItem(item);// 向“供应商”下拉列表中添加选项
			}
			Item item = (Item) gysComboBox.getSelectedItem();// 获得“供应商”下拉列表中被选中的选项
			TbGysinfo gysInfo = Dao.getGysInfo(item);// 供应商信息
			getLxrField().setText(gysInfo.getLian());// 设置“联系人”文本框的文本内容
		}
		return gysComboBox;
	}

	/**
	 * 该方法用于停止表格单元的编辑
	 */
	private void stopTableCellEditing() {
		TableCellEditor cellEditor = table.getCellEditor();// 创建表格单元编辑器
		if (cellEditor != null)// 表格单元编辑器存在
			cellEditor.stopCellEditing();// 停止表格单元的编辑
	}

	/**
	 * 获得“经手人”下拉列表的方法
	 * 
	 * @return “经手人”下拉列表
	 */
	private JComboBox getJsrComboBox() {
		if (jsrComboBox == null) {// 如果“经手人”下拉列表不存在
			jsrComboBox = new JComboBox();// 创建“经手人”下拉列表
			List<List> czyList = Dao.getJsrs();// 获得被启用的经手人集合
			for (List<String> list : czyList) {// 遍历被启用的经手人集合
				String id = list.get(0);// 经手人编号
				String name = list.get(1);// 经手人姓名
				Item item = new Item(id, name);// 数据表公共类
				item.setId(id + "");// 编号属性
				item.setName(name);// 名称信息
				jsrComboBox.addItem(item);// 向“经手人”下拉列表中添加经手人
			}
		}
		return jsrComboBox;
	}

	/**
	 * 事件处理器，该处理器用于计算货品总数、合计金额等信息。
	 */
	private final class computeInfo implements ContainerListener {
		@Override
		public void componentRemoved(ContainerEvent e) {
			// 清除空行
			clearEmptyRow();
			int rows = table.getRowCount();// 获得表格模型中的行数
			int count = 0;// “货品总数”
			double money = 0.0;// “合计金额”
			TbSpinfo column = null;// “商品信息”的实例
			if (rows > 0)// 表格模型中的行数大于0
				column = (TbSpinfo) table.getValueAt(rows - 1, 0);// 为“商品信息”的实例赋值
			if (rows > 0 && (column == null || column.getId().isEmpty()))// 表格模型中的行数大于0且“商品信息”的实例不存在或商品编号为空
				rows--;// 表格模型中的行数减一
			// 计算货品总数和合计金额
			for (int i = 0; i < rows; i++) {
				String column7 = (String) table.getValueAt(i, 7);// 获得表格中“数量”
				String column6 = (String) table.getValueAt(i, 6);// 获得表格中“单价”
				int c7 = (column7 == null || column7.isEmpty()) ? 0 : Integer.parseInt(column7);// 将String类型的“数量”转换为int型
				float c6 = (column6 == null || column6.isEmpty()) ? 0 : Float.parseFloat(column6);// 将String类型的“单价”转换为float型
				count += c7;// 计算货品总数
				money += c6 * c7;// 计算合计金额
			}
			pzslField.setText(rows + "");// 设置“品种数量”文本框中的文本内容
			hpzsField.setText(count + "");// 设置“货品总数”文本框中的文本内容
			hjjeField.setText(money + "");// 设置“合计金额”文本框中的文本内容
		}
		@Override
		public void componentAdded(ContainerEvent e) {
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
}
