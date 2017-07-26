-- phpMyAdmin SQL Dump
-- version 4.0.10.17
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 26, 2017 at 05:32 AM
-- Server version: 5.5.41-MariaDB
-- PHP Version: 5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `phishing_platformdb`
--

-- --------------------------------------------------------

--
-- Table structure for table `tblHumanResultNonPhishing`
--

CREATE TABLE IF NOT EXISTS `tblHumanResultNonPhishing` (
  `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `HostNameOnly` tinyint(3) unsigned DEFAULT '0',
  `DateAdd` decimal(12,0) NOT NULL,
  PRIMARY KEY (`EventId`)
) ENGINE=MEMORY DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblHumanResultPhishing`
--

CREATE TABLE IF NOT EXISTS `tblHumanResultPhishing` (
  `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `HostNameOnly` tinyint(3) unsigned DEFAULT '0',
  `DateAdd` decimal(12,0) NOT NULL,
  PRIMARY KEY (`EventId`)
) ENGINE=MEMORY DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblPhishingMinerEventQueue`
--

CREATE TABLE IF NOT EXISTS `tblPhishingMinerEventQueue` (
  `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `EventData` text NOT NULL,
  `EventType` smallint(6) NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblPhishingMinerKeywords`
--

CREATE TABLE IF NOT EXISTS `tblPhishingMinerKeywords` (
  `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Keyword` varchar(255) NOT NULL,
  `KeywordWeight` smallint(5) unsigned NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotInitConfig`
--

CREATE TABLE IF NOT EXISTS `tblRobotInitConfig` (
  `Id` bigint(20) unsigned NOT NULL,
  `Key` text NOT NULL,
  `Value` text NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotKeywords`
--

CREATE TABLE IF NOT EXISTS `tblRobotKeywords` (
  `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Keyword` varchar(255) NOT NULL,
  `KeywordWeight` smallint(5) unsigned NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotProcessQueue`
--

CREATE TABLE IF NOT EXISTS `tblRobotProcessQueue` (
  `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `DateAdd` decimal(12,0) NOT NULL,
  PRIMARY KEY (`EventId`)
) ENGINE=MEMORY  DEFAULT CHARSET=latin1 AUTO_INCREMENT=189564821 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotResultNonPhishing`
--

CREATE TABLE IF NOT EXISTS `tblRobotResultNonPhishing` (
  `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `HostNameOnly` tinyint(3) unsigned DEFAULT '0',
  `DateAdd` decimal(12,0) NOT NULL,
  PRIMARY KEY (`EventId`)
) ENGINE=MEMORY DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotResultPhishing_humanQueue`
--

CREATE TABLE IF NOT EXISTS `tblRobotResultPhishing_humanQueue` (
  `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `DateAdd` decimal(12,0) NOT NULL,
  PRIMARY KEY (`EventId`)
) ENGINE=MEMORY DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `tblURIWhitelist`
--

CREATE TABLE IF NOT EXISTS `tblURIWhitelist` (
  `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `HostNameOnly` tinyint(3) unsigned DEFAULT '0',
  `DateAdd` decimal(12,0) unsigned NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
