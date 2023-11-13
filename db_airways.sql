/*
A database used to store flight information for an airport, this includes flights arriving and departing,
and the passengers on the flights, employees.
*/

drop database if exists db_airways;
create database if not exists db_airways;

use db_airways;

create table if not exists person
	(person_name		varchar(20),
	 address			varchar(40),
	 phone				varchar(13),
	 primary key(person_name, address, phone)
	);

create table if not exists passenger
	(ticket_number		varchar(20),
     person_name		varchar(20),
     primary key(person_name, ticket_number),
     foreign key (person_name) references person(person_name)
    );
  
create table if not exists flight
	(flight_number		varchar(10),
     origin				varchar(3),
     destination		varchar(3),
     departure_time		time,
     arrival_time		time,
     flight_status		varchar(10),
     primary key(flight_number)
	);
    
create table if not exists departure
	(flight_number		varchar(10),
	 departure_date		varchar(20),
	 primary key(departure_date, flight_number),
     foreign key(flight_number) references flight(flight_number)
	);
    
create table if not exists booked_on
	(person_name		varchar(20),
     ticket_number		varchar(20),
     departure_date		varchar(20),
     flight_number		varchar(10),
     foreign key(person_name, ticket_number) references passenger(person_name, ticket_number),
	 foreign key(departure_date, flight_number) references departure(departure_date, flight_number)
    );
    
create table if not exists employee
	(employee_name		varchar(20),
     employee_no		varchar(5),
     salary				numeric(10,2) check (salary > 0),
     primary key(employee_no),
     foreign key (employee_name) references person(person_name) on delete set null
	);

create table if not exists assigned_to
	(employee_no		varchar(5),
     departure_date		varchar(20),
     flight_number		varchar(10),
     foreign key(employee_no) references employee(employee_no),
     foreign key(departure_date, flight_number) references departure(departure_date, flight_number)
    );
create table if not exists pilot
	(flight_hours		varchar(6),
     employee_no		varchar(5),
     foreign key (employee_no) references employee(employee_no) on delete set null
	);

create table if not exists plane
	(maker				varchar(20),
     model_number		varchar(5),
     primary key(model_number)
	);
    
create table if not exists can_fly
	(employee_no		varchar(5),
     model_number		varchar(5),
     foreign key (employee_no) references employee(employee_no),
     foreign key (model_number) references plane(model_number)
    );

create table if not exists aircraft
	(serial_number		varchar(4),
     model_number		varchar(5),
     primary key(serial_number, model_number),
     foreign key (model_number) references plane(model_number)
	);
