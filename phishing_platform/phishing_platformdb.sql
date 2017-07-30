-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 30, 2017 at 08:21 AM
-- Server version: 10.1.25-MariaDB
-- PHP Version: 5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `SAMPLE`
--

-- --------------------------------------------------------

--
-- Table structure for table `tblHumanResultNonPhishing`
--

CREATE TABLE IF NOT EXISTS `tblHumanResultNonPhishing` (
  `EventId` bigint(20) unsigned NOT NULL,
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
  `DateAdd` decimal(12,0) NOT NULL
) ENGINE=MEMORY DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblHumanResultPhishing`
--

CREATE TABLE IF NOT EXISTS `tblHumanResultPhishing` (
  `EventId` bigint(20) unsigned NOT NULL,
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
  `DateAdd` decimal(12,0) NOT NULL
) ENGINE=MEMORY DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblPhishingMinerEventQueue`
--

CREATE TABLE IF NOT EXISTS `tblPhishingMinerEventQueue` (
  `Id` bigint(20) unsigned NOT NULL,
  `EventData` text NOT NULL,
  `EventType` smallint(6) NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblPhishingMinerKeywords`
--

CREATE TABLE IF NOT EXISTS `tblPhishingMinerKeywords` (
  `Id` bigint(20) unsigned NOT NULL,
  `Keyword` varchar(255) NOT NULL,
  `KeywordWeight` smallint(5) unsigned NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotInitConfig`
--

CREATE TABLE IF NOT EXISTS `tblRobotInitConfig` (
  `Id` bigint(20) unsigned NOT NULL,
  `Key` text NOT NULL,
  `Value` text NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotKeywords`
--

CREATE TABLE IF NOT EXISTS `tblRobotKeywords` (
  `Id` bigint(20) unsigned NOT NULL,
  `Keyword` varchar(255) NOT NULL,
  `KeywordWeight` smallint(5) unsigned NOT NULL,
  `DateAdd` decimal(12,0) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotProcessFailur`
--

CREATE TABLE IF NOT EXISTS `tblRobotProcessFailur` (
  `EventId` bigint(20) unsigned NOT NULL,
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
  `DateAdd` decimal(12,0) NOT NULL
) ENGINE=MEMORY DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotProcessQueue`
--

CREATE TABLE IF NOT EXISTS `tblRobotProcessQueue` (
  `EventId` bigint(20) unsigned NOT NULL,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `DateAdd` decimal(12,0) NOT NULL
) ENGINE=MEMORY DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotResultNonPhishing`
--

CREATE TABLE IF NOT EXISTS `tblRobotResultNonPhishing` (
  `EventId` bigint(20) unsigned NOT NULL,
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
  `DateAdd` decimal(12,0) NOT NULL
) ENGINE=MEMORY DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblRobotResultPhishing_humanQueue`
--

CREATE TABLE IF NOT EXISTS `tblRobotResultPhishing_humanQueue` (
  `EventId` bigint(20) unsigned NOT NULL,
  `ProcessId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Protocol` smallint(1) unsigned NOT NULL,
  `SRC_IP` int(4) unsigned NOT NULL,
  `DST_IP` int(4) unsigned NOT NULL,
  `SRC_Port` int(2) unsigned NOT NULL,
  `DST_Port` int(2) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `Href` varchar(511) NOT NULL,
  `DateAdd` decimal(12,0) NOT NULL
) ENGINE=MEMORY DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tblURIWhitelist`
--

CREATE TABLE IF NOT EXISTS `tblURIWhitelist` (
  `Id` bigint(20) unsigned NOT NULL,
  `HostName` varchar(255) NOT NULL,
  `URL` varchar(511) NOT NULL,
  `HostNameOnly` tinyint(3) unsigned DEFAULT '0',
  `DateAdd` decimal(12,0) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `tblHumanResultNonPhishing`
--
ALTER TABLE `tblHumanResultNonPhishing`
  ADD PRIMARY KEY (`EventId`);

--
-- Indexes for table `tblHumanResultPhishing`
--
ALTER TABLE `tblHumanResultPhishing`
  ADD PRIMARY KEY (`EventId`);

--
-- Indexes for table `tblPhishingMinerEventQueue`
--
ALTER TABLE `tblPhishingMinerEventQueue`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `tblPhishingMinerKeywords`
--
ALTER TABLE `tblPhishingMinerKeywords`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `tblRobotInitConfig`
--
ALTER TABLE `tblRobotInitConfig`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `tblRobotKeywords`
--
ALTER TABLE `tblRobotKeywords`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `tblRobotProcessFailur`
--
ALTER TABLE `tblRobotProcessFailur`
  ADD PRIMARY KEY (`EventId`);

--
-- Indexes for table `tblRobotProcessQueue`
--
ALTER TABLE `tblRobotProcessQueue`
  ADD PRIMARY KEY (`EventId`);

--
-- Indexes for table `tblRobotResultNonPhishing`
--
ALTER TABLE `tblRobotResultNonPhishing`
  ADD PRIMARY KEY (`EventId`);

--
-- Indexes for table `tblRobotResultPhishing_humanQueue`
--
ALTER TABLE `tblRobotResultPhishing_humanQueue`
  ADD PRIMARY KEY (`EventId`);

--
-- Indexes for table `tblURIWhitelist`
--
ALTER TABLE `tblURIWhitelist`
  ADD PRIMARY KEY (`Id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `tblHumanResultNonPhishing`
--
ALTER TABLE `tblHumanResultNonPhishing`
  MODIFY `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblHumanResultPhishing`
--
ALTER TABLE `tblHumanResultPhishing`
  MODIFY `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblPhishingMinerEventQueue`
--
ALTER TABLE `tblPhishingMinerEventQueue`
  MODIFY `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblPhishingMinerKeywords`
--
ALTER TABLE `tblPhishingMinerKeywords`
  MODIFY `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblRobotKeywords`
--
ALTER TABLE `tblRobotKeywords`
  MODIFY `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblRobotProcessFailur`
--
ALTER TABLE `tblRobotProcessFailur`
  MODIFY `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblRobotProcessQueue`
--
ALTER TABLE `tblRobotProcessQueue`
  MODIFY `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblRobotResultNonPhishing`
--
ALTER TABLE `tblRobotResultNonPhishing`
  MODIFY `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblRobotResultPhishing_humanQueue`
--
ALTER TABLE `tblRobotResultPhishing_humanQueue`
  MODIFY `EventId` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tblURIWhitelist`
--
ALTER TABLE `tblURIWhitelist`
  MODIFY `Id` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
