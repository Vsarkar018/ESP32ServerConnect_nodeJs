const express = require("express");
const router = express.Router();

const { addButton, updateButton, getButton } = require("../controller/pin");

router.route("/").post(addButton).get(getButton);
router.route("/:id").patch(updateButton);

module.exports = router;
