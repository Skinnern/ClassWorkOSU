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
-- Table structure for table `STEP`
--

CREATE TABLE `STEP` (
  `STEP_ID` int(9) NOT NULL,
  `STEP_DESC` varchar(300) NOT NULL,
  `INGREDIENT_ID` int(9) DEFAULT NULL,
  `INGREDIENT_AMOUNT` double DEFAULT NULL,
  `RECIPE_ID` int(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `STEP`
--

INSERT INTO `STEP` (`STEP_ID`, `STEP_DESC`, `INGREDIENT_ID`, `INGREDIENT_AMOUNT`, `RECIPE_ID`) VALUES
(1, 'Pour water into a glass', 1, 8, 1),
(22, 'Place on 450 degree grill for 15 min, flip every 5 min', 11, 4, 13),
(24, 'After finishing last step, flip burger over, and then place cheddar on top of the patty, cook for 5 more min, but lower the heat to 350 degrees', 12, 1, 13),
(25, 'Place Hamburger buns adjacent to the patty to let them heat up and toast a bit ', 13, 4, 13),
(26, 'Turn off all heat, and place the patty with the cheese cooked on between the slices of bread, and Voila! a tidy burger!', 16, 1, 13),
(49, 'place a pot filled with water on high heat, leave until the water starts to bubble/boil', 1, 128, 11),
(50, 'after the water has started to boil, break apart, and then place the noodles in the boiling water for appx 10 min.', 9, 12, 11),
(51, 'place tomato paste/sauce in a heated pan on high heat, then begin mixing to keep it from burning', 2, 6, 11),
(52, 'Add some spices, and then mix in the meatballs, continue mixing and cooking for about 20 min, or until the meat seems done.', 10, 8, 11),
(53, 'place the pasta in a strainer, and let it dry out a bit, then place in a bowl, place the tomato sauce and meatballs on top, mix and enjoy! (I also like to add some salt)', 16, 1, 11),
(54, 'Either use leftovers, or make some fresh rice for this recipe. fully cooked you should have about 5 and a half cups of rice', 14, 12, 12),
(55, 'throw the rice into a frying pan, add some oil to prevent it from sticking', 5, 3, 12),
(56, 'add some soy sauce, and monitor/mix the rice to prevent it from burning', 21, 3, 12),
(57, 'add your first vegetable, i prefer to put onions first so they grill more thoroughly than the others', 20, 2, 12),
(58, 'add in the second ingredient, I like to do chopped carrots next to get a nice variety of flavors, be sure to keep mixing, and add any additional soysauce or veggies that you may want', 17, 2, 12),
(59, 'finally adding my last vegetable, peas, i add them last so they retain a good flavor, while also not getting overcooked ', 19, 1, 12),
(60, 'Often as a side to this meal, I will fry some pot stickers that will go nicely into it, you can throw them into the mix at anytime depending on how crunchy you want the recipe to be. as soon as you are done grilling them to your liking, the rest of the recipe should be ready to go! ', 15, 6, 12),
(61, 'throw some flour into the bowl, and begin mixing it around, make sure there are no clumps, and then proceed', 7, 10, 10),
(62, 'add warm water into the mix, and keep stirring ', 1, 12, 10),
(63, 'add a little bit of vegitable oil to prevent it from burning to the pan or anything else.', 5, 1, 10),
(64, 'add some yeast, i\'d actually reccomend adding .5 of an ounce, but 1 will do very well, just be careful of rising crust!', 4, 1, 10),
(65, 'finally, add some salt. mix everything together so that it has no lumps, and then let rise for an hour or so.', 16, 2, 10),
(66, 'spread the dough out on the table into whatever shape your heart desires, and start adding some tomato sauce on top of the dough', 2, 4, 10),
(67, 'place some of that fine cheese on top of your creation, you can add as much, or as little as you want, but I prefer to cover that sweet pie until it resembles a cheese wheel.', 3, 8, 10),
(68, 'place some pepperoni on that pizza pie, you may be asking how much? i just place a recommended amount, but you can have as much as you want. some people also like to add a cheese layer on top of this, but i will refrain', 8, 4, 10),
(69, 'place that dude in the oven for about 20 to 25 min on 400 degrees, if it does not look cooked at that point, you may want a new oven, or to place it in at 400 degrees for additional 5 min intervals until done. and there you have it!', 23, 1, 10),
(70, 'do a presentation', 24, 1, 36),
(71, 'test2', 24, 5, 36),
(72, 'add people', 25, 20, 37);

--
-- Triggers `STEP`
--
DELIMITER $$
CREATE TRIGGER `UpdateRecipe` AFTER INSERT ON `STEP` FOR EACH ROW update 
RECIPE T
inner join 
(select R.Recipe_id, SUM(I.INGREDIENT_COST * S.INGREDIENT_AMOUNT) as Cost from RECIPE R, INGREDIENT I, STEP S where S.RECIPE_ID = R.RECIPE_ID and I.INGREDIENT_ID = S.INGREDIENT_ID group by R.RECIPE_ID) k
set T.RECIPE_COST = k.Cost
where T.RECIPE_ID = k.RECIPE_ID
$$
DELIMITER ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `STEP`
--
ALTER TABLE `STEP`
  ADD PRIMARY KEY (`STEP_ID`),
  ADD KEY `STEP_INGREDIENT_FK` (`INGREDIENT_ID`),
  ADD KEY `STEP_RECIPE_FK` (`RECIPE_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `STEP`
--
ALTER TABLE `STEP`
  MODIFY `STEP_ID` int(9) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=73;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `STEP`
--
ALTER TABLE `STEP`
  ADD CONSTRAINT `STEP_INGREDIENT_FK` FOREIGN KEY (`INGREDIENT_ID`) REFERENCES `INGREDIENT` (`INGREDIENT_ID`),
  ADD CONSTRAINT `STEP_RECIPE_FK` FOREIGN KEY (`RECIPE_ID`) REFERENCES `RECIPE` (`RECIPE_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
