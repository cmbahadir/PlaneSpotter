CREATE TABLE ADSBDATA (
    HEX varchar(255),
    SQUAWK varchar(255),
    FLIGHT varchar(255),
    ALTITUDE int,
    SPEED int,
    HEADING int,
    LAT varchar(255),
    LON varchar(255),
    TRACK int,
    MESSAGES int,
    SEEN int,
    Date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP 
);
