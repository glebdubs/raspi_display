from RPLCD.i2c import CharLCD
from gpiozero import CPUTemperature
from time import sleep
from datetime import datetime
from zoneinfo import ZoneInfo
import python_weather
import asyncio
import os

lcd = CharLCD('PCF8574', 0x3F, cols=16, rows=2)

current_time = datetime.now(ZoneInfo("Australia/Adelaide")).strftime('%I:%M %p')

lcd.write_string("loading.")
sleep(1)
lcd.write_string(".")
sleep(1)
lcd.write_string(".")
sleep(1)

cpu = CPUTemperature()

degrees_sign = (
    0b01110,
    0b01010,
    0b01110,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
        )
lcd.create_char(0,degrees_sign)

async def main() -> None:
    async with python_weather.Client(unit=python_weather.METRIC) as client:
        weather  = await client.get('Adelaide')
        return weather.temperature

while True:
    lcd.clear()
    lcd.write_string(f"CPU Temp:{cpu.temperature:.2f}\x00C")
    lcd.cursor_pos = (1, 0)
    lcd.write_string(f"{current_time}  {asyncio.run(main())}\x00C")
    sleep(60)
