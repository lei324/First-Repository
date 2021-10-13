-- MySQL dump 10.13  Distrib 5.5.13, for Win32 (x86)
--
-- Host: localhost    Database: db_database28
-- ------------------------------------------------------
-- Server version	5.5.13

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tb_gysinfo`
--

DROP TABLE IF EXISTS `tb_gysinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_gysinfo` (
  `id` varchar(50) NOT NULL,
  `name` varchar(60) NOT NULL,
  `jc` varchar(50) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `bianma` varchar(50) DEFAULT NULL,
  `tel` varchar(50) DEFAULT NULL,
  `fax` varchar(50) DEFAULT NULL,
  `lian` varchar(50) DEFAULT NULL,
  `ltel` varchar(50) DEFAULT NULL,
  `yh` varchar(50) DEFAULT NULL,
  `mail` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_gysinfo`
--

LOCK TABLES `tb_gysinfo` WRITE;
/*!40000 ALTER TABLE `tb_gysinfo` DISABLE KEYS */;
INSERT INTO `tb_gysinfo` VALUES ('gys1007','***供应商公司','GYS','长春市二道区','130031','2132','1111','32121','231231','231213','231231'),('gys1002','新*纪文化百货商城','新百','吉林省辽源市','1363','0437-6930**','52186**','于X','138686*****','中国人民银行','y*@etang.com'),('gys1004','吉林省明日*业有限公司','JLMRSY','长春市东盛大街89号','','0431-4972**','','ww','','',''),('gys1005','笔*有限公司','BHYXGS','长在市','1111','1212','2151','毛皮','44411','8*@1*.com','8885');
/*!40000 ALTER TABLE `tb_gysinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_jsr`
--

DROP TABLE IF EXISTS `tb_jsr`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_jsr` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `sex` char(2) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `tel` varchar(20) DEFAULT NULL,
  `enable` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_jsr`
--

LOCK TABLES `tb_jsr` WRITE;
/*!40000 ALTER TABLE `tb_jsr` DISABLE KEYS */;
INSERT INTO `tb_jsr` VALUES (3,'lx','女',25,'136******',0),(4,'liuxin','男',25,'136******',1);
/*!40000 ALTER TABLE `tb_jsr` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_khinfo`
--

DROP TABLE IF EXISTS `tb_khinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_khinfo` (
  `id` varchar(50) NOT NULL,
  `khname` varchar(50) DEFAULT NULL,
  `jian` varchar(50) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `bianma` varchar(50) DEFAULT NULL,
  `tel` varchar(50) DEFAULT NULL,
  `fax` varchar(50) DEFAULT NULL,
  `lian` varchar(50) DEFAULT NULL,
  `ltel` varchar(50) DEFAULT NULL,
  `mail` varchar(50) DEFAULT NULL,
  `xinhang` varchar(60) DEFAULT NULL,
  `hao` varchar(60) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_khinfo`
--

LOCK TABLES `tb_khinfo` WRITE;
/*!40000 ALTER TABLE `tb_khinfo` DISABLE KEYS */;
INSERT INTO `tb_khinfo` VALUES ('kh1001','明日科技有限公司','明日','长春市东盛大街','111111','111111','111111','高经理','544444','888@**.com','544554','454545'),('kh1002','吉林省明日科技有限公司','明日科技','长春市二道区','1111110','52415','54252','高经理','136524','mingrisoft@mingrisoft.com.cn','建设银\n行','231586'),('kh1003','五*缤纷','五彩','长春市','122','45644','8888','路路','1000402','0*@*4.com','25250','020202'),('kh1004','小小公司','XXGS','长春市','1010','1111','1111','明子','121212','88*@.com','8888','88');
/*!40000 ALTER TABLE `tb_khinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_kucun`
--

DROP TABLE IF EXISTS `tb_kucun`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_kucun` (
  `id` varchar(30) NOT NULL DEFAULT '',
  `spname` varchar(50) NOT NULL,
  `jc` varchar(25) DEFAULT NULL,
  `cd` varchar(50) DEFAULT NULL,
  `gg` varchar(50) DEFAULT NULL,
  `bz` varchar(50) DEFAULT NULL,
  `dw` varchar(10) DEFAULT NULL,
  `dj` decimal(10,2) DEFAULT NULL,
  `kcsl` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_kucun`
--

LOCK TABLES `tb_kucun` WRITE;
/*!40000 ALTER TABLE `tb_kucun` DISABLE KEYS */;
INSERT INTO `tb_kucun` VALUES ('sp1005','润*滴眼液','RZDYY','山*正大福*达制药有限公司','10ml/支','纸盒','盒',40.00,19400),('sp1007','铅笔','QB','长春','9*','沿着','铅笔厂',10.00,4),('sp1008','手工艺品','SAYP','长春市','1','5','长春',10.00,999),('sp1003','碧**莉香型洗衣粉','BLMLXXXYF','广**保洁公司','350g','塑包','袋',0.00,6);
/*!40000 ALTER TABLE `tb_kucun` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_rkth_detail`
--

DROP TABLE IF EXISTS `tb_rkth_detail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_rkth_detail` (
  `rkthID` varchar(30) NOT NULL,
  `spid` varchar(50) NOT NULL,
  `dj` decimal(10,2) NOT NULL,
  `sl` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_rkth_detail`
--

LOCK TABLES `tb_rkth_detail` WRITE;
/*!40000 ALTER TABLE `tb_rkth_detail` DISABLE KEYS */;
INSERT INTO `tb_rkth_detail` VALUES ('RT20050923001','sp1003',3.50,1),('RT20050926001','sp1003',3.40,10),('RT20051005002','sp1003',3.40,1),('RT20051005002','sp1002',890.00,1),('RT20071020001','sp1005',431.00,10),('RT20071020001','sp1004',120.00,2),('RT20071109001','sp1001',101.00,1000),('RT20071109002','sp1005',40.00,10),('RT20080403001','sp1002',23.00,462),('RT20080410005','sp1002',432.00,0),('RT20080521001','sp1007',10.00,5);
/*!40000 ALTER TABLE `tb_rkth_detail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_rkth_main`
--

DROP TABLE IF EXISTS `tb_rkth_main`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_rkth_main` (
  `rkthID` varchar(30) NOT NULL,
  `pzs` float NOT NULL,
  `je` decimal(10,2) NOT NULL,
  `ysjl` varchar(50) DEFAULT NULL,
  `gysname` varchar(100) NOT NULL,
  `rtdate` datetime NOT NULL,
  `czy` varchar(30) NOT NULL,
  `jsr` varchar(30) NOT NULL,
  `jsfs` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_rkth_main`
--

LOCK TABLES `tb_rkth_main` WRITE;
/*!40000 ALTER TABLE `tb_rkth_main` DISABLE KEYS */;
INSERT INTO `tb_rkth_main` VALUES ('RT20050923001',1,3.50,'3.50','新*纪文化百货商城','2005-09-23 15:19:24','admin','wgh','现金'),('RT20050926001',1,34.00,'0.00','振撼*琴行','2005-09-26 14:01:48','admin','wg','现金'),('RT20051005001',1,3.40,'0.00','振撼*琴行','2005-10-05 09:09:34','admin','hj','现金'),('RT20051005002',2,893.40,'0.00','振撼*琴行','2005-10-05 13:05:35','admin','wq','现金'),('RT20071020001',2,4550.00,'33333','振撼*琴行','2007-10-20 09:10:49','mr','33333','现金'),('RT20071109001',1,101000.00,'合格','振撼*琴行','2007-11-09 14:32:39','mr','00','现金'),('RT20071109002',1,400.00,'质量有问题','振撼*琴行','2007-11-09 15:50:03','mr','11','现金'),('RT20080403001',1,10626.00,'4444','新*纪文化百货商城','2008-04-03 15:52:16','','44','现金'),('RT20080410001',1,432.00,'1','新*纪文化百货商城','2008-04-10 10:33:51','','1','现金'),('RT20080410002',1,0.00,'12','新*纪文化百货商城','2008-04-10 10:37:56','tsoft','范德萨','现金'),('RT20080410003',1,-432.00,'12','新*纪文化百货商城','2008-04-10 10:38:23','tsoft','范德萨','现金'),('RT20080521001',1,50.00,'合格','新*纪文化百货商城','2008-05-21 14:47:37','tsoft','范德萨','现金'),('RT20080410004',1,0.00,'12','新*纪文化百货商城','2008-04-10 10:39:13','tsoft','范德萨','现金'),('RT20080410005',1,0.00,'12','新*纪文化百货商城','2008-04-10 10:40:31','tsoft','范德萨','现金');
/*!40000 ALTER TABLE `tb_rkth_main` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_ruku_detail`
--

DROP TABLE IF EXISTS `tb_ruku_detail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_ruku_detail` (
  `rkID` varchar(30) NOT NULL,
  `spid` varchar(50) NOT NULL,
  `dj` decimal(10,2) NOT NULL,
  `sl` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_ruku_detail`
--

LOCK TABLES `tb_ruku_detail` WRITE;
/*!40000 ALTER TABLE `tb_ruku_detail` DISABLE KEYS */;
INSERT INTO `tb_ruku_detail` VALUES ('RK20071016001','sp1004',12.00,1142),('RK20071016001','sp1001',10.00,100),('RK20071016002','sp1001',10.00,400),('RK20071016003','sp1005',10.00,400),('RK20071016003','sp1001',10.00,500),('RK20071016004','sp1005',10.00,100),('RK20071016004','sp1001',10.00,10),('RK20071016005','sp1004',10.00,110),('RK20071016005','sp1005',100.00,1000),('RK20071016006','sp1004',321.00,432),('RK20071016006','sp1005',432.00,3330),('RK20071020001','sp1004',12.00,232),('RK20071109001','sp1002',22.00,22),('RK20071109002','sp1007',10.00,10),('RK20071109003','sp1005',40.00,100),('RK20071112001','sp1008',10.00,1000),('RK20080403001','sp1002',43.00,32),('RK20080403002','sp1002',23.00,430),('RK20080410007','sp1003',3.00,2),('RK20080410008','sp1002',432.00,432),('RK20080410009','sp1003',0.00,0),('RK20080521001','sp1007',10.00,10),('RK20100209001','sp1009',1.00,100),('RK20080410009','sp1007',0.00,0);
/*!40000 ALTER TABLE `tb_ruku_detail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_ruku_main`
--

DROP TABLE IF EXISTS `tb_ruku_main`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_ruku_main` (
  `rkID` varchar(30) NOT NULL,
  `pzs` int(11) NOT NULL,
  `je` decimal(10,2) NOT NULL,
  `ysjl` varchar(50) NOT NULL,
  `gysname` varchar(100) NOT NULL,
  `rkdate` datetime NOT NULL,
  `czy` varchar(30) NOT NULL,
  `jsr` varchar(30) NOT NULL,
  `jsfs` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_ruku_main`
--

LOCK TABLES `tb_ruku_main` WRITE;
/*!40000 ALTER TABLE `tb_ruku_main` DISABLE KEYS */;
INSERT INTO `tb_ruku_main` VALUES ('RK20071016001',2,14704.00,'合格','振撼*琴行','2007-10-16 10:32:26','测试人员','某人','现金'),('RK20071016002',1,4000.00,'合格','振撼*琴行','2007-10-16 10:39:28','测试人员','小小','现金'),('RK20071016003',2,9000.00,'合格','振撼*琴行','2007-10-16 10:40:00','测试人员','小小','现金'),('RK20071016004',2,1100.00,'1111','振撼*琴行','2007-10-16 10:42:18','测试人员','1111','现金'),('RK20071016005',2,101100.00,'fdsa','振撼*琴行','2007-10-16 10:45:14','测试人员','fds','现金'),('RK20071016006',2,1577232.00,'fdsa','振撼*琴行','2007-10-16 10:45:31','测试人员','fds','现金'),('RK20071020001',1,2784.00,'fff','振撼*琴行','2007-10-20 09:04:36','mr','lzw','现金'),('RK20071109001',1,484.00,'合格','新*纪文化百货商城','2007-11-09 14:27:56','mr','玲子','现金'),('RK20071109002',1,100.00,'合格','新*纪文化百货商城','2007-11-09 14:28:24','mr','玲子','现金'),('RK20071109003',1,4000.00,'合格','振撼*琴行','2007-11-09 15:49:32','mr','小百','现金'),('RK20071112001',1,10000.00,'010','吉林省明日*业有限公司','2007-11-12 10:47:31','mr','11','现金'),('RK20080403001',1,1376.00,'ds','新*纪文化百货商城','2008-04-03 00:00:00','null','ggf','现金结款'),('RK20080403002',1,9890.00,'ftf','新*纪文化百货商城','2008-04-03 00:00:00','小陈','33','现金结款'),('RK20080410001',1,0.00,'23','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410002',1,0.00,'543','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410003',1,8.00,'111','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410004',1,2795.00,'432','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410007',1,6.00,'2321','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410008',1,186624.00,'32','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080521001',1,100.00,'合格','新*纪文化百货商城','2008-05-21 00:00:00','范德萨','范德萨','现金结款'),('RK20100209001',1,100.00,'10','笔*有限公司','2010-02-09 00:00:00','liuxin','liuxin','现金结款'),('RK20080410005',1,0.00,'g','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410006',1,736.00,'111','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款'),('RK20080410009',2,0.00,'22','新*纪文化百货商城','2008-04-10 00:00:00','范德萨','范德萨','现金结款');
/*!40000 ALTER TABLE `tb_ruku_main` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_sell_detail`
--

DROP TABLE IF EXISTS `tb_sell_detail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_sell_detail` (
  `sellID` varchar(30) NOT NULL,
  `spid` varchar(50) NOT NULL,
  `dj` decimal(10,2) NOT NULL,
  `sl` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_sell_detail`
--

LOCK TABLES `tb_sell_detail` WRITE;
/*!40000 ALTER TABLE `tb_sell_detail` DISABLE KEYS */;
INSERT INTO `tb_sell_detail` VALUES ('XS20050923001','sp1003',3.50,1),('XS20050923001','sp1001',789.00,1),('XS20050923002','sp1003',3.50,2),('XS20050926001','sp1005',10.00,1),('XS20051004001','sp1005',8.70,2),('XS20050104001','sp1002',890.00,1),('XS20050104002','sp1002',890.00,1),('XS20050120001','sp1002',890.00,1),('XS20050220001','sp1002',890.00,1),('XS20051004002','sp1002',890.00,1),('XS20051004003','sp1005',8.70,2),('XS20051004004','sp1003',3.40,4),('XS20050309001','sp1001',1500.00,1),('XS20050309002','sp1002',890.00,1),('XS20050309002','sp1001',1500.00,1),('XS20051005001','sp1001',1500.00,1),('XS20051005002','sp1002',890.00,1),('XS20051005002','sp1005',8.70,1),('XS20051005003','sp1003',3.40,1),('XS20051005004','sp1004',790.00,1),('XS20051005004','sp1001',1500.00,1),('XS20051006001','sp1003',3.40,1),('XS20071016001','sp1004',321.00,16),('XS20071017001','sp1004',321.00,1668),('XS20071109001','sp1007',10.00,5),('XS20071115001','sp1002',22.00,22),('XS20080410003','sp1002',432.00,0),('XS20080521001','sp1007',10.00,1),('XS20150507001','sp1009',1.00,200),('XS20150507002','sp1008',10.00,1),('XS20150507002','sp1007',10.00,1),('XS20150507002','sp1009',1.00,3);
/*!40000 ALTER TABLE `tb_sell_detail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_sell_main`
--

DROP TABLE IF EXISTS `tb_sell_main`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_sell_main` (
  `sellID` varchar(30) NOT NULL,
  `pzs` int(11) NOT NULL,
  `je` decimal(10,2) NOT NULL,
  `ysjl` varchar(50) DEFAULT NULL,
  `khname` varchar(100) NOT NULL,
  `xsdate` datetime NOT NULL,
  `czy` varchar(30) NOT NULL,
  `jsr` varchar(30) NOT NULL,
  `jsfs` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_sell_main`
--

LOCK TABLES `tb_sell_main` WRITE;
/*!40000 ALTER TABLE `tb_sell_main` DISABLE KEYS */;
INSERT INTO `tb_sell_main` VALUES ('XS20050104001',1,890.00,'100.00','新*纪文化百货用品商城','2005-01-04 15:27:48','admin','gh','现金'),('XS20050104002',1,890.00,'100.00','新*纪文化百货用品商城','2005-01-04 15:28:10','admin','wg','现金'),('XS20050120001',1,890.00,'200.00','新*纪文化百货用品商城','2005-01-20 15:28:51','admin','g','现金'),('XS20050220001',1,890.00,'100.00','新*纪文化百货用品商城','2005-02-20 15:29:31','admin','gh','现金'),('XS20050309001',1,1500.00,'0.00','新*纪文化百货用品商城','2005-03-09 15:42:32','admin','kk','现金'),('XS20050309002',2,2390.00,'2000.00','新*纪文化百货用品商城','2005-03-09 17:20:00','admin','言','现金'),('XS20050923001',2,792.50,'792.50','新*纪文化百货用品商城','2005-09-23 13:12:45','admin','wgh','现金'),('XS20050923002',1,7.00,'7.00','新*纪文化百货用品商城','2005-09-23 13:13:04','admin','wgh','现金'),('XS20050926001',1,10.00,'10.00','新*纪文化百货用品商城','2005-09-26 13:58:30','admin','wgh','现金'),('XS20051004001',1,17.40,'17.40','新*纪文化百货用品商城','2005-10-04 13:19:03','admin','wgh','现金'),('XS20051004002',1,890.00,'0.00','新*纪文化百货用品商城','2005-10-04 15:30:04','admin','wgh','现金'),('XS20051004003',1,17.40,'0.00','新*纪文化百货用品商城','2005-10-04 15:30:23','admin','gh','现金'),('XS20051004004',1,13.60,'0.00','新*纪文化百货用品商城','2005-10-04 15:31:38','admin','w','现金'),('XS20051005001',1,1500.00,'0.00','新*纪文化百货用品商城','2005-10-05 08:24:02','admin','ttt','现金'),('XS20051005002',2,898.70,'0.00','新*纪文化百货用品商城','2005-10-05 08:24:28','admin','eee','现金'),('XS20051005003',1,3.40,'3.40','新*纪文化百货用品商城','2005-10-05 08:41:07','admin','ww','现金'),('XS20051005004',2,2290.00,'2000.00','新*纪文化百货用品商城','2005-10-05 08:42:29','admin','eutwin','现金'),('XS20051006001',1,3.40,'2.40','新*纪文化百货用品商城','2005-10-06 08:54:38','yan','yyy','现金'),('XS20071016001',1,5136.00,'fds','明日科技有限公司','2007-10-16 17:00:08','测试人员','伙','现金'),('XS20071017001',1,535428.00,'4321','明日科技有限公司','2007-10-17 08:49:34','测试人员','4321','现金'),('XS20071109001',1,50.00,'合格','明日科技有限公司','2007-11-09 14:41:40','mr','小刘','现金'),('XS20071115001',1,484.00,'ggg','明日科技有限公司','2007-11-15 18:41:15','mr','00','现金'),('XS20080410001',2,219024.00,'e2','明日科技有限公司','2008-04-10 10:26:47','','范德萨','现金'),('XS20080410002',1,0.00,'e2','明日科技有限公司','2008-04-10 10:27:51','','范德萨','现金'),('XS20080410003',1,0.00,'e2','明日科技有限公司','2008-04-10 10:28:54','','范德萨','现金'),('XS20080521001',1,10.00,'10','明日科技有限公司','2008-05-21 14:57:55','tsoft','范德萨','现金'),('XS20150507001',1,200.00,'测试是否会出库大于库存','明日科技有限公司','2015-05-07 15:44:33','tsoft','liuxin','现金'),('XS20150507002',3,23.00,'1111111111111','明日科技有限公司','2015-05-07 16:31:10','tsoft','liuxin','现金');
/*!40000 ALTER TABLE `tb_sell_main` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_spinfo`
--

DROP TABLE IF EXISTS `tb_spinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_spinfo` (
  `id` varchar(50) NOT NULL,
  `spname` varchar(50) NOT NULL,
  `jc` varchar(50) DEFAULT NULL,
  `cd` varchar(60) DEFAULT NULL,
  `dw` varchar(50) NOT NULL,
  `gg` varchar(50) NOT NULL,
  `bz` varchar(50) DEFAULT NULL,
  `ph` varchar(50) DEFAULT NULL,
  `pzwh` varchar(50) DEFAULT NULL,
  `memo` varchar(90) DEFAULT NULL,
  `gysname` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_spinfo`
--

LOCK TABLES `tb_spinfo` WRITE;
/*!40000 ALTER TABLE `tb_spinfo` DISABLE KEYS */;
INSERT INTO `tb_spinfo` VALUES ('sp1001','电吉他','吉他1','中**连','把','FD－3100','盒','56217','23232','无限延音功能、自带效果器','新*纪文化百货商城'),('sp1002','木吉他','吉他','中**海','把','HM2100','盒','32286','875845624','可接电','新*纪文化百货商城'),('sp1005','润*滴眼液','RZDYY','山*正大福*达制药有限公司','盒','10ml/支','纸盒','20040728','鲁*消备字','','振撼*琴行'),('sp1006','电吉他','电吉他','电吉他','电吉他','电吉他','','','','',''),('sp1007','铅笔','QB','长春','铅笔厂','9*','沿着','14**','222**','无','新*纪文化百货商城'),('sp1008','手工艺品','SAYP','长春市','长春','1','5','25','212','很不错','吉林省明日*业有限公司'),('sp1009','锅巴','锅巴','吉林','袋','200G/袋','袋','001','2131213','无','笔*有限公司');
/*!40000 ALTER TABLE `tb_spinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_userlist`
--

DROP TABLE IF EXISTS `tb_userlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_userlist` (
  `name` varchar(30) NOT NULL,
  `pass` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_userlist`
--

LOCK TABLES `tb_userlist` WRITE;
/*!40000 ALTER TABLE `tb_userlist` DISABLE KEYS */;
INSERT INTO `tb_userlist` VALUES ('tsoft','111');
/*!40000 ALTER TABLE `tb_userlist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_xsth_detail`
--

DROP TABLE IF EXISTS `tb_xsth_detail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_xsth_detail` (
  `xsthID` varchar(30) NOT NULL,
  `spid` varchar(50) NOT NULL,
  `dj` decimal(10,2) NOT NULL,
  `sl` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_xsth_detail`
--

LOCK TABLES `tb_xsth_detail` WRITE;
/*!40000 ALTER TABLE `tb_xsth_detail` DISABLE KEYS */;
INSERT INTO `tb_xsth_detail` VALUES ('XT20051005001','sp1004',790.00,1),('XT20051005002','sp1002',890.00,1),('XT20051005003','sp1002',890.00,1),('XT20051216001','sp1004',790.00,1),('XT20071017001','sp1005',432.00,4830),('XT20071017002','sp1005',432.00,9660),('XT20071109001','sp1007',10.00,1),('XT20080410001','sp1001',151.00,-1000),('XT20080521001','sp1007',10.00,1);
/*!40000 ALTER TABLE `tb_xsth_detail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_xsth_main`
--

DROP TABLE IF EXISTS `tb_xsth_main`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_xsth_main` (
  `xsthID` varchar(30) NOT NULL,
  `pzs` int(11) NOT NULL,
  `je` decimal(10,2) NOT NULL,
  `ysjl` varchar(50) DEFAULT NULL,
  `khname` varchar(100) NOT NULL,
  `thdate` datetime NOT NULL,
  `czy` varchar(30) NOT NULL,
  `jsr` varchar(30) NOT NULL,
  `jsfs` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_xsth_main`
--

LOCK TABLES `tb_xsth_main` WRITE;
/*!40000 ALTER TABLE `tb_xsth_main` DISABLE KEYS */;
INSERT INTO `tb_xsth_main` VALUES ('XT20051005001',1,790.00,'0.00','新*纪文化百货用品商城','2005-10-05 13:17:31','admin','jh','现金'),('XT20051005002',1,890.00,'90.00','新*纪文化百货用品商城','2005-10-05 13:25:52','admin','hj','现金'),('XT20051005003',1,890.00,'0.00','新*纪文化百货用品商城','2005-10-05 13:32:38','admin','wgh','现金'),('XT20051216001',1,790.00,'90.00','新*纪文化百货用品商城','2005-12-16 17:24:46','admin','kk','现金'),('XT20071017001',1,2086560.00,'432','明日科技有限公司','2007-10-17 08:50:05','测试人员','432','现金'),('XT20071017002',1,4173120.00,'432','明日科技有限公司','2007-10-17 08:50:12','测试人员','432','现金'),('XT20071109001',1,10.00,'不合格','明日科技有限公司','2007-11-09 14:42:12','mr','99','现金'),('XT20080410001',1,-151000.00,'321','明日科技有限公司','2008-04-10 10:34:27','tsoft','范德萨','现金'),('XT20080521001',1,10.00,'10','明日科技有限公司','2008-05-21 14:58:18','tsoft','范德萨','现金');
/*!40000 ALTER TABLE `tb_xsth_main` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `v_rukuview`
--

DROP TABLE IF EXISTS `v_rukuview`;
/*!50001 DROP VIEW IF EXISTS `v_rukuview`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `v_rukuview` (
  `rkID` varchar(30),
  `spid` varchar(50),
  `spname` varchar(50),
  `gg` varchar(50),
  `dj` decimal(10,2),
  `sl` int(11),
  `je` decimal(20,2),
  `gysname` varchar(100),
  `rkdate` datetime,
  `czy` varchar(30),
  `jsr` varchar(30),
  `jsfs` varchar(10)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `v_sellview`
--

DROP TABLE IF EXISTS `v_sellview`;
/*!50001 DROP VIEW IF EXISTS `v_sellview`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `v_sellview` (
  `sellID` varchar(30),
  `spname` varchar(50),
  `spid` varchar(50),
  `gg` varchar(50),
  `dj` decimal(10,2),
  `sl` float,
  `je` double,
  `khname` varchar(100),
  `xsdate` datetime,
  `czy` varchar(30),
  `jsr` varchar(30),
  `jsfs` varchar(10)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Final view structure for view `v_rukuview`
--

/*!50001 DROP TABLE IF EXISTS `v_rukuview`*/;
/*!50001 DROP VIEW IF EXISTS `v_rukuview`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `v_rukuview` AS select `tb_ruku_main`.`rkID` AS `rkID`,`tb_ruku_detail`.`spid` AS `spid`,`tb_spinfo`.`spname` AS `spname`,`tb_spinfo`.`gg` AS `gg`,`tb_ruku_detail`.`dj` AS `dj`,`tb_ruku_detail`.`sl` AS `sl`,(`tb_ruku_detail`.`dj` * `tb_ruku_detail`.`sl`) AS `je`,`tb_spinfo`.`gysname` AS `gysname`,`tb_ruku_main`.`rkdate` AS `rkdate`,`tb_ruku_main`.`czy` AS `czy`,`tb_ruku_main`.`jsr` AS `jsr`,`tb_ruku_main`.`jsfs` AS `jsfs` from ((`tb_ruku_detail` join `tb_ruku_main` on((`tb_ruku_detail`.`rkID` = `tb_ruku_main`.`rkID`))) join `tb_spinfo` on((`tb_ruku_detail`.`spid` = `tb_spinfo`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `v_sellview`
--

/*!50001 DROP TABLE IF EXISTS `v_sellview`*/;
/*!50001 DROP VIEW IF EXISTS `v_sellview`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `v_sellview` AS select `tb_sell_main`.`sellID` AS `sellID`,`tb_spinfo`.`spname` AS `spname`,`tb_sell_detail`.`spid` AS `spid`,`tb_spinfo`.`gg` AS `gg`,`tb_sell_detail`.`dj` AS `dj`,`tb_sell_detail`.`sl` AS `sl`,(`tb_sell_detail`.`sl` * `tb_sell_detail`.`dj`) AS `je`,`tb_sell_main`.`khname` AS `khname`,`tb_sell_main`.`xsdate` AS `xsdate`,`tb_sell_main`.`czy` AS `czy`,`tb_sell_main`.`jsr` AS `jsr`,`tb_sell_main`.`jsfs` AS `jsfs` from ((`tb_sell_detail` join `tb_sell_main` on((`tb_sell_detail`.`sellID` = `tb_sell_main`.`sellID`))) join `tb_spinfo` on((`tb_sell_detail`.`spid` = `tb_spinfo`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-06-22 11:41:33
