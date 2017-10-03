#pragma once

typedef struct employee
{
	int id;
	char salutation[4];
	char firstname[21];
	char surname[31];
	char position[16];
	int salary;
	int deleted;

} employee;