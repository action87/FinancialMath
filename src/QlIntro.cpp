#include <ql/quantlib.hpp>
#include <iostream>

using namespace QuantLib;

void dateIntroduction()
{
  //constructors:
  //  Date() - returns null date
  //  Date(BigInteger serialNumber) - number of days from 1899-12-31 (as in Excel)
  //  Date(Day d, Month m, Year y) - Day is integral, Month/Year special Quantlib type (see below)
  
  //member functions (the names are quite self-explanatory):
  //  Weekday weekday() const
  //  Day dayOfMonth() const
  //  Day dayOfYear() const
  //  Month month() const
  //  Year year() const
  //  BigInteger serialNumber()
  //  algebra: you can do usual date algebra (increment, add days/months/years)
  
  //static member functions:
  //  Date todaysDate()
  //  Date minDate()
  //  Date maxDate()
  //  bool isLeap(Year y)
  //  Date endOfMonth(const Date& d)
  //  bool isEndOfMonth(const Date& d)
  //  Date nextWeekday(const Date &d, Weekday w)
  
  //other related functions:
  //  comparison (==, <=, <, ...)
  //  Time daysBetween(const Date&, const Date&)
  //  operator<< to write to ostream
  
  Date myDate(11, Jun, 2016);
  auto today = Date::todaysDate();
  std::cout << "========= Date =========" << std::endl;
  std::cout << "Today's date: " << today << std::endl;
  std::cout << "Next Friday: " << Date::nextWeekday(today, Friday) << std::endl;
  std::cout << "1 month from today: " << today + 1*Months << std::endl;
  std::cout << "End of month: " << Date::endOfMonth(today) << std::endl;
}

void calendarIntroduction()
{
  //A calendar shows the holidays, business days and weekends
  //There are many calendars implemented in Quantlib:
  //  Germany - Settlement, FrankfurtStockExchange, Xetra, Eurex
  //  UnitedKingdom - Settlement, Exchange, Metals
  //  TARGET (Trans-European Automated Real-time Gross settlement Express Transfer)
  //  etc.

  //interface:
  //  string name() - returns the name of the calendar
  //  bool isBusinessDay(const Date&) const
  //  bool isHoliday(const Date&) const
  //  bool isWeekend(const Date&) const
  //  bool isEndOfMonth(const Date&) const - true if it's the last business day
  //  Date endOfMonth(const Date&) const
  //  vector<Date> holidayList(Calendar, Date, Date, bool includeWeekends)
  //  Date adjust(Date, BusinessDayConvention) - see later section for BusinessDayConvention
  //  Date advance(Date, Integer, TimeUnit, BusinessDayConvention, bool endOfMonth) - see later
  //  Date advance(Date, Period, BusinessDayConvention, bool endOfMonth) - see later
  
  Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
  Calendar hungaryCal = Hungary();
  Date today = Date::todaysDate();

  std::cout << std::endl << "======== Calendar =========" << std::endl;
  std::cout << "Calendar: " << frankfCal.name() << std::endl;
  std::cout << "Date: " << today << std::endl;
  std::cout << "Is it business day?: " << frankfCal.isBusinessDay(today) << std::endl;
  std::cout << "Is it the last BD in the month?: " << frankfCal.isEndOfMonth(today) << std::endl;
  std::cout << "Last BD in the month: " << frankfCal.endOfMonth(today) << std::endl;
  
  std::cout << "Holidays in Hungary in the next 6 months: " << std::endl;
  auto holidayList = hungaryCal.holidayList(hungaryCal, today, today + 6*Months, false);
  for (const auto& holiday: holidayList)
    std::cout << "  " << holiday << std::endl;
}

void businessDayConventionIntroduction()
{
  //If a transaction date falls on a holiday than it 
  // must be adjusted based on the Business Day Convention.
  //The following conventions are available in QuantLib:
  //  Following: first following business day
  //  ModifiedFollowing: if the first following business day is in the next month
  //    than it will be the first preceding business day
  //  Preceding: first preceding business day
  //  ModifiedPreceding: if the first preceding business day is in the previous month
  //    than it will be the first following business day
  //  Unadjusted
  
  Date today = Date::todaysDate();
  Calendar hungaryCal = Hungary();
  
  std::cout << std::endl << "========= Business Day Convention ===========" << std::endl;
  std::cout << "Date: " << today << std::endl;
  std::cout << "Calendar: " << hungaryCal.name() << std::endl;
  std::cout << "Advancing by 1 month, using ModifiedFollowing convention: " << hungaryCal.advance(today, 1, Months, BusinessDayConvention(ModifiedFollowing), false) << std::endl;
}

void daycountIntroduction()
{
  //The following daycount conventions are available in QuantLib:
  //  Actual360, Actual365Fixed, ActualActual, Business252, Thirty360
  
  auto today = Date::todaysDate();
  // advance it by 3M using TARGET calendar 
  // and ModifiedFollowing business day convention
  Calendar myCal = TARGET();
  auto todayAdvanced = myCal.advance(
      today, 
      3, 
      Months,
      BusinessDayConvention(ModifiedFollowing),
     false);
  // calculate daycount/yearfraction between them using Actual360
  DayCounter dc = Actual360();
  std::cout << std::endl << "========== Daycount =========" << std::endl;
  std::cout << "Date: " << today << std::endl;
  std::cout << "3M advanced (TARGET, ModifiedFollowing): " << todayAdvanced << std::endl;
  std::cout << "Daycount using Actual360: " << dc.dayCount(today, todayAdvanced) << std::endl;
  std::cout << "Yearfraction using Actual360: " << dc.yearFraction(today, todayAdvanced) << std::endl;
}

int main()
{
  dateIntroduction();

  calendarIntroduction();

  businessDayConventionIntroduction();

  daycountIntroduction();

  return 0;
}
