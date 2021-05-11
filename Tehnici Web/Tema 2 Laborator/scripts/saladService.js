const uuid = require("uuid");
const saladRepository = require("./saladRepository.js");

module.exports.getIngredients = () => {
    let list = saladRepository.readJSONFile();
    return list;
}

module.exports.addIngredient = (newIngredient) => {

    const list = saladRepository.readJSONFile();

    newIngredient.id = uuid.v4.apply();

    list.push(newIngredient);

    saladRepository.writeJSONFile(list);

    res.status(200).send(newIngredient);

    return newIngredient;
}