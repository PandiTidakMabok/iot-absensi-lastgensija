-- phpMyAdmin SQL Dump
-- version 5.2.2-1.fc41
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Mar 25, 2025 at 06:43 PM
-- Server version: 10.11.10-MariaDB
-- PHP Version: 8.3.19

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

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`phpmyadmin`@`localhost` PROCEDURE `CariSiswa` (IN `p_uid` VARCHAR(255))   SELECT * FROM users WHERE uid=p_uid$$

CREATE DEFINER=`phpmyadmin`@`localhost` PROCEDURE `UpdateUser` (IN `p_uid` VARCHAR(255), IN `p_username` VARCHAR(255), IN `p_kelas` INT, IN `p_jurusan` VARCHAR(255), IN `p_email` VARCHAR(255), IN `p_password` VARCHAR(255))   UPDATE users SET username=p_username, kelas=p_kelas, jurusan=p_jurusan, email=p_email , password=p_password, role_id=3 WHERE uid=p_uid$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `absensi_hadirs`
--

CREATE TABLE `absensi_hadirs` (
  `uid` varchar(255) NOT NULL,
  `hari_tanggal` date NOT NULL,
  `username` varchar(255) NOT NULL,
  `role_id` bigint(20) UNSIGNED NOT NULL,
  `kelas` bigint(20) NOT NULL,
  `jurusan` varchar(255) NOT NULL,
  `status` tinyint(1) NOT NULL DEFAULT 0,
  `waktu_datang` time NOT NULL,
  `waktu_pulang` time DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `absensi_hadirs`
--

INSERT INTO `absensi_hadirs` (`uid`, `hari_tanggal`, `username`, `role_id`, `kelas`, `jurusan`, `status`, `waktu_datang`, `waktu_pulang`, `created_at`, `updated_at`) VALUES
('91ac3a3', '2025-03-25', 'a', 3, 1, 'a', 0, '10:36:48', NULL, '2025-03-25 03:36:48', '2025-03-25 03:36:48'),
('U003', '2025-03-25', 'siswa1', 3, 11, 'Teknik Elektro', 0, '07:00:00', '15:00:00', '2025-03-24 20:12:08', '2025-03-24 20:12:08'),
('U004', '2025-03-25', 'siswa2', 3, 11, 'Teknik Mesin', 0, '07:00:00', '15:00:00', '2025-03-24 20:12:08', '2025-03-24 20:12:08'),
('U005', '2025-03-25', 'siswa3', 3, 12, 'Teknik Sipil', 0, '07:00:00', '15:00:00', '2025-03-24 20:12:08', '2025-03-24 20:12:08'),
('U006', '2025-03-25', 'siswa4', 3, 10, 'Teknik Listrik', 0, '10:13:12', NULL, '2025-03-25 03:13:12', '2025-03-25 03:13:12');

-- --------------------------------------------------------

--
-- Table structure for table `absensi_tidak_hadirs`
--

CREATE TABLE `absensi_tidak_hadirs` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `username` varchar(255) NOT NULL,
  `role_id` bigint(20) UNSIGNED NOT NULL,
  `kelas` varchar(255) NOT NULL,
  `jurusan` text NOT NULL,
  `hari_tanggal` date NOT NULL,
  `alasan` varchar(255) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `absensi_tidak_hadirs`
--

INSERT INTO `absensi_tidak_hadirs` (`id`, `username`, `role_id`, `kelas`, `jurusan`, `hari_tanggal`, `alasan`, `created_at`, `updated_at`) VALUES
(1, 'siswa4', 3, '10', 'Teknik Listrik', '2025-03-25', 'izin', '2025-03-24 20:12:08', '2025-03-24 20:12:08'),
(2, 'siswa3', 3, '12', 'Teknik Sipil', '2025-03-25', 'sakit', '2025-03-24 20:12:08', '2025-03-24 20:12:08');

-- --------------------------------------------------------

--
-- Table structure for table `cache`
--

CREATE TABLE `cache` (
  `key` varchar(255) NOT NULL,
  `value` mediumtext NOT NULL,
  `expiration` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `cache_locks`
--

CREATE TABLE `cache_locks` (
  `key` varchar(255) NOT NULL,
  `owner` varchar(255) NOT NULL,
  `expiration` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `failed_jobs`
--

CREATE TABLE `failed_jobs` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `uuid` varchar(255) NOT NULL,
  `connection` text NOT NULL,
  `queue` text NOT NULL,
  `payload` longtext NOT NULL,
  `exception` longtext NOT NULL,
  `failed_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `jadwal`
--

CREATE TABLE `jadwal` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `hari` varchar(255) NOT NULL,
  `tanggal` date NOT NULL,
  `tugas` varchar(255) DEFAULT NULL,
  `praktek` varchar(255) DEFAULT NULL,
  `kegiatan` varchar(255) DEFAULT NULL,
  `deadline_hari` varchar(255) DEFAULT NULL,
  `deadline_tanggal` varchar(255) DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `jobs`
--

CREATE TABLE `jobs` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `queue` varchar(255) NOT NULL,
  `payload` longtext NOT NULL,
  `attempts` tinyint(3) UNSIGNED NOT NULL,
  `reserved_at` int(10) UNSIGNED DEFAULT NULL,
  `available_at` int(10) UNSIGNED NOT NULL,
  `created_at` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `job_batches`
--

CREATE TABLE `job_batches` (
  `id` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `total_jobs` int(11) NOT NULL,
  `pending_jobs` int(11) NOT NULL,
  `failed_jobs` int(11) NOT NULL,
  `failed_job_ids` longtext NOT NULL,
  `options` mediumtext DEFAULT NULL,
  `cancelled_at` int(11) DEFAULT NULL,
  `created_at` int(11) NOT NULL,
  `finished_at` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `kegiatan`
--

CREATE TABLE `kegiatan` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `hari` enum('Senin','Selasa','Rabu','Kamis','Jumat','Sabtu','Minggu') NOT NULL,
  `tanggal` date NOT NULL,
  `kegiatan` varchar(255) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `log`
--

CREATE TABLE `log` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `uid` varchar(255) NOT NULL,
  `username` varchar(255) DEFAULT NULL,
  `waktu_absen` time DEFAULT NULL,
  `pesan` text NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `log`
--

INSERT INTO `log` (`id`, `uid`, `username`, `waktu_absen`, `pesan`, `created_at`, `updated_at`) VALUES
(2, 'U006', 'siswa4', '10:13:12', 'terlambat', '2025-03-25 03:13:12', '2025-03-25 03:13:12'),
(3, 'edfwfwf', NULL, NULL, 'user tidak terdaftar', '2025-03-25 03:13:22', '2025-03-25 03:13:22'),
(6, '91ac3a3', 'a', '10:36:48', 'terlambat', '2025-03-25 03:36:48', '2025-03-25 03:36:48'),
(7, '829ece4', NULL, NULL, 'user tidak terdaftar', '2025-03-25 03:51:09', '2025-03-25 03:51:09'),
(8, '872e484', NULL, NULL, 'user tidak terdaftar', '2025-03-25 03:52:01', '2025-03-25 03:52:01');

-- --------------------------------------------------------

--
-- Table structure for table `migrations`
--

CREATE TABLE `migrations` (
  `id` int(10) UNSIGNED NOT NULL,
  `migration` varchar(255) NOT NULL,
  `batch` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `migrations`
--

INSERT INTO `migrations` (`id`, `migration`, `batch`) VALUES
(1, '0001_01_01_000000_create_users_table', 1),
(2, '0001_01_01_000001_create_cache_table', 1),
(3, '0001_01_01_000002_create_jobs_table', 1),
(4, '2025_02_08_143034_create_absensi_hadirs_table', 1),
(5, '2025_02_08_143045_create_absensi_tidak_hadirs_table', 1),
(6, '2025_02_10_235544_create_roles_table', 1),
(7, '2025_02_28_131704_create_personal_access_tokens_table', 1),
(8, '2025_03_02_092533_create_waktus_table', 1),
(9, '2025_03_07_121535_create_jadwal_table', 1),
(10, '2025_03_14_033349_create_log_table', 1),
(11, '2025_03_22_122945_create_tugas_table', 1),
(12, '2025_03_22_124826_create_praktek_table', 1),
(13, '2025_03_22_125605_create_kegiatan_table', 1);

-- --------------------------------------------------------

--
-- Table structure for table `password_reset_tokens`
--

CREATE TABLE `password_reset_tokens` (
  `email` varchar(255) NOT NULL,
  `token` varchar(255) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `personal_access_tokens`
--

CREATE TABLE `personal_access_tokens` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `tokenable_type` varchar(255) NOT NULL,
  `tokenable_id` bigint(20) UNSIGNED NOT NULL,
  `name` varchar(255) NOT NULL,
  `token` varchar(64) NOT NULL,
  `abilities` text DEFAULT NULL,
  `last_used_at` timestamp NULL DEFAULT NULL,
  `expires_at` timestamp NULL DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `praktek`
--

CREATE TABLE `praktek` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `hari` enum('Senin','Selasa','Rabu','Kamis','Jumat','Sabtu','Minggu') NOT NULL,
  `tanggal` date NOT NULL,
  `praktek` varchar(255) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `roles`
--

CREATE TABLE `roles` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `name` varchar(255) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `roles`
--

INSERT INTO `roles` (`id`, `name`, `created_at`, `updated_at`) VALUES
(1, 'admin', '2025-03-24 20:12:06', '2025-03-24 20:12:06'),
(2, 'guru', '2025-03-24 20:12:06', '2025-03-24 20:12:06'),
(3, 'siswa', '2025-03-24 20:12:06', '2025-03-24 20:12:06');

-- --------------------------------------------------------

--
-- Table structure for table `sessions`
--

CREATE TABLE `sessions` (
  `id` varchar(255) NOT NULL,
  `user_id` bigint(20) UNSIGNED DEFAULT NULL,
  `ip_address` varchar(45) DEFAULT NULL,
  `user_agent` text DEFAULT NULL,
  `payload` longtext NOT NULL,
  `last_activity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `tugas`
--

CREATE TABLE `tugas` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `hari` enum('Senin','Selasa','Rabu','Kamis','Jumat','Sabtu','Minggu') NOT NULL,
  `tanggal` date NOT NULL,
  `tugas` varchar(255) NOT NULL,
  `deadline_hari` enum('Senin','Selasa','Rabu','Kamis','Jumat','Sabtu','Minggu') NOT NULL,
  `deadline_tanggal` date NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `uid` varchar(255) NOT NULL,
  `username` varchar(255) NOT NULL,
  `image` text DEFAULT NULL,
  `jurusan` varchar(255) NOT NULL,
  `kelas` bigint(20) NOT NULL,
  `role_id` bigint(20) UNSIGNED NOT NULL,
  `email` varchar(255) DEFAULT NULL,
  `email_verified_at` timestamp NULL DEFAULT NULL,
  `password` varchar(255) NOT NULL,
  `remember_token` varchar(100) DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `uid`, `username`, `image`, `jurusan`, `kelas`, `role_id`, `email`, `email_verified_at`, `password`, `remember_token`, `created_at`, `updated_at`) VALUES
(1, 'U001', 'admin', NULL, 'Teknik Informatika', 12, 1, 'admin@gmail.com', NULL, '$2y$12$yYErAXI7L4MJ3U6FVbyvru3qIbEfXElerRZ6vRD3NRm5dR1hYUhsi', NULL, '2025-03-24 20:12:07', '2025-03-24 20:12:07'),
(2, 'U002', 'guru1', NULL, 'Matematika', 0, 2, 'guru@gmail.com', NULL, '$2y$12$g0s4xqRNOIo9BQe0Y9QSR.c56BKupXfVrMjSqYjpMLu7MFDRUjD6W', NULL, '2025-03-24 20:12:07', '2025-03-24 20:12:07'),
(3, 'U003', 'siswa1', NULL, 'Teknik Elektro', 11, 3, 'siswa@gmail.com', NULL, '$2y$12$8/nYi6PuXoJ2.ZXlIz5gFuABmGrA1Vc6eG9s76GUfLb9okqMcDia2', NULL, '2025-03-24 20:12:07', '2025-03-24 20:12:07'),
(4, 'U004', 'siswa2', NULL, 'Teknik Mesin', 11, 3, 'siswa2@gmail.com', NULL, '$2y$12$Jm1mUrgpG60RCAvpzdC9BeK.JDHB4En9KFWPcPEfq8jBZMf0XO..u', NULL, '2025-03-24 20:12:07', '2025-03-24 20:12:07'),
(5, 'U005', 'siswa3', NULL, 'Teknik Sipil', 12, 3, 'siswa3@gmail.com', NULL, '$2y$12$hHY0vFf9Qg1m2L57c/bLFOQS.2/hJ17H4.49odmwtd3dkgkOn7rS2', NULL, '2025-03-24 20:12:07', '2025-03-24 20:12:07'),
(6, 'U006', 'siswa4', NULL, 'Teknik Listrik', 10, 3, 'siswa4@gmail.com', NULL, '$2y$12$zzJ2s7E3BlxY1QER2sNk6ONyQ.8s8asnc1KWb566wcfDyLpF5W5DC', NULL, '2025-03-24 20:12:08', '2025-03-24 20:12:08'),
(7, '91ac3a3', 'a', NULL, 'a', 1, 3, 'null', NULL, '$2y$12$BXk2KysY9f1UnYUNUKVdNOSqt/XYzIkKb2xbaaxwMuZWT/gfySwdi', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `waktus`
--

CREATE TABLE `waktus` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `hari` enum('Senin','Selasa','Rabu','Kamis','Jumat','Sabtu','Minggu') NOT NULL,
  `jam_masuk` time NOT NULL,
  `jam_pulang` time NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `absensi_hadirs`
--
ALTER TABLE `absensi_hadirs`
  ADD UNIQUE KEY `absensi_hadirs_uid_unique` (`uid`);

--
-- Indexes for table `absensi_tidak_hadirs`
--
ALTER TABLE `absensi_tidak_hadirs`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `cache`
--
ALTER TABLE `cache`
  ADD PRIMARY KEY (`key`);

--
-- Indexes for table `cache_locks`
--
ALTER TABLE `cache_locks`
  ADD PRIMARY KEY (`key`);

--
-- Indexes for table `failed_jobs`
--
ALTER TABLE `failed_jobs`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `failed_jobs_uuid_unique` (`uuid`);

--
-- Indexes for table `jadwal`
--
ALTER TABLE `jadwal`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `jobs`
--
ALTER TABLE `jobs`
  ADD PRIMARY KEY (`id`),
  ADD KEY `jobs_queue_index` (`queue`);

--
-- Indexes for table `job_batches`
--
ALTER TABLE `job_batches`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `kegiatan`
--
ALTER TABLE `kegiatan`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `log`
--
ALTER TABLE `log`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `migrations`
--
ALTER TABLE `migrations`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `password_reset_tokens`
--
ALTER TABLE `password_reset_tokens`
  ADD PRIMARY KEY (`email`);

--
-- Indexes for table `personal_access_tokens`
--
ALTER TABLE `personal_access_tokens`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `personal_access_tokens_token_unique` (`token`),
  ADD KEY `personal_access_tokens_tokenable_type_tokenable_id_index` (`tokenable_type`,`tokenable_id`);

--
-- Indexes for table `praktek`
--
ALTER TABLE `praktek`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `roles`
--
ALTER TABLE `roles`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sessions`
--
ALTER TABLE `sessions`
  ADD PRIMARY KEY (`id`),
  ADD KEY `sessions_user_id_index` (`user_id`),
  ADD KEY `sessions_last_activity_index` (`last_activity`);

--
-- Indexes for table `tugas`
--
ALTER TABLE `tugas`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `users_uid_unique` (`uid`),
  ADD UNIQUE KEY `users_email_unique` (`email`);

--
-- Indexes for table `waktus`
--
ALTER TABLE `waktus`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `absensi_tidak_hadirs`
--
ALTER TABLE `absensi_tidak_hadirs`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `failed_jobs`
--
ALTER TABLE `failed_jobs`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `jadwal`
--
ALTER TABLE `jadwal`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `jobs`
--
ALTER TABLE `jobs`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `kegiatan`
--
ALTER TABLE `kegiatan`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log`
--
ALTER TABLE `log`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `migrations`
--
ALTER TABLE `migrations`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `personal_access_tokens`
--
ALTER TABLE `personal_access_tokens`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `praktek`
--
ALTER TABLE `praktek`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `roles`
--
ALTER TABLE `roles`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `tugas`
--
ALTER TABLE `tugas`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `waktus`
--
ALTER TABLE `waktus`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
