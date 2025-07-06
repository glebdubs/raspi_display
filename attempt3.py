from RPLCD.i2c import CharLCD
from gpiozero import CPUTemperature
from time import sleep
import python_weather
import asyncio
import dis
import os

lcd = CharLCD('PCF8574', 0x3F, cols=16, rows=2)

lcd.write_string("wassup nigga")
sleep(3)
cpu = CPUTemperature()

async def main() -> None:
    async with python_weather.Client(unit=python_weather.METRIC) as client:
        weather  = await client.get('Adelaide')
        return weather.temperature

while True:
    lcd.clear()
    lcd.write_string(f"CPU Temp: {cpu.temperature}")
    lcd.cursor_pos = (1, 0)
    lcd.write_string('\u00b0')
    sleep(3)
