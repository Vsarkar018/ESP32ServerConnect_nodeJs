const mongoose = require("mongoose");

const PinSchema = new mongoose.Schema({
  GPIO_No: {
    type: Number,
    required: [true, "Please provide GPIO Pin Number"],
    unique:true
  },
  value: {
    type: Number,
    default: 0,
  },
});

module.exports = mongoose.model("Pin", PinSchema);
