DROP TABLE IF EXISTS r_alert_picture CASCADE;
DROP TABLE IF EXISTS pictures CASCADE;
DROP TABLE IF EXISTS url CASCADE;
DROP TABLE IF EXISTS pest CASCADE;
DROP TABLE IF EXISTS crop CASCADE;
DROP TABLE IF EXISTS disease CASCADE;
DROP TABLE IF EXISTS harvest CASCADE;



-- table pest
CREATE TABLE pest (
	id_pest serial PRIMARY KEY,
	lbl_pest text NOT NULL,
	id_pic integer NOT NULL,
	url text NOT NULL,
	comment text
)
WITH (
  OIDS=FALSE
);
ALTER TABLE pest OWNER TO postgres;


-- table crop
CREATE TABLE crop (
	id_crop serial NOT NULL PRIMARY KEY,
	lbl_crop text NOT NULL,
	id_pic integer NOT NULL,
	url text NOT NULL,
	comment text
)
WITH (
  OIDS=FALSE
);
ALTER TABLE crop OWNER TO postgres;

-- table disease
CREATE TABLE disease (
	id_disease serial NOT NULL PRIMARY KEY,
	lbl_disease text NOT NULL,
	id_pic integer NOT NULL,
	url text NOT NULL,
	comment text
)
WITH (
  OIDS=FALSE
);
ALTER TABLE disease OWNER TO postgres;

-- table picture
CREATE TABLE pictures (
	id_pic serial NOT NULL PRIMARY KEY,
	pic bytea NOT NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE pictures OWNER TO postgres;


-- table harvest
CREATE TABLE harvest (
	id_harvest serial NOT NULL PRIMARY KEY,
	datetime TIMESTAMP NOT NULL,
	prct_destroyed REAL NOT NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE harvest OWNER TO postgres;


-- table alert
DROP TABLE IF EXISTS alert;
CREATE TABLE alert (
	id_alert serial NOT NULL PRIMARY KEY,
	id_crop integer NOT NULL REFERENCES crop (id_crop),
	id_pest integer REFERENCES pest (id_pest),
	id_disease integer REFERENCES disease (id_disease),
	id_harvest integer REFERENCES harvest (id_harvest),
	location text,
	latlong text,
	datetime_cur TIMESTAMP NOT NULL,
	datetime_start TIMESTAMP NOT NULL,
	prct_area REAL NOT NULL,
	comment TEXT
)
WITH (
  OIDS=FALSE
);
ALTER TABLE alert OWNER TO postgres;


-- r_alert_picture
CREATE TABLE r_alert_picture (
	id_alert integer NOT NULL REFERENCES alert (id_alert),
	id_picture integer NOT NULL REFERENCES pictures (id_pic),
	PRIMARY KEY (id_alert, id_picture)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE r_alert_picture OWNER TO postgres;


-- url
CREATE TABLE url (
	id_url serial NOT NULL PRIMARY KEY,
	url text
)
WITH (
  OIDS=FALSE
);
ALTER TABLE url OWNER TO postgres;




