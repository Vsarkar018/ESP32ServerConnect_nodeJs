require("dotenv").config();
const express = require("express");
const app = express();
const connectDB = require("./connectDB");
app.use(express.json());

const pinRouter = require("./routes/pins");

app.use(pinRouter);

const port = process.env.PORT || 5000;
const start = async () => {
  try {
    await connectDB(process.env.MONGO_URI);
    app.listen(port, () => console.log(`Server listening to port ${port}...`));
  } catch (error) {
    console.log(error);
  }
};

start();
