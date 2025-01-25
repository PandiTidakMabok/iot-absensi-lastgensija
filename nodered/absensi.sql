-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Jan 25, 2025 at 05:30 AM
-- Server version: 10.4.32-MariaDB-log
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `absensi`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_absensi`
--

CREATE TABLE `log_absensi` (
  `uid` int(11) NOT NULL,
  `student_name` char(255) DEFAULT NULL,
  `status` varchar(50) NOT NULL,
  `date` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `log_absensi`
--

INSERT INTO `log_absensi` (`uid`, `student_name`, `status`, `date`) VALUES
(123123123, NULL, 'user tidak terdaftar', '2025-01-25 10:35:16'),
(123123123, NULL, 'user tidak terdaftar', '2025-01-25 11:09:29'),
(123123123, NULL, 'user tidak terdaftar', '2025-01-25 11:14:39'),
(123123123, NULL, 'user tidak terdaftar', '2025-01-25 11:14:46'),
(123123123, NULL, 'user tidak terdaftar', '2025-01-25 11:20:20'),
(123123123, NULL, 'user tidak terdaftar', '2025-01-25 11:20:31');

-- --------------------------------------------------------

--
-- Table structure for table `siswa`
--

CREATE TABLE `siswa` (
  `uid` varchar(255) NOT NULL,
  `student_name` char(255) NOT NULL,
  `class` int(11) NOT NULL,
  `major` char(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `siswa`
--

INSERT INTO `siswa` (`uid`, `student_name`, `class`, `major`) VALUES
('43857987', 'a', 1, 'a');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `siswa`
--
ALTER TABLE `siswa`
  ADD UNIQUE KEY `uid` (`uid`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
