-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: classmysql.engr.oregonstate.edu:3306
-- Generation Time: Dec 05, 2017 at 03:53 PM
-- Server version: 10.1.22-MariaDB
-- PHP Version: 7.0.23

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cs340_skinnern`
--

-- --------------------------------------------------------

--
-- Table structure for table `RECIPE`
--

CREATE TABLE `RECIPE` (
  `RECIPE_ID` int(9) NOT NULL,
  `RECIPE_NAME` varchar(50) NOT NULL,
  `RECIPE_COST` decimal(10,2) NOT NULL,
  `USER_ID` int(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `RECIPE`
--

INSERT INTO `RECIPE` (`RECIPE_ID`, `RECIPE_NAME`, `RECIPE_COST`, `USER_ID`) VALUES
(1, 'A Tall Glass of Water', '40.00', 2),
(10, 'Papa Murphys Home Pizza Recipe', '69.55', 4),
(11, 'Jeanetti Spaghetti', '647.50', 3),
(12, 'Casual Fried Rice', '74.40', 6),
(13, 'IMakeFoods Burger', '4.90', 5),
(36, 'classdemo', '1.20', 3),
(37, 'classdemo2', '240.00', 2);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `RECIPE`
--
ALTER TABLE `RECIPE`
  ADD PRIMARY KEY (`RECIPE_ID`),
  ADD KEY `RECIPE_USER_FK` (`USER_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `RECIPE`
--
ALTER TABLE `RECIPE`
  MODIFY `RECIPE_ID` int(9) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=38;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `RECIPE`
--
ALTER TABLE `RECIPE`
  ADD CONSTRAINT `RECIPE_USER_FK` FOREIGN KEY (`USER_ID`) REFERENCES `USER` (`USER_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
