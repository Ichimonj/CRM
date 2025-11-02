#include "date.hpp"
#include <stdexcept>
#include "location.hpp"
#include <ctime>
#include <stdio.h>

Date::Date()
{
	std::time_t t = std::time(nullptr);
	std::tm now;

#ifdef _MSC_VER 
	localtime_s(&now, &t); // Windows
#else
	now = *std::localtime(&t); // Non-Windows
#endif

	this->d_year	= now.tm_year + 1900;
	this->d_month	= now.tm_mon;
	this->d_day		= now.tm_mday;
	this->d_hour	= now.tm_hour;
	this->d_min		= now.tm_min;
}

Date::Date(
	const uint16_t year, 
	const uint8_t month, 
	const uint8_t day, 
	const uint8_t hour, 
	const uint8_t min
)
{
	if (year > 3000)
		throw std::runtime_error(errors::year_incorrect);

	if (month > 11)
		throw std::runtime_error(errors::month_incorrect);

	if (month == 1) { // February
		if (year % 4 == 0) { // Intercalary year
			if (day > 29)
				throw std::runtime_error(errors::day_incorrect);
		}
		else
		{
			if (day > 28)
				throw std::runtime_error(errors::day_incorrect);
		}
	}
	else {
		if (day > numberDaysInMonth(month))
			throw std::runtime_error(errors::day_incorrect);
	}

	if (hour > 23)
		throw std::runtime_error(errors::hour_incorrect);

	if (min > 59)
		throw std::runtime_error(errors::min_incorrect);

	this->d_year = year;
	this->d_month = month;
	this->d_day = day;
	this->d_hour = hour;
	this->d_min = min;
}

Date::Date(const Date& ex)
	:d_year(ex.d_year), d_month(ex.d_month), d_day(ex.d_day), d_hour(ex.d_hour), d_min(ex.d_min)
{
}

Date& Date::operator=(const Date& other)
{
	if (this == &other)
		return *this;

	this->d_year	= other.d_year;
	this->d_month	= other.d_month;
	this->d_day		= other.d_day;
	this->d_hour	= other.d_hour;
	this->d_min		= other.d_min;
	return *this;
}

bool Date::operator!=(const Date& other) const
{
	if (this->d_year != other.d_year)
		return true;
	if (this->d_month != other.d_month)
		return true;
	if (this->d_day != other.d_day)
		return true;
	if (this->d_hour != other.d_hour)
		return true;
	if (this->d_min != other.d_min)
		return true;
	return false;
}

bool Date::operator==(const Date& other) const
{
	if (this->d_year != other.d_year)
		return false;
	if (this->d_month != other.d_month)
		return false;
	if (this->d_day != other.d_day)
		return false;
	if (this->d_hour != other.d_hour)
		return false;
	if (this->d_min != other.d_min)
		return false;
	return true;
}

const std::string Date::getDateStr() const
{
	return std::string(std::to_string(this->d_day) + ' ' + this->monthToStr() + ' ' + std::to_string(this->d_year) + ' ' + std::to_string(this->d_hour) + ':' + std::to_string(this->d_min));
}

const uint16_t Date::getYear() const { return this->d_year; }
const uint8_t Date::getMonth() const { return this->d_month; }
const uint8_t Date::getDay()   const { return this->d_day; }
const uint8_t Date::getHour()  const { return this->d_hour; }
const uint8_t Date::getMin()   const { return this->d_min; }

const std::string Date::toJsonFormat() const {
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%04d-%02d-%02dT%02d:%02d:00",
		d_year, d_month, d_day, d_hour, d_min);
	return buffer;
}

const uint8_t Date::numberDaysInMonth(const uint8_t month) const
{
	switch (month)
	{
	case 0: case 2: case 4: case 6: case 7: case 9: case 11:
		return 31;
	default:
		return 30;
	}
}

const std::string Date::monthToStr() const
{
	switch (this->d_month)
	{
	case 0:
		return month_str::january;
		break;
	case 1:
		return month_str::february;
		break;
	case 2:
		return month_str::march;
		break;
	case 3:
		return month_str::april;
		break;
	case 4:
		return month_str::may;
		break;
	case 5:
		return month_str::june;
		break;
	case 6:
		return month_str::july;
		break;
	case 7:
		return month_str::august;
		break;
	case 8:
		return month_str::september;
		break;
	case 9:
		return month_str::october;
		break;
	case 10:
		return month_str::november;
		break;
	case 11:
		return month_str::december;
		break;
	default:
		return "NULL";
		break;
	}
}
