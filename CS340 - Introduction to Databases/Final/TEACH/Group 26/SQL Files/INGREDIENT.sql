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
-- Table structure for table `INGREDIENT`
--

CREATE TABLE `INGREDIENT` (
  `INGREDIENT_ID` int(9) NOT NULL,
  `INGREDIENT_COST` double NOT NULL,
  `INGREDIENT_NAME` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `INGREDIENT`
--

INSERT INTO `INGREDIENT` (`INGREDIENT_ID`, `INGREDIENT_COST`, `INGREDIENT_NAME`) VALUES
(1, 5, 'Water'),
(2, 0.3, 'Tomato Paste'),
(3, 0.5, 'Mozzarella Cheese'),
(4, 0.25, 'Yeast'),
(5, 0.7, 'Vegetable Oil '),
(6, 0.2, 'Sugar'),
(7, 0.2, 'Flour'),
(8, 0.3, 'Pepperoni'),
(9, 0.2, 'Spaghetti Noodles'),
(10, 0.4, 'Meatballs'),
(11, 0.8, 'Hamburger Patty'),
(12, 0.4, 'Cheddar Cheese'),
(13, 0.3, 'Hamburger Bun'),
(14, 0.2, 'Rice'),
(15, 0.5, 'Pot Sticker'),
(16, 0.1, 'Salt'),
(17, 0.3, 'Carrots'),
(18, 0.6, 'Eggs'),
(19, 0.1, 'Peas'),
(20, 0.1, 'Onion'),
(21, 22, 'Soy Sauce'),
(22, 1, 'Red Wine'),
(23, 0, 'Nothing'),
(24, 0.2, 'ClassDemoRec'),
(25, 50, 'people');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `INGREDIENT`
--
ALTER TABLE `INGREDIENT`
  ADD PRIMARY KEY (`INGREDIENT_ID`),
  ADD UNIQUE KEY `INGREDIENT_NAME` (`INGREDIENT_NAME`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `INGREDIENT`
--
ALTER TABLE `INGREDIENT`
  MODIFY `INGREDIENT_ID` int(9) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
