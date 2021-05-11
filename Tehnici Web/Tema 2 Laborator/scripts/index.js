const express = require("express");
const morgan = require("morgan");       // nu se stie ce face acesta
const bodyParser = require("body-parser");  // parseaza bodyul si il face json
const cors = require("cors");           // se foloseste pt a spune backendului ca poate fi accesata din anumite surse, daca e gol, inseamna ca poate fi accesata de oriunde, se poate pune ca parametru o adresa de la care sa accepte requesturi

const fs = require("fs");
const app = express();

app.use(morgan("tiny"));
app.use(bodyParser.json());
app.use(cors());

app.use(require("./saladController.js"));

app.listen("3000", () =>
  console.log("Server started at: http://localhost:3000")
);