import python_weather
import asyncio
import os

async def main() -> None:
    async with python_weather.Client(unit=python_weather.METRIC) as client:
        weather  = await client.get('Adelaide')
        return weather.temperature

if __name__ == '__main__':
    print(asyncio.run(main))
