create database if not exists university;

use university;

create table if not exists classroom
	(building				varchar(15),
     room_number			varchar(7),
	 capacity				numeric(4,0),
     primary key (building, room_number)
	);
    
create table if not exists department
	(dept_name				varchar(20), 
     building				varchar(15), 
     budget					numeric(12,2) check(budget > 0),
     primary key (dept_name)
	);
    
create table if not exists course
	(course_id				varchar(8),
     title					varchar(50),
     dept_name				varchar(20),
     credits				numeric(2,0) check(credits > 0),
	 primary key (course_id),
     foreign key (dept_name) references department (dept_name) on delete set null
	);
    
create table if not exists instructor
(ID varchar(5),
 instructor_name varchar (20) not null,
 dept_name varchar (20),
 salary numeric (8,2) check (salary > 29000),
 primary key (ID),
 foreign key (dept_name) references department (dept_name) on delete set null
 );
            
create table if not exists section
(course_id varchar (8),
 sec_id varchar (8),
 semester varchar (6) check (semester in
					('Fall', 'Winter', 'Spring', 'Summer')),
 year numeric (4,0) check (year > 1701 and year < 2100),
 building varchar (15),
 room_number varchar (7),
 time_slotid varchar (4),
 primary key (course_id, sec_id, semester, year),
 foreign key (course_id) references course
		on delete cascade,
 foreign key (building, room_number) references classroom
		on delete set null
);

create table if not exists teaches
 (ID varchar (5),
  course_id varchar (8),
  sec_id varchar (8),
  semester varchar (8),
  year numeric(4,0),
  primary key(ID, course_id, sec_id, semester, year),
  foreign key(course_id, sec_id, semester, year) references section on delete cascade,
  foreign key(ID) references instructor
  on delete cascade
);

create table if not exists student
 (ID varchar(5),
  name varchar(20) not null,
  dept_name varchar(20),
  tot_cred numeric(3,0) check(tot_cred >= 0),
  primary key (ID),
  foreign key (dept_name) references department
  on delete set null);
  
create table if not exists takes
 (ID varchar (5),
  course_id varchar(8),
  sec_id varchar (8),
  semester varchar (6),
  year numeric (4,0),
  grade varchar (2),
  primary key(ID, course_id, sec_id, semester, year),
  foreign key(course_id, sec_id, semester, year) references section on delete cascade,
  foreign key(ID) references student on delete cascade
);