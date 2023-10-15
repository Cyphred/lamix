# Arduino Usage

## Serial output

The serial output is formatted in a comma-separated value.

| Column | Data                  |
| ------ | --------------------- |
| 0      | pH level reading      |
| 1      | Ethanol level reading |
| 2      | Temperature reading   |
| 3      | Fan relay state       |
| 4      | Heater relay state    |
| 5      | Pump relay state      |

## Relay Control

| Char | Result                   |
| ---- | ------------------------ |
| `1`  | Turns on `FAN_RELAY`     |
| `2`  | Turns off `FAN_RELAY`    |
| `3`  | Turns on `HEATER_RELAY`  |
| `4`  | Turns off `HEATER_RELAY` |
| `5`  | Turns on `PUMP_RELAY`    |
| `6`  | Turns off `PUMP_RELAY`   |
