import mongoose, { Schema, Types, Document, Model, mongo } from "mongoose";

interface Device {
  deviceId: string;
  ph: number;
  temp: number;
  ethanol: number;
  fan_relay: boolean;
  heater_relay: boolean;
  pump_relay: boolean;
  set: {
    fan: boolean;
    heater: boolean;
    pump: boolean;
  };
}

interface DeviceDocument extends Device, Document {}

const DeviceSchema: Schema<DeviceDocument> = new Schema<DeviceDocument>({
  deviceId: { type: String, required: true },
  ph: { type: Number, required: true },
  temp: { type: Number, required: true },
  ethanol: { type: Number, required: true },
  fan_relay: { type: Boolean, required: true },
  heater_relay: { type: Boolean, required: true },
  pump_relay: { type: Boolean, required: true },
  set: {
    fan: { type: Boolean, default: false },
    pump: { type: Boolean, default: false },
    heater: { type: Boolean, default: false },
  },
});

export const DeviceModel: Model<DeviceDocument> =
  mongoose.model<DeviceDocument>("Device", DeviceSchema);

export default DeviceModel;
