-- phpMyAdmin SQL Dump
-- version 3.5.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Sep 19, 2013 at 12:34 AM
-- Server version: 5.1.40-community
-- PHP Version: 5.2.12

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sicamp`
--

-- --------------------------------------------------------

--
-- Table structure for table `referals`
--

CREATE TABLE IF NOT EXISTS `referals` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `parent_id` int(11) NOT NULL,
  `fer_id` int(11) NOT NULL,
  `money` float NOT NULL,
  `time_reg` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `parent_id` (`parent_id`,`fer_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=23 ;

--
-- Dumping data for table `referals`
--

INSERT INTO `referals` (`id`, `parent_id`, `fer_id`, `money`, `time_reg`) VALUES
(2, 1, 1, 5.6, '2013-07-18 10:42:12'),
(3, 1, 11, 5.6, '2013-07-18 10:43:32'),
(4, 1, 3, 5.6, '2013-07-18 10:43:32'),
(5, 1, 4, 5.6, '2013-07-18 10:43:32'),
(6, 1, 5, 5.6, '2013-07-18 10:43:32'),
(7, 1, 6, 5.6, '2013-07-18 10:43:32'),
(8, 1, 7, 5.6, '2013-07-18 10:43:32'),
(9, 1, 8, 5.6, '2013-07-18 10:43:32'),
(10, 1, 9, 5.6, '2013-07-18 10:43:32'),
(11, 1, 10, 5.6, '2013-07-18 10:43:32'),
(12, 1, 12, 5.6, '2013-07-18 10:43:32'),
(13, 2, 11, 5.6, '2013-07-18 10:43:53'),
(14, 2, 3, 5.6, '2013-07-18 10:43:53'),
(15, 2, 4, 5.6, '2013-07-18 10:43:53'),
(16, 2, 5, 5.6, '2013-07-18 10:43:53'),
(17, 2, 6, 5.6, '2013-07-18 10:43:53'),
(18, 2, 7, 5.6, '2013-07-18 10:43:53'),
(19, 2, 8, 5.6, '2013-07-18 10:43:53'),
(20, 2, 9, 5.6, '2013-07-18 10:43:53'),
(21, 2, 10, 5.6, '2013-07-18 10:43:53'),
(22, 2, 12, 5.6, '2013-07-18 10:43:53');

-- --------------------------------------------------------

--
-- Table structure for table `sys_components`
--

CREATE TABLE IF NOT EXISTS `sys_components` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `key` varchar(255) NOT NULL,
  `caption` varchar(255) NOT NULL,
  `order` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `sys_components`
--

INSERT INTO `sys_components` (`id`, `key`, `caption`, `order`) VALUES
(1, 'allgrps', 'Все группы', 1),
(2, 'lstgrps', 'Список групп', 2),
(3, 'group', 'Редактирование групп', 3),
(4, 'data', 'Ввод данных', 4);

-- --------------------------------------------------------

--
-- Table structure for table `tbl_admin`
--

CREATE TABLE IF NOT EXISTS `tbl_admin` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `active` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `tbl_admin`
--

INSERT INTO `tbl_admin` (`id`, `login`, `password`, `active`) VALUES
(1, 'demo', 'c514c91e4ed341f263e458d44b3bb0a7', 1);

-- --------------------------------------------------------

--
-- Table structure for table `tbl_criteria`
--

CREATE TABLE IF NOT EXISTS `tbl_criteria` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `order` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `tbl_criteria`
--

INSERT INTO `tbl_criteria` (`id`, `name`, `order`) VALUES
(1, 'Описание проблемы', 1),
(2, 'Механизм реализации', 2),
(3, 'Сроки реализации', 3),
(4, 'Тахнологическое решение', 4),
(5, 'Сообщества пользователей', 5),
(6, 'Информационная компания', 6),
(7, 'Устойчивость проекта', 7),
(8, 'Бюджет проекта', 8);

-- --------------------------------------------------------

--
-- Table structure for table `tbl_donejob`
--

CREATE TABLE IF NOT EXISTS `tbl_donejob` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `criteria_id` int(11) NOT NULL,
  `group_id` int(11) NOT NULL,
  `timeline_num` int(11) NOT NULL,
  `done` float NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `criteria_id` (`criteria_id`,`group_id`,`timeline_num`),
  KEY `criteria_id_2` (`criteria_id`),
  KEY `group_id` (`group_id`),
  KEY `timeline_num` (`timeline_num`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tbl_group`
--

CREATE TABLE IF NOT EXISTS `tbl_group` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `head` varchar(255) NOT NULL,
  `deleted` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=14 ;

--
-- Dumping data for table `tbl_group`
--

INSERT INTO `tbl_group` (`id`, `name`, `head`, `deleted`) VALUES
(1, 'Группа 1', 'Саид Умар ибн Фатх', 0),
(2, 'Группа 2', 'Глава группы 2', 0),
(3, 'Группа 3', 'Глава группы 3', 0),
(4, 'Группа 4', 'Глава группы 4', 0),
(5, 'Группа 5', 'Глава группы 5', 0),
(6, 'Группа 6', 'Глава группы 6', 0),
(7, 'Группа 7', 'Глава группы 7', 0),
(8, 'Группа 8', 'Глава группы 8', 0),
(9, 'Группа 9', 'Глава группы 9', 0),
(10, 'Группа 10', 'Глава группы 10', 0),
(13, 'Group_test', 'test', 1);

-- --------------------------------------------------------

--
-- Table structure for table `tbl_timeline`
--

CREATE TABLE IF NOT EXISTS `tbl_timeline` (
  `num` int(11) NOT NULL AUTO_INCREMENT,
  `day` tinyint(4) NOT NULL,
  `hour` varchar(50) NOT NULL,
  PRIMARY KEY (`num`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

--
-- Dumping data for table `tbl_timeline`
--

INSERT INTO `tbl_timeline` (`num`, `day`, `hour`) VALUES
(1, 30, '11:00'),
(2, 30, '13:00'),
(3, 30, '17:00'),
(4, 30, '19:00'),
(5, 1, '11:00'),
(6, 1, '13:00'),
(7, 1, '17:00'),
(8, 1, '19:00'),
(9, 2, '11:00'),
(10, 2, '13:00'),
(11, 2, '17:00');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
