DROP TABLE IF EXISTS USER;
CREATE TABLE USER
(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    NAME VARCHAR(255) NOT NULL,
    AGE INT NOT NULL,
    CITY VARCHAR(255) NOT NULL
);