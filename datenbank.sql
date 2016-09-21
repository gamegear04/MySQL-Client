-- phpMyAdmin SQL Dump
-- version 4.5.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 21. Sep 2016 um 17:25
-- Server-Version: 10.1.13-MariaDB
-- PHP-Version: 5.6.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;


GRANT ALL PRIVILEGES ON *.* TO 'datauser'@'localhost' IDENTIFIED BY PASSWORD '*E5A63B28505A86B7FBAD473EF1D742A716B8FCF5' WITH GRANT OPTION;

GRANT ALL PRIVILEGES ON `databank`.* TO 'datauser'@'localhost';

--
-- Datenbank: `databank`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tab`
--

CREATE TABLE `tab` (
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `red` tinyint(1) NOT NULL,
  `yellow` tinyint(1) NOT NULL,
  `green` tinyint(1) NOT NULL,
  `status` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `tab`
--

INSERT INTO `tab` (`date`, `red`, `yellow`, `green`, `status`) VALUES
('2016-06-24 14:54:01', 1, 0, 0, 'PI -> Fehler ');

-- --------------------------------------------------------

