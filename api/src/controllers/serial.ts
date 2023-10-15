import { SerialPort, ReadlineParser } from "serialport";
import dotenv from "dotenv";
dotenv.config();

export default function initializeSerial() {
  const port = new SerialPort({
    path: process.env.SERIAL_PORT,
    baudRate: 9600,
  });

  const parser = port.pipe(new ReadlineParser({ delimiter: "\n" })); // Read the port data

  port.on("open", () => {
    console.log("serial port open");
  });

  parser.on("data", (data) => {
    console.log("got word from arduino:", data);
  });

  return { port, parser };
}

export function sendToSerial(message: string, port: SerialPort) {
  const result = port.write("data", (err) => {
    if (err) {
      return console.error("Error on serial:", err);
    }
    console.log("Message written");
  });

  return result;
}
