const fs = require("fs");


const router = require("./saladController.js");

function readJSONFile() {
    return JSON.parse(fs.readFileSync("db.json"))["ingredients"];
}

module.exports.readJSONFile = () => {
    return JSON.parse(fs.readFileSync("db.json"))["ingredients"];
}

module.exports.writeJSONFile = (content) => {
    fs.writeFileSync(
        "db.json",
        JSON.stringify({ingredients: content}, null, 4),
        "utf8",
        err => {
            if(err) {
                console.log(err);
            }
        }
    )
}