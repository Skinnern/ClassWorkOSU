-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: classmysql.engr.oregonstate.edu:3306
-- Generation Time: Dec 05, 2017 at 03:52 PM
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
-- Table structure for table `COMMENT`
--

CREATE TABLE `COMMENT` (
  `USER_ID` int(9) NOT NULL,
  `RECIPE_ID` int(9) NOT NULL,
  `COMMENT_ID` int(9) NOT NULL,
  `COMMENT` varchar(300) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `COMMENT`
--

INSERT INTO `COMMENT` (`USER_ID`, `RECIPE_ID`, `COMMENT_ID`, `COMMENT`) VALUES
(2, 1, 2, 'this is my favorite recipe, did you know this \'water stuff is used in all kinds of recipes? crazy!'),
(6, 10, 4, 'This Recipe is fantastic! Papa Murphy has done it again!'),
(3, 12, 5, 'Can I substitute the Onion with Green or red Onion?'),
(5, 11, 6, 'Add some jalapenos to the tomato paste for a nice kick of spice!'),
(2, 13, 7, 'Delicious recipe! super simple! what more can a college kid ask for?'),
(4, 1, 8, 'This is a great recipe to go with anything! water washes down food really well!'),
(3, 11, 18, 'Sounds like a great idea IMakeFood!'),
(3, 36, 19, 'wow, so great!'),
(2, 1, 20, 'hi class');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `COMMENT`
--
ALTER TABLE `COMMENT`
  ADD PRIMARY KEY (`COMMENT_ID`),
  ADD KEY `COMMENT_RECIPE_FK` (`RECIPE_ID`),
  ADD KEY `COMMENT_USER_FK` (`USER_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `COMMENT`
--
ALTER TABLE `COMMENT`
  MODIFY `COMMENT_ID` int(9) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `COMMENT`
--
ALTER TABLE `COMMENT`
  ADD CONSTRAINT `COMMENT_RECIPE_FK` FOREIGN KEY (`RECIPE_ID`) REFERENCES `RECIPE` (`RECIPE_ID`),
  ADD CONSTRAINT `COMMENT_USER_FK` FOREIGN KEY (`USER_ID`) REFERENCES `USER` (`USER_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
