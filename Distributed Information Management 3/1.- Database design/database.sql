SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci ;
USE `mydb`;

-- -----------------------------------------------------
-- Table `mydb`.`Course`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Course` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`Course` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NOT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Student`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Student` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`Student` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NOT NULL ,
  `surname` VARCHAR(45) NOT NULL ,
  `matriculationNumber` VARCHAR(10) NOT NULL ,
  `password` VARCHAR(70) NOT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`StudentCourse`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`StudentCourse` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`StudentCourse` (
  `Course_id` INT NOT NULL ,
  `Student_id` INT NOT NULL ,
  PRIMARY KEY (`Course_id`, `Student_id`) ,
  INDEX `fk_Course_has_Student_Course` (`Course_id` ASC) ,
  INDEX `fk_Course_has_Student_Student` (`Student_id` ASC) ,
  CONSTRAINT `fk_Course_has_Student_Course`
    FOREIGN KEY (`Course_id` )
    REFERENCES `mydb`.`Course` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Course_has_Student_Student`
    FOREIGN KEY (`Student_id` )
    REFERENCES `mydb`.`Student` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `mydb`.`Questionaire`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Questionaire` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`Questionaire` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NULL ,
  `Course_id` INT NOT NULL ,
  `Student_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_Questionaire_Course` (`Course_id` ASC) ,
  INDEX `fk_Questionaire_Student` (`Student_id` ASC) ,
  CONSTRAINT `fk_Questionaire_Course`
    FOREIGN KEY (`Course_id` )
    REFERENCES `mydb`.`Course` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Questionaire_Student`
    FOREIGN KEY (`Student_id` )
    REFERENCES `mydb`.`Student` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Question`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Question` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`Question` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `content` TEXT NOT NULL ,
  `Questionaire_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_Question_Questionaire` (`Questionaire_id` ASC) ,
  CONSTRAINT `fk_Question_Questionaire`
    FOREIGN KEY (`Questionaire_id` )
    REFERENCES `mydb`.`Questionaire` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Choice`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Choice` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`Choice` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `content` TEXT NOT NULL ,
  `Question_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_Choice_Question` (`Question_id` ASC) ,
  CONSTRAINT `fk_Choice_Question`
    FOREIGN KEY (`Question_id` )
    REFERENCES `mydb`.`Question` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Answer`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Answer` ;

CREATE  TABLE IF NOT EXISTS `mydb`.`Answer` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `Student_id` INT NOT NULL ,
  `Questionaire_id` INT NOT NULL ,
  `Question_id` INT NOT NULL ,
  `Choice_id` INT NOT NULL ,
  `Result` BOOLEAN NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_Answer_Student` (`Student_id` ASC) ,
  INDEX `fk_Answer_Questionaire` (`Questionaire_id` ASC) ,
  INDEX `fk_Answer_Question` (`Question_id` ASC) ,
  INDEX `fk_Answer_Choice` (`Choice_id` ASC) ,
  CONSTRAINT `fk_Answer_Student`
    FOREIGN KEY (`Student_id` )
    REFERENCES `mydb`.`Student` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Answer_Questionaire`
    FOREIGN KEY (`Questionaire_id` )
    REFERENCES `mydb`.`Questionaire` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Answer_Question`
    FOREIGN KEY (`Question_id` )
    REFERENCES `mydb`.`Question` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Answer_Choice`
    FOREIGN KEY (`Choice_id` )
    REFERENCES `mydb`.`Choice` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
