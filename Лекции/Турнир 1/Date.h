#pragma once
#include <string>
#include <vector>

class Date {
 private:
  int Year, Month, Day;

  void IncDay();

 public:
  Date(const int &y, const int &m, const int &d);

  bool IsLeap() const;

  std::string ToString() const;

  Date DaysLater(const int &days) const;

  int DaysLeft(const Date &otherDate) const;
};

int DateToDays(int year, int month, const int &day) {
  double ycor = 0;
  if (year <= 0) ycor = 0.75;
  if (month <= 2) {
    --year;
    month += 12;
  }
  int b = 0;
  if (((year * 10000) + (month * 100) + day) >= 15821015) {
    int a = year / 100;
    b = 2 - a + (a / 4);
  }
  int yn = (365.25 * year) - ycor;
  return floor(yn + (30.6001 * (month + 1)) + day + b - 679006);
}

std::vector<int> GetAllMonths(const bool &isLeapYear) {
  return {31, (isLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}

std::string AddNulls(std::string str, const int &s) {
  while (size(str) < s) {
    str.insert(0, 1, '0');
  }
  return str;
}

void Date::IncDay() {
  const auto allMonths = GetAllMonths(IsLeap());
  // Month isnt ful
  if (Day < allMonths[Month - 1]) {
    ++Day;
    return;
  }
  // Month is full, Year isn full
  if (Month < 12) {
    ++Month;
    Day = 1;
    return;
  }
  // Year is full
  Month = 1;
  Day = 1;
  ++Year;
}

Date Date::DaysLater(const int &days) const {
  Date res = *this;
  for (int i = 0; i < days; ++i) {
    res.IncDay();
  }
  return res;
}

int Date::DaysLeft(const Date &otherDate) const {
  return DateToDays(otherDate.Year, otherDate.Month, otherDate.Day) -
         DateToDays(Year, Month, Day);
}

std::string Date::ToString() const {
  return AddNulls(std::to_string(Day), 2) + '.' +
         AddNulls(std::to_string(Month), 2) + '.' +
         AddNulls(std::to_string(Year), 4);
}

bool Date::IsLeap() const {
  return !(Year % 4 != 0 || Year % 100 == 0 && Year % 400 != 0);
}

Date::Date(const int &y, const int &m, const int &d)
    : Year(y), Month(m), Day(d) {}