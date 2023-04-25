const Pin = require("../model/pin");
const addButton = async (req, res) => {
  const data = await Pin.create({...req.body});
  res.status(200).json({ data });
};
const getButton = async (req, res) => {
  const data = await Pin.find();

  //Sending Only Necesesary Data to ESP32
  let temp = [];
  data.forEach(ele => {
    temp.push({ g: ele.GPIO_No, v: ele.value });
  });
  res.status(200).json({ ...temp });
};
const updateButton = async (req, res) => {
  const data = await Pin.findByIdAndUpdate(
    { _id: req.params.id },
    {
      value: req.body.value,
    },
    {
      new: true,
      runValidators: true,
    }
  );
  res.status(200).json({ data });
};

module.exports = { updateButton, getButton, addButton };
