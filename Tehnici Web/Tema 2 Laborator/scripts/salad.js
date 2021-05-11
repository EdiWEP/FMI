var currentId;
var container = document.getElementsByClassName("ingredientsContainer")[0];


function getAllIngredients() {

    fetch("http://localhost:3000/ingredients",
    {
        method: 'get'
    }).then( function(response) {
        response.json().then((data) => {
            
            for(let i = 0; i < data.length; ++i) {

                let h3 = document.createElement("h3");
                h3.innerText = data[i].name;
                h3.setAttribute("class", "ingredientName");
                
                let image = document.createElement("img");
                image.setAttribute("src", data[i].image);


                container.appendChild(h3);
                container.appendChild(image);

                let editButton = document.createElement("button");
                let editText = document.createTextNode("Edit");
                editButton.setAttribute("class", "individualButton");
                editButton.appendChild(editText);

                editButton.onclick = function() {
                    document.getElementById("nameInput").value = data[i].name;
                    document.getElementById("imageInput").value = data[i].image;
                    currentId = data[i].id;
                }

                container.appendChild(editButton);

                let deleteButton = document.createElement("button");
                let deleteText = document.createTextNode("Delete");
                deleteButton.setAttribute("class", "individualButton");

                deleteButton.appendChild(deleteText);

                deleteButton.addEventListener("click", function() {
                    deleteIngredient(data[i].id);
                });

                container.appendChild(deleteButton);

            }
        })
    })
}


getAllIngredients();

function addIngredient() {

    let name = document.getElementById("nameInput").value;
    let image = document.getElementById("imageInput").value;

    let newIngredient = {
        name: name,
        image: image
    } 

    fetch("http://localhost:3000/ingredients", {

        method: 'post',

        headers: {
            'Content-Type': 'application/json'
        },

        body: JSON.stringify(newIngredient) 
    
    }).then(function(response) {
        console.log(response);
    })
    
}

function editIngredient() {

    let name = document.getElementById("nameInput").value;
    let image = document.getElementById("imageInput").value;

    let newIngredient = {
        name: name,
        image: image
    }

    console.log(currentId);
    fetch("http://localhost:3000/ingredients/" + currentId , {

    method: 'put',

    headers: {
        'Content-Type': 'application/json'
    },

    body: JSON.stringify(newIngredient)
    }).then(function(response) {
        window.location.reload();
    })
}

function deleteIngredient(id) {

    fetch("http://localhost:3000/ingredients/" + id, {

        method: 'delete',

        headers: {

            'Content-Type': 'application/json'
        }
    }).then(function(response) {
        window.location.reload();
    })
}

document.addEventListener("keydown", checkKey);

function checkKey(key) {
    
    if (key.key == "Delete") {

        deleteIngredient(currentId);
    }
}