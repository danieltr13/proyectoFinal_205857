CREATE DATABASE  IF NOT EXISTS `casainteligente` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `casainteligente`;
-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: casainteligente
-- ------------------------------------------------------
-- Server version	8.0.22

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `alarmas`
--

DROP TABLE IF EXISTS `alarmas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `alarmas` (
  `idalarmas` int NOT NULL AUTO_INCREMENT,
  `fechahora` datetime DEFAULT NULL,
  PRIMARY KEY (`idalarmas`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `alarmas`
--

LOCK TABLES `alarmas` WRITE;
/*!40000 ALTER TABLE `alarmas` DISABLE KEYS */;
INSERT INTO `alarmas` VALUES (1,'2021-05-28 04:01:01'),(2,'2021-05-28 04:36:12'),(3,'2021-05-28 04:37:25'),(4,'2021-05-28 04:40:11'),(5,'2021-05-28 04:40:33'),(6,'2021-05-28 04:45:26'),(7,'2021-05-28 04:47:49'),(8,'2021-05-28 04:48:01'),(9,'2021-05-28 04:48:27'),(10,'2021-05-28 04:50:10'),(11,'2021-05-28 04:50:18'),(12,'2021-05-28 05:00:50'),(13,'2021-05-28 05:01:16');
/*!40000 ALTER TABLE `alarmas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cambiosangulos`
--

DROP TABLE IF EXISTS `cambiosangulos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cambiosangulos` (
  `idnew_table` int NOT NULL AUTO_INCREMENT,
  `cambio` datetime DEFAULT NULL,
  `angulo` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idnew_table`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cambiosangulos`
--

LOCK TABLES `cambiosangulos` WRITE;
/*!40000 ALTER TABLE `cambiosangulos` DISABLE KEYS */;
INSERT INTO `cambiosangulos` VALUES (1,'2021-05-28 04:01:01','90'),(2,'2021-05-28 04:08:57','45'),(3,'2021-05-28 04:31:28','45'),(4,'2021-05-28 04:31:32','135'),(5,'2021-05-28 04:31:45','45'),(6,'2021-05-28 04:31:49','135'),(7,'2021-05-28 04:35:30','45'),(8,'2021-05-28 04:35:42','90'),(9,'2021-05-28 04:35:45','135'),(10,'2021-05-28 04:35:48','180'),(11,'2021-05-28 04:35:52','45'),(12,'2021-05-28 04:40:42','135'),(13,'2021-05-28 04:40:46','90');
/*!40000 ALTER TABLE `cambiosangulos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `intencidad`
--

DROP TABLE IF EXISTS `intencidad`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `intencidad` (
  `idintencidad` int NOT NULL AUTO_INCREMENT,
  `promedio` float DEFAULT NULL,
  `horafecha` datetime(6) DEFAULT NULL,
  PRIMARY KEY (`idintencidad`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `intencidad`
--

LOCK TABLES `intencidad` WRITE;
/*!40000 ALTER TABLE `intencidad` DISABLE KEYS */;
INSERT INTO `intencidad` VALUES (1,2.5,'2021-05-28 04:01:01.000000');
/*!40000 ALTER TABLE `intencidad` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-28  5:05:27
