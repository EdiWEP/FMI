var express = require("express");
var router = express.Router();

let saladService = require("./saladService.js");
let saladRepository = require("./saladRepository.js");

router.get("/ingredients", (req,res) => {

    const list = saladService.getIngredients();

    if(list != undefined && list.length != 0) {
        res.status(200).send(list);
    }
    else {
        res.status(404).send("No ingredients in db");
    }


});

router.get("/ingredients/:id", (req, res) => {

    let list = saladService.getIngredients();
    let ingredientId = req.params.id;

    let checker = false;

    list.forEach(ingredient => {
        if(ingredient.id == id) {
            checker = true;
            res.status(200).send(ingredient);
        }
    })

    if (checker === false) {
        res.status(404).send("Can't find ingredient");
    }
});

router.post("/ingredients", (req, res) => {

    let newIngredient = saladService.addIngredient(req.body);
    res.status(200).send(newIngredient);
});

router.put("/ingredients/:id", (req, res) => {

    let list = saladService.getIngredients();

    let id = req.params.id;
    let checker = false;

    for(let i = 0; i < list.length; ++i) {
        if(list[i].id === id) {

            if(req.body.name) {
                list[i].name = req.body.name;
            }

            if(req.body.image) {
                list[i].image = req.body.image; 
            }
            
            checker = true;

            break;
        }
    }

    if(checker) {

        saladRepository.writeJSONFile(list);
        res.status(200).send("Updated ingredient");

    }
    else {
        res.status(404).send("Can't find ingredient");
    }
});

router.delete("/ingredients/:id", (req,res) => {

    let list = saladService.getIngredients();
    
    let id = req.params.id;

    let checker = false;

    for(let i = 0; i < list.length; ++i) {
        if(list[i].id === id) {
            checker = true;
            list.splice(i,1);
            break;
        }
    }

    if(checker) {
        saladRepository.writeJSONFile(list);
        res.status(200).send("Deleted ingredient");

    }
    else {
        res.status(404).send("Can't find ingredient");
    }
});

module.exports = router;