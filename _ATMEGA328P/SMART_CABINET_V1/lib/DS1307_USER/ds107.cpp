#include "ds1307.h"

const uint8_t DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const uint8_t NumberOfFields = 7;
DateTime_t DateTimeNow;
void readDS1307()
{
    Wire.beginTransmission(DS1307);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307, NumberOfFields);

    DateTimeNow.second = bcd2dec(Wire.read() & 0x7f);
    DateTimeNow.minute = bcd2dec(Wire.read());
    DateTimeNow.hour = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
    DateTimeNow.wday = bcd2dec(Wire.read());
    DateTimeNow.day = bcd2dec(Wire.read());
    DateTimeNow.month = bcd2dec(Wire.read());
    DateTimeNow.year = bcd2dec(Wire.read());
    DateTimeNow.year += 2000;
}
int bcd2dec(uint8_t num)
{
    return ((num / 16 * 10) + (num % 16));
}
int dec2bcd(uint8_t num)
{
    return ((num / 10 * 16) + (num % 10));
}
/* cài đặt thời gian cho DS1307 */
void setTime(uint8_t hr, uint8_t min, uint8_t sec, uint8_t wd, uint8_t d, uint8_t mth, uint8_t yr)
{
    Wire.beginTransmission(DS1307);
    Wire.write(uint8_t(0x00)); // đặt lại pointer
    Wire.write(dec2bcd(sec));
    Wire.write(dec2bcd(min));
    Wire.write(dec2bcd(hr));
    Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
    Wire.write(dec2bcd(d));
    Wire.write(dec2bcd(mth));
    Wire.write(dec2bcd(yr));
    Wire.endTransmission();
}