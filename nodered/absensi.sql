-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Jan 29, 2025 at 05:53 AM
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
  `uid` char(100) NOT NULL,
  `student_name` char(255) DEFAULT NULL,
  `status` varchar(50) NOT NULL,
  `date` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `log_absensi`
--

INSERT INTO `log_absensi` (`uid`, `student_name`, `status`, `date`) VALUES
('undefined', 'qw', '5', '2025-01-29 11:43:06'),
('undefined', 'qw', '5', '2025-01-29 11:43:09'),
('undefined', 'qw', '5', '2025-01-29 11:43:11'),
('undefined', 'qw', '5', '2025-01-29 11:44:43'),
('sdfgyu', 'qw', '5', '2025-01-29 11:46:07'),
('dfubhjiasbhuid', NULL, 'user tidak terdaftar', '2025-01-29 11:46:20');

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
('43857987', 'a', 1, 'a'),
('c43t8bb834cvt57', 'sadas', 4, 'dfgdfg'),
('dfubhjiasbhuid', 'qwewq', 123, 'eqwqe'),
('sdfgyu', 'qw', 5, 'qe');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `log_absensi`
--
ALTER TABLE `log_absensi`
  ADD KEY `uid` (`uid`),
  ADD KEY `date` (`date`);

--
-- Indexes for table `siswa`
--
ALTER TABLE `siswa`
  ADD UNIQUE KEY `uid` (`uid`),
  ADD KEY `uid_2` (`uid`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
